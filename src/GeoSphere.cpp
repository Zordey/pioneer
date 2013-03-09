// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "GeoSphere.h"
#include "perlin.h"
#include "Pi.h"
#include "RefCounted.h"
#include "graphics/Material.h"
#include "graphics/Renderer.h"
#include "graphics/Frustum.h"
#include "graphics/Graphics.h"
#include "graphics/VertexArray.h"
#include "graphics/gl2/GeoSphereMaterial.h"
#include "vcacheopt/vcacheopt.h"
#include <deque>
#include <algorithm>

// tri edge lengths
#define GEOPATCH_SUBDIVIDE_AT_CAMDIST	5.0
#define GEOPATCH_MAX_DEPTH  15 + (2*Pi::detail.fracmult) //15

static const int GEOPATCH_MAX_EDGELEN = 55;
int GeoSphere::s_vtxGenCount = 0;
RefCountedPtr<GeoPatchContext> GeoSphere::s_patchContext;

// must be odd numbers
static const int detail_edgeLen[5] = {
	7, 15, 25, 35, 55
};

#define PRINT_VECTOR(_v) printf("%f,%f,%f\n", (_v).x, (_v).y, (_v).z);

#pragma pack(4)
struct VBOVertex
{
	float x,y,z;
	float nx,ny,nz;
	unsigned char col[4];
	float padding;
};
#pragma pack()

// hold the 16 possible terrain edge connections
const int NUM_INDEX_LISTS = 16;

class GeoPatchContext : public RefCounted {
public:
	int edgeLen;

	inline int VBO_COUNT_LO_EDGE() const { return 3*(edgeLen/2); }
	inline int VBO_COUNT_HI_EDGE() const { return 3*(edgeLen-1); }
	inline int VBO_COUNT_MID_IDX() const { return (4*3*(edgeLen-3))    + 2*(edgeLen-3)*(edgeLen-3)*3; }
	//                                            ^^ serrated teeth bit  ^^^ square inner bit

	inline int IDX_VBO_LO_OFFSET(int i) const { return i*sizeof(unsigned short)*3*(edgeLen/2); }
	inline int IDX_VBO_HI_OFFSET(int i) const { return (i*sizeof(unsigned short)*VBO_COUNT_HI_EDGE())+IDX_VBO_LO_OFFSET(4); }
	inline int IDX_VBO_MAIN_OFFSET()    const { return IDX_VBO_HI_OFFSET(4); }
	inline int IDX_VBO_COUNT_ALL_IDX()	const { return ((edgeLen-1)*(edgeLen-1))*2*3; }

	inline int NUMVERTICES() const { return edgeLen*edgeLen; }

	double frac;

	ScopedArray<unsigned short> midIndices;
	ScopedArray<unsigned short> loEdgeIndices[4];
	ScopedArray<unsigned short> hiEdgeIndices[4];
	GLuint indices_vbo;
	GLuint indices_list[NUM_INDEX_LISTS];
	GLuint indices_tri_count;
	GLuint indices_tri_counts[NUM_INDEX_LISTS];
	VBOVertex *vbotemp;

	GeoPatchContext(int _edgeLen) : edgeLen(_edgeLen) {
		Init();
	}

	~GeoPatchContext() {
		Cleanup();
	}

	void Refresh() {
		Cleanup();
		Init();
	}

	void Cleanup() {
		midIndices.Reset();
		for (int i=0; i<4; i++) {
			loEdgeIndices[i].Reset();
			hiEdgeIndices[i].Reset();
		}
		if (indices_vbo) {
			indices_vbo = 0;
		}
		for (int i=0; i<NUM_INDEX_LISTS; i++) {
			if (indices_list[i]) {
				glDeleteBuffersARB(1, &indices_list[i]);
			}
		}
		delete [] vbotemp;
	}

	void updateIndexBufferId(const GLuint edge_hi_flags) {
		assert(edge_hi_flags < GLuint(NUM_INDEX_LISTS));
		indices_vbo = indices_list[edge_hi_flags];
		indices_tri_count = indices_tri_counts[edge_hi_flags];
	}

	int getIndices(std::vector<unsigned short> &pl, const unsigned int edge_hi_flags)
	{
		// calculate how many tri's there are
		int tri_count = (VBO_COUNT_MID_IDX() / 3);
		for( int i=0; i<4; ++i ) {
			if( edge_hi_flags & (1 << i) ) {
				tri_count += (VBO_COUNT_HI_EDGE() / 3);
			} else {
				tri_count += (VBO_COUNT_LO_EDGE() / 3);
			}
		}

		// pre-allocate enough space
		pl.reserve(tri_count);

		// add all of the middle indices
		for(int i=0; i<VBO_COUNT_MID_IDX(); ++i) {
			pl.push_back(midIndices[i]);
		}
		// selectively add the HI or LO detail indices
		for (int i=0; i<4; i++) {
			if( edge_hi_flags & (1 << i) ) {
				for(int j=0; j<VBO_COUNT_HI_EDGE(); ++j) {
					pl.push_back(hiEdgeIndices[i][j]);
				}
			} else {
				for(int j=0; j<VBO_COUNT_LO_EDGE(); ++j) {
					pl.push_back(loEdgeIndices[i][j]);
				}
			}
		}

		return tri_count;
	}

	void Init() {
		frac = 1.0 / double(edgeLen-1);

		vbotemp = new VBOVertex[NUMVERTICES()];

		unsigned short *idx;
		midIndices.Reset(new unsigned short[VBO_COUNT_MID_IDX()]);
		for (int i=0; i<4; i++) {
			loEdgeIndices[i].Reset(new unsigned short[VBO_COUNT_LO_EDGE()]);
			hiEdgeIndices[i].Reset(new unsigned short[VBO_COUNT_HI_EDGE()]);
		}
		/* also want vtx indices for tris not touching edge of patch */
		idx = midIndices.Get();
		for (int x=1; x<edgeLen-2; x++) {
			for (int y=1; y<edgeLen-2; y++) {
				idx[0] = x + edgeLen*y;
				idx[1] = x+1 + edgeLen*y;
				idx[2] = x + edgeLen*(y+1);
				idx+=3;

				idx[0] = x+1 + edgeLen*y;
				idx[1] = x+1 + edgeLen*(y+1);
				idx[2] = x + edgeLen*(y+1);
				idx+=3;
			}
		}
		{
			for (int x=1; x<edgeLen-3; x+=2) {
				// razor teeth near edge 0
				idx[0] = x + edgeLen;
				idx[1] = x+1;
				idx[2] = x+1 + edgeLen;
				idx+=3;
				idx[0] = x+1;
				idx[1] = x+2 + edgeLen;
				idx[2] = x+1 + edgeLen;
				idx+=3;
			}
			for (int x=1; x<edgeLen-3; x+=2) {
				// near edge 2
				idx[0] = x + edgeLen*(edgeLen-2);
				idx[1] = x+1 + edgeLen*(edgeLen-2);
				idx[2] = x+1 + edgeLen*(edgeLen-1);
				idx+=3;
				idx[0] = x+1 + edgeLen*(edgeLen-2);
				idx[1] = x+2 + edgeLen*(edgeLen-2);
				idx[2] = x+1 + edgeLen*(edgeLen-1);
				idx+=3;
			}
			for (int y=1; y<edgeLen-3; y+=2) {
				// near edge 1
				idx[0] = edgeLen-2 + y*edgeLen;
				idx[1] = edgeLen-1 + (y+1)*edgeLen;
				idx[2] = edgeLen-2 + (y+1)*edgeLen;
				idx+=3;
				idx[0] = edgeLen-2 + (y+1)*edgeLen;
				idx[1] = edgeLen-1 + (y+1)*edgeLen;
				idx[2] = edgeLen-2 + (y+2)*edgeLen;
				idx+=3;
			}
			for (int y=1; y<edgeLen-3; y+=2) {
				// near edge 3
				idx[0] = 1 + y*edgeLen;
				idx[1] = 1 + (y+1)*edgeLen;
				idx[2] = (y+1)*edgeLen;
				idx+=3;
				idx[0] = 1 + (y+1)*edgeLen;
				idx[1] = 1 + (y+2)*edgeLen;
				idx[2] = (y+1)*edgeLen;
				idx+=3;
			}
		}
		// full detail edge triangles
		{
			idx = hiEdgeIndices[0].Get();
			for (int x=0; x<edgeLen-1; x+=2) {
				idx[0] = x; idx[1] = x+1; idx[2] = x+1 + edgeLen;
				idx+=3;
				idx[0] = x+1; idx[1] = x+2; idx[2] = x+1 + edgeLen;
				idx+=3;
			}
			idx = hiEdgeIndices[1].Get();
			for (int y=0; y<edgeLen-1; y+=2) {
				idx[0] = edgeLen-1 + y*edgeLen;
				idx[1] = edgeLen-1 + (y+1)*edgeLen;
				idx[2] = edgeLen-2 + (y+1)*edgeLen;
				idx+=3;
				idx[0] = edgeLen-1 + (y+1)*edgeLen;
				idx[1] = edgeLen-1 + (y+2)*edgeLen;
				idx[2] = edgeLen-2 + (y+1)*edgeLen;
				idx+=3;
			}
			idx = hiEdgeIndices[2].Get();
			for (int x=0; x<edgeLen-1; x+=2) {
				idx[0] = x + (edgeLen-1)*edgeLen;
				idx[1] = x+1 + (edgeLen-2)*edgeLen;
				idx[2] = x+1 + (edgeLen-1)*edgeLen;
				idx+=3;
				idx[0] = x+1 + (edgeLen-2)*edgeLen;
				idx[1] = x+2 + (edgeLen-1)*edgeLen;
				idx[2] = x+1 + (edgeLen-1)*edgeLen;
				idx+=3;
			}
			idx = hiEdgeIndices[3].Get();
			for (int y=0; y<edgeLen-1; y+=2) {
				idx[0] = y*edgeLen;
				idx[1] = 1 + (y+1)*edgeLen;
				idx[2] = (y+1)*edgeLen;
				idx+=3;
				idx[0] = (y+1)*edgeLen;
				idx[1] = 1 + (y+1)*edgeLen;
				idx[2] = (y+2)*edgeLen;
				idx+=3;
			}
		}
		// these edge indices are for patches with no
		// neighbour of equal or greater detail -- they reduce
		// their edge complexity by 1 division
		{
			idx = loEdgeIndices[0].Get();
			for (int x=0; x<edgeLen-2; x+=2) {
				idx[0] = x;
				idx[1] = x+2;
				idx[2] = x+1+edgeLen;
				idx += 3;
			}
			idx = loEdgeIndices[1].Get();
			for (int y=0; y<edgeLen-2; y+=2) {
				idx[0] = (edgeLen-1) + y*edgeLen;
				idx[1] = (edgeLen-1) + (y+2)*edgeLen;
				idx[2] = (edgeLen-2) + (y+1)*edgeLen;
				idx += 3;
			}
			idx = loEdgeIndices[2].Get();
			for (int x=0; x<edgeLen-2; x+=2) {
				idx[0] = x+edgeLen*(edgeLen-1);
				idx[2] = x+2+edgeLen*(edgeLen-1);
				idx[1] = x+1+edgeLen*(edgeLen-2);
				idx += 3;
			}
			idx = loEdgeIndices[3].Get();
			for (int y=0; y<edgeLen-2; y+=2) {
				idx[0] = y*edgeLen;
				idx[2] = (y+2)*edgeLen;
				idx[1] = 1 + (y+1)*edgeLen;
				idx += 3;
			}
		}

		// these will hold the optimised indices
		std::vector<unsigned short> pl_short[NUM_INDEX_LISTS];
		// populate the N indices lists from the arrays built during InitTerrainIndices()
		for( int i=0; i<NUM_INDEX_LISTS; ++i ) {
			const unsigned int edge_hi_flags = i;
			indices_tri_counts[i] = getIndices(pl_short[i], edge_hi_flags);
		}

		// iterate over each index list and optimize it
		for( int i=0; i<NUM_INDEX_LISTS; ++i ) {
			int tri_count = indices_tri_counts[i];
			VertexCacheOptimizerUShort vco;
			VertexCacheOptimizerUShort::Result res = vco.Optimize(&pl_short[i][0], tri_count);
			assert(0 == res);
		}

		// everything should be hunky-dory for setting up as OpenGL index buffers now.
		for( int i=0; i<NUM_INDEX_LISTS; ++i ) {
			glGenBuffersARB(1, &indices_list[i]);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, indices_list[i]);
			glBufferDataARB(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short)*indices_tri_counts[i]*3, &(pl_short[i][0]), GL_STATIC_DRAW);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		// default it to the last entry which uses the hi-res borders
		indices_vbo			= indices_list[NUM_INDEX_LISTS-1];
		indices_tri_count	= indices_tri_counts[NUM_INDEX_LISTS-1];

		if (midIndices) {
			midIndices.Reset();
			for (int i=0; i<4; i++) {
				loEdgeIndices[i].Reset();
				hiEdgeIndices[i].Reset();
			}
		}
	}

	void GetEdge(vector3d *array, int edge, vector3d *ev) {
		if (edge == 0) {
			for (int x=0; x<edgeLen; x++) ev[x] = array[x];
		} else if (edge == 1) {
			const int x = edgeLen-1;
			for (int y=0; y<edgeLen; y++) ev[y] = array[x + y*edgeLen];
		} else if (edge == 2) {
			const int y = edgeLen-1;
			for (int x=0; x<edgeLen; x++) ev[x] = array[(edgeLen-1)-x + y*edgeLen];
		} else {
			for (int y=0; y<edgeLen; y++) ev[y] = array[0 + ((edgeLen-1)-y)*edgeLen];
		}
	}

	void SetEdge(vector3d *array, int edge, const vector3d *ev) {
		if (edge == 0) {
			for (int x=0; x<edgeLen; x++) array[x] = ev[x];
		} else if (edge == 1) {
			const int x = edgeLen-1;
			for (int y=0; y<edgeLen; y++) array[x + y*edgeLen] = ev[y];
		} else if (edge == 2) {
			const int y = edgeLen-1;
			for (int x=0; x<edgeLen; x++) array[(edgeLen-1)-x + y*edgeLen] = ev[x];
		} else {
			for (int y=0; y<edgeLen; y++) array[0 + ((edgeLen-1)-y)*edgeLen] = ev[y];
		}
	}
};



class GeoPatch {
private:
	//********************************************************************************
	// Overloaded PureJob class to handle generating the mesh for each patch
	//********************************************************************************
	class PatchJob : public PureJob
	{
	public:
		PatchJob(const SSplitRequestDescription &data) : mData(data)
		{
		}

		virtual ~PatchJob()
		{
		}

		virtual void init(unsigned int *counter)
		{
			PureJob::init( counter );
		}

		virtual void job_process(void * userData,int /* userId */)    // RUNS IN ANOTHER THREAD!! MUST BE THREAD SAFE!
		{
			const vector3d v01	= (mData.v0+mData.v1).Normalized();
			const vector3d v12	= (mData.v1+mData.v2).Normalized();
			const vector3d v23	= (mData.v2+mData.v3).Normalized();
			const vector3d v30	= (mData.v3+mData.v0).Normalized();
			const vector3d cn	= (mData.centroid).Normalized();

			// 
			const vector3d vecs[4][4] = {
				{mData.v0,	v01,		cn,			v30},
				{v01,		mData.v1,	v12,		cn},
				{cn,		v12,		mData.v2,	v23},
				{v30,		cn,			v23,		mData.v3}
			};

			SSplitResult *sr = new SSplitResult(mData.patchID.GetPatchFaceIdx(), mData.depth);
			for (int i=0; i<4; i++)
			{
				// fill out the data
				GenerateMesh(mData.vertices[i], mData.normals[i], mData.colors[i], 
					vecs[i][0], vecs[i][1], vecs[i][2], vecs[i][3], 
					mData.edgeLen, mData.fracStep);
				// add this patches data
				sr->addResult(mData.vertices[i], mData.normals[i], mData.colors[i], 
					vecs[i][0], vecs[i][1], vecs[i][2], vecs[i][3], 
					mData.patchID.NextPatchID(mData.depth+1, i));
			}
			mData.pGeoSphere->AddSplitResult(sr);
		}

		virtual void job_onFinish(void * userData, int userId)  // runs in primary thread of the context
		{
			PureJob::job_onFinish(userData, userId);
		}

		virtual void job_onCancel(void * userData, int userId)   // runs in primary thread of the context
		{
			PureJob::job_onCancel(userData, userId);
		}

	private:
		const SSplitRequestDescription	mData;

		/* in patch surface coords, [0,1] */
		inline vector3d GetSpherePoint(const vector3d &v0, const vector3d &v1, const vector3d &v2, const vector3d &v3, const double x, const double y) const {
			return (v0 + x*(1.0-y)*(v1-v0) +
					x*y*(v2-v0) +
					(1.0-x)*y*(v3-v0)).Normalized();
		}

		// Generates full-detail vertices, and also non-edge normals and colors 
		void GenerateMesh(
			vector3d *vertices, vector3d *normals, vector3d *colors, 
			const vector3d &v0,
			const vector3d &v1,
			const vector3d &v2,
			const vector3d &v3,
			const int edgeLen,
			const double fracStep) const
		{
			vector3d *vts = vertices;
			vector3d *col = colors;
			double xfrac;
			double yfrac = 0;
			for (int y=0; y<edgeLen; y++) {
				xfrac = 0;
				for (int x=0; x<edgeLen; x++) {
					const vector3d p = GetSpherePoint(v0, v1, v2, v3, xfrac, yfrac);
					const double height = mData.pTerrain->GetHeight(p);
					*(vts++) = p * (height + 1.0);
					// remember this -- we will need it later
					(col++)->x = height;
					xfrac += fracStep;
				}
				yfrac += fracStep;
			}
			assert(vts == &vertices[mData.NUMVERTICES()]);
			// Generate normals & colors for non-edge vertices since they never change
			for (int y=1; y<edgeLen-1; y++) {
				for (int x=1; x<edgeLen-1; x++) {
					// normal
					const vector3d &x1 = vertices[x-1 + y*edgeLen];
					const vector3d &x2 = vertices[x+1 + y*edgeLen];
					const vector3d &y1 = vertices[x + (y-1)*edgeLen];
					const vector3d &y2 = vertices[x + (y+1)*edgeLen];

					const vector3d n = ((x2-x1).Cross(y2-y1)).Normalized();
					normals[x + y*edgeLen] = n;
					// color
					const vector3d p = GetSpherePoint(v0, v1, v2, v3, x*fracStep, y*fracStep);
					const double height = colors[x + y*edgeLen].x;
					vector3d &col_r = colors[x + y*edgeLen];
					col_r = mData.pTerrain->GetColor(p, height, n);
				}
			}
		}
	};
public:
	RefCountedPtr<GeoPatchContext> ctx;
	const vector3d v0, v1, v2, v3;
	vector3d *vertices;
	vector3d *normals;
	vector3d *colors;
	GLuint m_vbo;
	GeoPatch *kids[4];
	GeoPatch *parent;
	GeoPatch *edgeFriend[4]; // [0]=v01, [1]=v12, [2]=v20
	GeoSphere *geosphere;
	double m_roughLength;
	vector3d clipCentroid, centroid;
	double clipRadius;
	int m_depth;
	SDL_mutex *m_kidsLock;
	bool m_needUpdateVBOs;
	double m_distMult;

	const GeoPatchID mPatchID;
	bool mHasSplitRequest;
	uint8_t mCanMergeChildren;

	#pragma optimize( "", off )
	GeoPatch(const RefCountedPtr<GeoPatchContext> &_ctx, GeoSphere *gs, 
		const vector3d &v0_, const vector3d &v1_, const vector3d &v2_, const vector3d &v3_, 
		const int depth, const GeoPatchID &ID_) 
		: ctx(_ctx), v0(v0_), v1(v1_), v2(v2_), v3(v3_), 
		vertices(NULL), normals(NULL), colors(NULL), 
		m_vbo(0), parent(NULL), geosphere(gs), 
		m_depth(depth), mPatchID(ID_), 
		mHasSplitRequest(false), mCanMergeChildren(0x0F)
	{
		for (int i=0; i<4; ++i) {
			edgeFriend[i]	= NULL;
			kids[i]			= NULL;
		}
		m_kidsLock = SDL_CreateMutex();
		
		clipCentroid = (v0+v1+v2+v3) * 0.25;
		centroid = clipCentroid.Normalized();
		clipRadius = 0.0;
		clipRadius = std::max(clipRadius, (v0-clipCentroid).Length());
		clipRadius = std::max(clipRadius, (v1-clipCentroid).Length());
		clipRadius = std::max(clipRadius, (v2-clipCentroid).Length());
		clipRadius = std::max(clipRadius, (v3-clipCentroid).Length());
		if (geosphere->m_sbody->type < SystemBody::TYPE_PLANET_ASTEROID) {
 			m_distMult = 10 / Clamp(depth, 1, 10);
 		} else {
 			m_distMult = 5 / Clamp(depth, 1, 5);
 		}
		m_roughLength = GEOPATCH_SUBDIVIDE_AT_CAMDIST / pow(2.0, depth) * m_distMult;
		m_needUpdateVBOs = false;
	}

	~GeoPatch() {
		assert(!mHasSplitRequest);
		SDL_DestroyMutex(m_kidsLock);
		for (int i=0; i<4; i++) {
			if (edgeFriend[i]) edgeFriend[i]->NotifyEdgeFriendDeleted(this);
		}
		for (int i=0; i<4; i++) if (kids[i]) delete kids[i];
		delete[] vertices;
		delete[] normals;
		delete[] colors;
		glDeleteBuffersARB(1, &m_vbo);
	}

	void UpdateVBOs() {
		m_needUpdateVBOs = (NULL!=vertices);
	}

	void _UpdateVBOs() {
		if (m_needUpdateVBOs) {
			if (!m_vbo) glGenBuffersARB(1, &m_vbo);
			m_needUpdateVBOs = false;
			glBindBufferARB(GL_ARRAY_BUFFER, m_vbo);
			glBufferDataARB(GL_ARRAY_BUFFER, sizeof(VBOVertex)*ctx->NUMVERTICES(), 0, GL_DYNAMIC_DRAW);
			for (int i=0; i<ctx->NUMVERTICES(); i++)
			{
				clipRadius = std::max(clipRadius, (vertices[i]-clipCentroid).Length());
				VBOVertex *pData = ctx->vbotemp + i;
				pData->x = float(vertices[i].x - clipCentroid.x);
				pData->y = float(vertices[i].y - clipCentroid.y);
				pData->z = float(vertices[i].z - clipCentroid.z);
				pData->nx = float(normals[i].x);
				pData->ny = float(normals[i].y);
				pData->nz = float(normals[i].z);
				pData->col[0] = static_cast<unsigned char>(Clamp(colors[i].x*255.0, 0.0, 255.0));
				pData->col[1] = static_cast<unsigned char>(Clamp(colors[i].y*255.0, 0.0, 255.0));
				pData->col[2] = static_cast<unsigned char>(Clamp(colors[i].z*255.0, 0.0, 255.0));
				pData->col[3] = 255;
			}
			glBufferDataARB(GL_ARRAY_BUFFER, sizeof(VBOVertex)*ctx->NUMVERTICES(), ctx->vbotemp, GL_DYNAMIC_DRAW);
			glBindBufferARB(GL_ARRAY_BUFFER, 0);
		}
	}

	/* not quite edge, since we share edge vertices so that would be
	 * fucking pointless. one position inwards. used to make edge normals
	 * for adjacent tiles */
	void GetEdgeMinusOneVerticesFlipped(const int edge, vector3d *ev) const {
		if (edge == 0) {
			for (int x=0; x<ctx->edgeLen; x++) ev[ctx->edgeLen-1-x] = vertices[x + ctx->edgeLen];
		} else if (edge == 1) {
			const int x = ctx->edgeLen-2;
			for (int y=0; y<ctx->edgeLen; y++) ev[ctx->edgeLen-1-y] = vertices[x + y*ctx->edgeLen];
		} else if (edge == 2) {
			const int y = ctx->edgeLen-2;
			for (int x=0; x<ctx->edgeLen; x++) ev[ctx->edgeLen-1-x] = vertices[(ctx->edgeLen-1)-x + y*ctx->edgeLen];
		} else {
			for (int y=0; y<ctx->edgeLen; y++) ev[ctx->edgeLen-1-y] = vertices[1 + ((ctx->edgeLen-1)-y)*ctx->edgeLen];
		}
	}

	int GetEdgeIdxOf(const GeoPatch *e) const {
		for (int i=0; i<4; i++) {
			if (edgeFriend[i] == e) {
				return i;
			}
		}
		abort();
		return -1;
	}

	void FixEdgeNormals(const int edge, const vector3d *ev) {
		int x, y;
		switch (edge) {
		case 0:
			for (x=1; x<ctx->edgeLen-1; x++) {
				const vector3d &x1 = vertices[x-1];
				const vector3d &x2 = vertices[x+1];
				const vector3d &y1 = ev[x];
				const vector3d &y2 = vertices[x + ctx->edgeLen];
				const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
				normals[x] = norm;
				// make color
				const vector3d p = GetSpherePoint(x*ctx->frac, 0);
				const double height = colors[x].x;
				colors[x] = geosphere->GetColor(p, height, norm);
			}
			break;
		case 1:
			x = ctx->edgeLen-1;
			for (y=1; y<ctx->edgeLen-1; y++) {
				const vector3d &x1 = vertices[(x-1) + y*ctx->edgeLen];
				const vector3d &x2 = ev[y];
				const vector3d &y1 = vertices[x + (y-1)*ctx->edgeLen];
				const vector3d &y2 = vertices[x + (y+1)*ctx->edgeLen];
				const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
				normals[x + y*ctx->edgeLen] = norm;
				// make color
				const vector3d p = GetSpherePoint(x*ctx->frac, y*ctx->frac);
				const double height = colors[x + y*ctx->edgeLen].x;
				colors[x + y*ctx->edgeLen] = geosphere->GetColor(p, height, norm);
	//			colors[x+y*ctx->edgeLen] = vector3d(1,0,0);
			}
			break;
		case 2:
			y = ctx->edgeLen-1;
			for (x=1; x<ctx->edgeLen-1; x++) {
				const vector3d &x1 = vertices[x-1 + y*ctx->edgeLen];
				const vector3d &x2 = vertices[x+1 + y*ctx->edgeLen];
				const vector3d &y1 = vertices[x + (y-1)*ctx->edgeLen];
				const vector3d &y2 = ev[ctx->edgeLen-1-x];
				const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
				normals[x + y*ctx->edgeLen] = norm;
				// make color
				const vector3d p = GetSpherePoint(x*ctx->frac, y*ctx->frac);
				const double height = colors[x + y*ctx->edgeLen].x;
				colors[x + y*ctx->edgeLen] = geosphere->GetColor(p, height, norm);
			}
			break;
		case 3:
			for (y=1; y<ctx->edgeLen-1; y++) {
				const vector3d &x1 = ev[ctx->edgeLen-1-y];
				const vector3d &x2 = vertices[1 + y*ctx->edgeLen];
				const vector3d &y1 = vertices[(y-1)*ctx->edgeLen];
				const vector3d &y2 = vertices[(y+1)*ctx->edgeLen];
				const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
				normals[y*ctx->edgeLen] = norm;
				// make color
				const vector3d p = GetSpherePoint(0, y*ctx->frac);
				const double height = colors[y*ctx->edgeLen].x;
				colors[y*ctx->edgeLen] = geosphere->GetColor(p, height, norm);
	//			colors[y*ctx->edgeLen] = vector3d(0,1,0);
			}
			break;
		}
	}

	int GetChildIdx(const GeoPatch *child) const {
		for (int i=0; i<4; i++) {
			if (kids[i] == child) return i;
		}
		abort();
		return -1;
	}

	void FixEdgeFromParentInterpolated(const int edge) {
		// noticeable artefacts from not doing so...
		vector3d ev[GEOPATCH_MAX_EDGELEN];
		vector3d en[GEOPATCH_MAX_EDGELEN];
		vector3d ec[GEOPATCH_MAX_EDGELEN];
		vector3d ev2[GEOPATCH_MAX_EDGELEN];
		vector3d en2[GEOPATCH_MAX_EDGELEN];
		vector3d ec2[GEOPATCH_MAX_EDGELEN];
		ctx->GetEdge(parent->vertices, edge, ev);
		ctx->GetEdge(parent->normals, edge, en);
		ctx->GetEdge(parent->colors, edge, ec);

		int kid_idx = parent->GetChildIdx(this);
		if (edge == kid_idx) {
			// use first half of edge
			for (int i=0; i<=ctx->edgeLen/2; i++) {
				ev2[i<<1] = ev[i];
				en2[i<<1] = en[i];
				ec2[i<<1] = ec[i];
			}
		} else {
			// use 2nd half of edge
			for (int i=ctx->edgeLen/2; i<ctx->edgeLen; i++) {
				ev2[(i-(ctx->edgeLen/2))<<1] = ev[i];
				en2[(i-(ctx->edgeLen/2))<<1] = en[i];
				ec2[(i-(ctx->edgeLen/2))<<1] = ec[i];
			}
		}
		// interpolate!!
		for (int i=1; i<ctx->edgeLen; i+=2) {
			ev2[i] = (ev2[i-1]+ev2[i+1]) * 0.5;
			en2[i] = (en2[i-1]+en2[i+1]).Normalized();
			ec2[i] = (ec2[i-1]+ec2[i+1]) * 0.5;
		}
		ctx->SetEdge(this->vertices, edge, ev2);
		ctx->SetEdge(this->normals, edge, en2);
		ctx->SetEdge(this->colors, edge, ec2);
	}

	template <int corner>
	void MakeCornerNormal(const vector3d *ev, const vector3d *ev2) {
		switch (corner) {
		case 0: {
			const vector3d &x1 = ev[ctx->edgeLen-1];
			const vector3d &x2 = vertices[1];
			const vector3d &y1 = ev2[0];
			const vector3d &y2 = vertices[ctx->edgeLen];
			const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
			normals[0] = norm;
			// make color
			const vector3d pt = GetSpherePoint(0, 0);
		//	const double height = colors[0].x;
			const double height = geosphere->GetHeight(pt);
			colors[0] = geosphere->GetColor(pt, height, norm);
			}
			break;
		case 1: {
			const int p = ctx->edgeLen-1;
			const vector3d &x1 = vertices[p-1];
			const vector3d &x2 = ev2[0];
			const vector3d &y1 = ev[ctx->edgeLen-1];
			const vector3d &y2 = vertices[p + ctx->edgeLen];
			const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
			normals[p] = norm;
			// make color
			const vector3d pt = GetSpherePoint(p*ctx->frac, 0);
		//	const double height = colors[p].x;
			const double height = geosphere->GetHeight(pt);
			colors[p] = geosphere->GetColor(pt, height, norm);
			}
			break;
		case 2: {
			const int p = ctx->edgeLen-1;
			const vector3d &x1 = vertices[(p-1) + p*ctx->edgeLen];
			const vector3d &x2 = ev[ctx->edgeLen-1];
			const vector3d &y1 = vertices[p + (p-1)*ctx->edgeLen];
			const vector3d &y2 = ev2[0];
			const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
			normals[p + p*ctx->edgeLen] = norm;
			// make color
			const vector3d pt = GetSpherePoint(p*ctx->frac, p*ctx->frac);
		//	const double height = colors[p + p*ctx->edgeLen].x;
			const double height = geosphere->GetHeight(pt);
			colors[p + p*ctx->edgeLen] = geosphere->GetColor(pt, height, norm);
			}
			break;
		case 3: {
			const int p = ctx->edgeLen-1;
			const vector3d &x1 = ev2[0];
			const vector3d &x2 = vertices[1 + p*ctx->edgeLen];
			const vector3d &y1 = vertices[(p-1)*ctx->edgeLen];
			const vector3d &y2 = ev[ctx->edgeLen-1];
			const vector3d norm = (x2-x1).Cross(y2-y1).Normalized();
			normals[p*ctx->edgeLen] = norm;
			// make color
			const vector3d pt = GetSpherePoint(0, p*ctx->frac);
		//	const double height = colors[p*ctx->edgeLen].x;
			const double height = geosphere->GetHeight(pt);
			colors[p*ctx->edgeLen] = geosphere->GetColor(pt, height, norm);
			}
			break;
		}
	}

	void FixCornerNormalsByEdge(const int edge, const vector3d *ev) {
		vector3d ev2[GEOPATCH_MAX_EDGELEN];
		/* XXX All these 'if's have an unfinished else, when a neighbour
		 * of our size doesn't exist and instead we must look at a bigger tile.
		 * But let's just leave it for the mo because it is a pain.
		 * See comment in OnEdgeFriendChanged() */
		switch (edge) {
		case 0:
			if (edgeFriend[3]) {
				const int we_are = edgeFriend[3]->GetEdgeIdxOf(this);
				edgeFriend[3]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<0>(ev2, ev);
			}
			if (edgeFriend[1]) {
				const int we_are = edgeFriend[1]->GetEdgeIdxOf(this);
				edgeFriend[1]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<1>(ev, ev2);
			}
			break;
		case 1:
			if (edgeFriend[0]) {
				const int we_are = edgeFriend[0]->GetEdgeIdxOf(this);
				edgeFriend[0]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<1>(ev2, ev);
			}
			if (edgeFriend[2]) {
				const int we_are = edgeFriend[2]->GetEdgeIdxOf(this);
				edgeFriend[2]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<2>(ev, ev2);
			}
			break;
		case 2:
			if (edgeFriend[1]) {
				const int we_are = edgeFriend[1]->GetEdgeIdxOf(this);
				edgeFriend[1]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<2>(ev2, ev);
			}
			if (edgeFriend[3]) {
				const int we_are = edgeFriend[3]->GetEdgeIdxOf(this);
				edgeFriend[3]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<3>(ev, ev2);
			}
			break;
		case 3:
			if (edgeFriend[2]) {
				const int we_are = edgeFriend[2]->GetEdgeIdxOf(this);
				edgeFriend[2]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<3>(ev2, ev);
			}
			if (edgeFriend[0]) {
				const int we_are = edgeFriend[0]->GetEdgeIdxOf(this);
				edgeFriend[0]->GetEdgeMinusOneVerticesFlipped(we_are, ev2);
				MakeCornerNormal<0>(ev, ev2);
			}
			break;
		}

	}

	void GenerateEdgeNormalsAndColors() {
		vector3d ev[4][GEOPATCH_MAX_EDGELEN];
		bool doneEdge[4];
		memset(doneEdge, 0, sizeof(doneEdge));
		for (int i=0; i<4; i++) {
			GeoPatch *e = edgeFriend[i];
			if (e) {
				int we_are = e->GetEdgeIdxOf(this);
				e->GetEdgeMinusOneVerticesFlipped(we_are, ev[i]);
			} else if (parent && parent->edgeFriend[i]) {
				assert(parent->edgeFriend[i]);
				doneEdge[i] = true;
				// parent has valid edge, so take our
				// bit of that, interpolated.
				FixEdgeFromParentInterpolated(i);
				// XXX needed for corners... probably not
				// correct
				ctx->GetEdge(vertices, i, ev[i]);
			}
		}

		MakeCornerNormal<0>(ev[3], ev[0]);
		MakeCornerNormal<1>(ev[0], ev[1]);
		MakeCornerNormal<2>(ev[1], ev[2]);
		MakeCornerNormal<3>(ev[2], ev[3]);

		for (int i=0; i<4; i++) if(!doneEdge[i]) FixEdgeNormals(i, ev[i]);
	}

	/* in patch surface coords, [0,1] */
	vector3d GetSpherePoint(const double x, const double y) const {
		return (v0 + x*(1.0-y)*(v1-v0) + x*y*(v2-v0) + (1.0-x)*y*(v3-v0)).Normalized();
	}

	// Generates full-detail vertices, and also non-edge normals and colors
	void GenerateMesh() {
		centroid = clipCentroid.Normalized();
		centroid = (1.0 + geosphere->GetHeight(centroid)) * centroid;
		vector3d *vts = vertices;
		vector3d *col = colors;
		double xfrac;
		double yfrac = 0;
		for (int y=0; y<ctx->edgeLen; y++) {
			xfrac = 0;
			for (int x=0; x<ctx->edgeLen; x++) {
				vector3d p = GetSpherePoint(xfrac, yfrac);
				double height = geosphere->GetHeight(p);
				*(vts++) = p * (height + 1.0);
				// remember this -- we will need it later
				(col++)->x = height;
				xfrac += ctx->frac;
			}
			yfrac += ctx->frac;
		}
		assert(vts == &vertices[ctx->NUMVERTICES()]);
		// Generate normals & colors for non-edge vertices since they never change
		for (int y=1; y<ctx->edgeLen-1; y++) {
			for (int x=1; x<ctx->edgeLen-1; x++) {
				// normal
				const vector3d &x1 = vertices[x-1 + y*ctx->edgeLen];
				const vector3d &x2 = vertices[x+1 + y*ctx->edgeLen];
				const vector3d &y1 = vertices[x + (y-1)*ctx->edgeLen];
				const vector3d &y2 = vertices[x + (y+1)*ctx->edgeLen];

				const vector3d n = (x2-x1).Cross(y2-y1);
				normals[x + y*ctx->edgeLen] = n.Normalized();
				// color
				const vector3d p = GetSpherePoint(x*ctx->frac, y*ctx->frac);
				vector3d &col_r = colors[x + y*ctx->edgeLen];
				const double height = col_r.x;
				const vector3d &norm = normals[x + y*ctx->edgeLen];
				col_r = geosphere->GetColor(p, height, norm);
			}
		}
	}
	void OnEdgeFriendChanged(const int edge, GeoPatch *e) {
		edgeFriend[edge] = e;
		vector3d ev[GEOPATCH_MAX_EDGELEN];
		const int we_are = e->GetEdgeIdxOf(this);
		e->GetEdgeMinusOneVerticesFlipped(we_are, ev);
		/* now we have a valid edge, fix the edge vertices */
		if (edge == 0) {
			for (int x=0; x<ctx->edgeLen; x++) {
				const vector3d p = GetSpherePoint(x * ctx->frac, 0);
				const double height = geosphere->GetHeight(p);
				vertices[x] = p * (height + 1.0);
				// XXX These bounds checks in each edge case are
				// only necessary while the "All these 'if's"
				// comment in FixCornerNormalsByEdge stands
				if ((x>0) && (x<ctx->edgeLen-1)) {
					colors[x].x = height;
				}
			}
		} else if (edge == 1) {
			for (int y=0; y<ctx->edgeLen; y++) {
				const vector3d p = GetSpherePoint(1.0, y * ctx->frac);
				const double height = geosphere->GetHeight(p);
				const int pos = (ctx->edgeLen-1) + y*ctx->edgeLen;
				vertices[pos] = p * (height + 1.0);
				if ((y>0) && (y<ctx->edgeLen-1)) {
					colors[pos].x = height;
				}
			}
		} else if (edge == 2) {
			for (int x=0; x<ctx->edgeLen; x++) {
				const vector3d p = GetSpherePoint(x * ctx->frac, 1.0);
				const double height = geosphere->GetHeight(p);
				const int pos = x + (ctx->edgeLen-1)*ctx->edgeLen;
				vertices[pos] = p * (height + 1.0);
				if ((x>0) && (x<ctx->edgeLen-1)) {
					colors[pos].x = height;
				}
			}
		} else {
			for (int y=0; y<ctx->edgeLen; y++) {
				const vector3d p = GetSpherePoint(0, y * ctx->frac);
				const double height = geosphere->GetHeight(p);
				const int pos = y * ctx->edgeLen;
				vertices[pos] = p * (height + 1.0);
				if ((y>0) && (y<ctx->edgeLen-1)) {
					colors[pos].x = height;
				}
			}
		}

		FixEdgeNormals(edge, ev);
		FixCornerNormalsByEdge(edge, ev);
		UpdateVBOs();

		if (kids[0]) {
			if (edge == 0) {
				kids[0]->FixEdgeFromParentInterpolated(0);
				kids[0]->UpdateVBOs();
				kids[1]->FixEdgeFromParentInterpolated(0);
				kids[1]->UpdateVBOs();
			} else if (edge == 1) {
				kids[1]->FixEdgeFromParentInterpolated(1);
				kids[1]->UpdateVBOs();
				kids[2]->FixEdgeFromParentInterpolated(1);
				kids[2]->UpdateVBOs();
			} else if (edge == 2) {
				kids[2]->FixEdgeFromParentInterpolated(2);
				kids[2]->UpdateVBOs();
				kids[3]->FixEdgeFromParentInterpolated(2);
				kids[3]->UpdateVBOs();
			} else {
				kids[3]->FixEdgeFromParentInterpolated(3);
				kids[3]->UpdateVBOs();
				kids[0]->FixEdgeFromParentInterpolated(3);
				kids[0]->UpdateVBOs();
			}
		}
	}

	void NotifyEdgeFriendSplit(GeoPatch *e) {
		if (!kids[0]) {return;}
		const int idx = GetEdgeIdxOf(e);
		const int we_are = e->GetEdgeIdxOf(this);
		// match e's new kids to our own... :/
		kids[idx]->OnEdgeFriendChanged(idx, e->kids[(we_are+1)%4]);
		kids[(idx+1)%4]->OnEdgeFriendChanged(idx, e->kids[we_are]);
	}

	void NotifyEdgeFriendDeleted(const GeoPatch *e) {
		const int idx = GetEdgeIdxOf(e);
		assert(idx>=0 && idx<4);
		edgeFriend[idx] = NULL;
		if (!parent) return;
		if (parent->edgeFriend[idx]) {
			FixEdgeFromParentInterpolated(idx);
			UpdateVBOs();
		} else {
			// XXX TODO XXX
			// Bad. not fixing up edges in this case!!!
		}
	}

	GeoPatch *GetEdgeFriendForKid(const int kid, const int edge) const {
		const GeoPatch *e = edgeFriend[edge];
		if (!e) return NULL;
		//assert (e);// && (e->m_depth >= m_depth));
		const int we_are = e->GetEdgeIdxOf(this);
		// neighbour patch has not split yet (is at depth of this patch), so kids of this patch do
		// not have same detail level neighbours yet
		if (edge == kid) return e->kids[(we_are+1)%4];
		else return e->kids[we_are];
	}

	GLuint determineIndexbuffer() const {
		return // index buffers are ordered by edge resolution flags
			(edgeFriend[0] ? 1u : 0u) |
			(edgeFriend[1] ? 2u : 0u) |
			(edgeFriend[2] ? 4u : 0u) |
			(edgeFriend[3] ? 8u : 0u);
	}

	void Render(vector3d &campos, const Graphics::Frustum &frustum) {
		PiVerify(SDL_mutexP(m_kidsLock)==0);
		if (kids[0]) {
			for (int i=0; i<4; i++) kids[i]->Render(campos, frustum);
			SDL_mutexV(m_kidsLock);
		} else if (NULL!=vertices) {
			SDL_mutexV(m_kidsLock);
			_UpdateVBOs();

			if (!frustum.TestPoint(clipCentroid, clipRadius))
				return;

			vector3d relpos = clipCentroid - campos;
			glPushMatrix();
			glTranslated(relpos.x, relpos.y, relpos.z);

			Pi::statSceneTris += 2*(ctx->edgeLen-1)*(ctx->edgeLen-1);
			glEnableClientState(GL_VERTEX_ARRAY);
			glEnableClientState(GL_NORMAL_ARRAY);
			glEnableClientState(GL_COLOR_ARRAY);

			// update the indices used for rendering
			ctx->updateIndexBufferId(determineIndexbuffer());

			glBindBufferARB(GL_ARRAY_BUFFER, m_vbo);
			glVertexPointer(3, GL_FLOAT, sizeof(VBOVertex), 0);
			glNormalPointer(GL_FLOAT, sizeof(VBOVertex), reinterpret_cast<void *>(3*sizeof(float)));
			glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VBOVertex), reinterpret_cast<void *>(6*sizeof(float)));
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, ctx->indices_vbo);
			glDrawElements(GL_TRIANGLES, ctx->indices_tri_count*3, GL_UNSIGNED_SHORT, 0);
			glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
			glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER, 0);

			glDisableClientState(GL_VERTEX_ARRAY);
			glDisableClientState(GL_NORMAL_ARRAY);
			glDisableClientState(GL_COLOR_ARRAY);
			glPopMatrix();
		}
	}

	inline bool canBeMerged() const {
		bool merge = !(mHasSplitRequest);
		if (merge && kids[0]) {
			for (int i=0; i<4; i++) {
				merge &= kids[i]->canBeMerged();
			}
		}
		return merge;
	}

	void LODUpdate(const vector3d &campos) {
		// there should be no LODUpdate'ing when we have active split requests
		if(mHasSplitRequest)
			return;

		bool canSplit = true;
		bool canMerge = (NULL!=kids[0]) && (0==mCanMergeChildren);
		if (canMerge) {
			for (int i=0; i<4; i++) { 
				canMerge &= kids[i]->canBeMerged();		
			}
		}

		// always split at first level
		if (parent) {
			for (int i=0; i<4; i++) {
				if (!edgeFriend[i]) { 
					canSplit = false; 
					break; 
				} else if (edgeFriend[i]->m_depth < m_depth) {
					canSplit = false;
					break;
				}
			}
			const float centroidDist = (campos - centroid).Length();
			const bool errorSplit = (centroidDist < m_roughLength);
			if( !(canSplit && (m_depth < GEOPATCH_MAX_DEPTH) && errorSplit) ) 
			{
				canSplit = false;
			}
		}

		if (canSplit) {
			if (!kids[0]) {
				// don't do anything if we can't handle anymore jobs
				if( !Pi::jobs.canAddJob() ) {
					return;
				}

				mHasSplitRequest = true;
				if(parent) {
					// set the bit flag preventing merging
					parent->mCanMergeChildren |= 1<<mPatchID.GetPatchIdx(m_depth);
				}
				SSplitRequestDescription ssrd(v0, v1, v2, v3, centroid.Normalized(), m_depth,
							geosphere->m_sbody->path, mPatchID, ctx->edgeLen,
							ctx->frac, geosphere->m_terrain, geosphere);
				Pi::jobs.addJob(new PatchJob(ssrd), NULL);
			} else {
				for (int i=0; i<4; i++) {
					kids[i]->LODUpdate(campos);
				}
			}
		} else if (canMerge) {
			PiVerify(SDL_mutexP(m_kidsLock)==0);
			for (int i=0; i<4; i++) { 
				delete kids[i]; 
				kids[i] = NULL; 
			}
			PiVerify(SDL_mutexV(m_kidsLock)!=-1);
		}
	}
	
	#pragma optimize( "", off )
	void ReceiveHeightmaps(const SSplitResult *psr)
	{
		if (m_depth<psr->depth) {
			// this should work because each depth should have a common history
			const uint32_t kidIdx = psr->data[0].patchID.GetPatchIdx(m_depth+1);
			kids[kidIdx]->ReceiveHeightmaps(psr);
		} else {
			const int nD = m_depth+1;
			for (int i=0; i<4; i++)
			{
				kids[i] = new GeoPatch(ctx, geosphere, 
					psr->data[i].v0, psr->data[i].v1, psr->data[i].v2, psr->data[i].v3, 
					nD, mPatchID.NextPatchID(nD,i));
			}

			// hm.. edges. Not right to pass this
			// edgeFriend...
			kids[0]->edgeFriend[0] = GetEdgeFriendForKid(0, 0);
			kids[0]->edgeFriend[1] = kids[1];
			kids[0]->edgeFriend[2] = kids[3];
			kids[0]->edgeFriend[3] = GetEdgeFriendForKid(0, 3);
			kids[1]->edgeFriend[0] = GetEdgeFriendForKid(1, 0);
			kids[1]->edgeFriend[1] = GetEdgeFriendForKid(1, 1);
			kids[1]->edgeFriend[2] = kids[2];
			kids[1]->edgeFriend[3] = kids[0];
			kids[2]->edgeFriend[0] = kids[1];
			kids[2]->edgeFriend[1] = GetEdgeFriendForKid(2, 1);
			kids[2]->edgeFriend[2] = GetEdgeFriendForKid(2, 2);
			kids[2]->edgeFriend[3] = kids[3];
			kids[3]->edgeFriend[0] = kids[0];
			kids[3]->edgeFriend[1] = kids[2];
			kids[3]->edgeFriend[2] = GetEdgeFriendForKid(3, 2);
			kids[3]->edgeFriend[3] = GetEdgeFriendForKid(3, 3);
			kids[0]->parent = kids[1]->parent = kids[2]->parent = kids[3]->parent = this;

			for (int i=0; i<4; i++)
			{
				kids[i]->vertices = psr->data[i].vertices;
				kids[i]->normals = psr->data[i].normals;
				kids[i]->colors = psr->data[i].colors;
			}
			PiVerify(SDL_mutexP(m_kidsLock)==0);
			for (int i=0; i<4; i++) { if(edgeFriend[i]) edgeFriend[i]->NotifyEdgeFriendSplit(this); }
			for (int i=0; i<4; i++) {
				kids[i]->GenerateEdgeNormalsAndColors();
				kids[i]->UpdateVBOs();
			}
			PiVerify(SDL_mutexV(m_kidsLock)!=-1);
			mHasSplitRequest = false;
			if(parent) {
				// remove the bit flag
				parent->mCanMergeChildren &= ~(1<<mPatchID.GetPatchIdx(m_depth));
			}
		}
	}
};

static const int geo_sphere_edge_friends[6][4] = {
	{ 3, 4, 1, 2 },
	{ 0, 4, 5, 2 },
	{ 0, 1, 5, 3 },
	{ 0, 2, 5, 4 },
	{ 0, 3, 5, 1 },
	{ 1, 4, 3, 2 }
};

static std::vector<GeoSphere*> s_allGeospheres;

static bool s_exitFlag = false;

void GeoSphere::Init()
{
	s_patchContext.Reset(new GeoPatchContext(detail_edgeLen[Pi::detail.planets > 4 ? 4 : Pi::detail.planets]));
	assert(s_patchContext->edgeLen <= GEOPATCH_MAX_EDGELEN);
}

void GeoSphere::Uninit()
{
	assert (s_patchContext.Unique());
	s_patchContext.Reset();
}

static void print_info(const SystemBody *sbody, const Terrain *terrain)
{
	printf(
		"%s:\n"
		"    height fractal: %s\n"
		"    colour fractal: %s\n"
		"    seed: %u\n",
		sbody->name.c_str(), terrain->GetHeightFractalName(), terrain->GetColorFractalName(), sbody->seed);
}

void GeoSphere::OnChangeDetailLevel()
{
	s_patchContext.Reset(new GeoPatchContext(detail_edgeLen[Pi::detail.planets > 4 ? 4 : Pi::detail.planets]));
	assert(s_patchContext->edgeLen <= GEOPATCH_MAX_EDGELEN);

	// reinit the geosphere terrain data
	for(std::vector<GeoSphere*>::iterator i = s_allGeospheres.begin(); i != s_allGeospheres.end(); ++i) 
	{
		for (int p=0; p<6; p++) {
			// delete patches
			if ((*i)->m_patches[p]) {
				delete (*i)->m_patches[p];
				(*i)->m_patches[p] = 0;
			}
		}

		// reinit the terrain with the new settings
		delete (*i)->m_terrain;
		(*i)->m_terrain = Terrain::InstanceTerrain((*i)->m_sbody);
		print_info((*i)->m_sbody, (*i)->m_terrain);
	}
}

#define GEOSPHERE_TYPE	(m_sbody->type)

GeoSphere::GeoSphere(const SystemBody *body)
{
	m_terrain = Terrain::InstanceTerrain(body);
	print_info(body, m_terrain);

	m_sbody = body;
	memset(m_patches, 0, 6*sizeof(GeoPatch*));

	m_splitResultLock = SDL_CreateMutex();

	s_allGeospheres.push_back(this);

	//SetUpMaterials is not called until first Render since light count is zero :)
}

GeoSphere::~GeoSphere()
{
	// update thread should not be able to access us now, so we can safely continue to delete
	assert(std::count(s_allGeospheres.begin(), s_allGeospheres.end(), this) == 1);
	s_allGeospheres.erase(std::find(s_allGeospheres.begin(), s_allGeospheres.end(), this));

	SDL_DestroyMutex(m_splitResultLock);

	for (int i=0; i<6; i++) if (m_patches[i]) delete m_patches[i];

	delete m_terrain;
}

/*bool GeoSphere::AddSplitRequest(SSplitRequestDescription *desc)
{
	assert(mSplitRequestDescriptions.size()<MAX_SPLIT_OPERATIONS);
	if(mSplitRequestDescriptions.size()<MAX_SPLIT_OPERATIONS) {
		mSplitRequestDescriptions.push_back(desc);
		return true;
	}
	return false;
}

void GeoSphere::ProcessSplitRequests()
{
	std::deque<SSplitRequestDescription*>::const_iterator iter = mSplitRequestDescriptions.begin();
	while (iter!=mSplitRequestDescriptions.end())
	{
		const SSplitRequestDescription* srd = (*iter);

		const vector3f v01	= (srd->v0+srd->v1).Normalized();
		const vector3f v12	= (srd->v1+srd->v2).Normalized();
		const vector3f v23	= (srd->v2+srd->v3).Normalized();
		const vector3f v30	= (srd->v3+srd->v0).Normalized();
		const vector3f cn	= (srd->centroid).Normalized();

		// 
		const vector3f vecs[4][4] = {
			{srd->v0,	v01,		cn,			v30},
			{v01,		srd->v1,	v12,		cn},
			{cn,		v12,		srd->v2,	v23},
			{v30,		cn,			v23,		srd->v3}
		};

		SSplitResult *sr = new SSplitResult(srd->patchID.GetPatchFaceIdx(), srd->depth);
		for (int i=0; i<4; i++)
		{
			//Graphics::Texture *pTex = Graphics::TextureBuilder::TerrainGen("TerrainGen").CreateTexture(Pi::renderer);
			Graphics::TextureDescriptor td(Graphics::TEXTURE_FLOAT, vector2f(sPatchContext->fboWidth(), sPatchContext->fboWidth()), Graphics::NEAREST_CLAMP, false, false);
			Graphics::Texture *pTex = Pi::renderer->CreateTexture(td);

			// render the heightmap to a framebuffer.
			mPatchGenData->v0 = vecs[i][0];
			mPatchGenData->v1 = vecs[i][1];
			mPatchGenData->v2 = vecs[i][2];
			mPatchGenData->v3 = vecs[i][3];

			Graphics::TextureGL* pTexGL = static_cast<Graphics::TextureGL*>(pTex);
			sPatchContext->renderHeightmap(0, mPatchGenData, pTexGL->GetTextureNum());

			sr->addResult(pTex, vecs[i][0], vecs[i][1], vecs[i][2], vecs[i][3], srd->patchID.NextPatchID(srd->depth+1, i));
		}

		// store result
		mSplitResult.push_back( sr );

		// cleanup after ourselves
		delete srd;

		// next!
		++iter;
	}
	mSplitRequestDescriptions.clear();
}*/

bool GeoSphere::AddSplitResult(SSplitResult *res)
{
	bool result = false;
	SDL_mutexP(m_splitResultLock);
	assert(mSplitResult.size()<MAX_SPLIT_OPERATIONS);
	if(mSplitResult.size()<MAX_SPLIT_OPERATIONS) {
		mSplitResult.push_back(res);
		result = true;
	}
	SDL_mutexV(m_splitResultLock);
	return result;
}

void GeoSphere::ProcessSplitResults()
{
	SDL_mutexP(m_splitResultLock);
	std::deque<SSplitResult*>::const_iterator iter = mSplitResult.begin();
	while(iter!=mSplitResult.end())
	{
		// finally pass SplitResults
		const SSplitResult *psr = (*iter);

		const int32_t faceIdx = psr->face;
		m_patches[faceIdx]->ReceiveHeightmaps(psr);

		// tidyup
		delete psr;

		// Next!
		++iter;
	}
	mSplitResult.clear();
	SDL_mutexV(m_splitResultLock);
}

#pragma optimize( "", off )
void GeoSphere::BuildFirstPatches()
{
	assert(NULL==m_patches[0]);
	// generate root face patches of the cube/sphere
	static const vector3d p1 = (vector3d( 1, 1, 1)).Normalized();
	static const vector3d p2 = (vector3d(-1, 1, 1)).Normalized();
	static const vector3d p3 = (vector3d(-1,-1, 1)).Normalized();
	static const vector3d p4 = (vector3d( 1,-1, 1)).Normalized();
	static const vector3d p5 = (vector3d( 1, 1,-1)).Normalized();
	static const vector3d p6 = (vector3d(-1, 1,-1)).Normalized();
	static const vector3d p7 = (vector3d(-1,-1,-1)).Normalized();
	static const vector3d p8 = (vector3d( 1,-1,-1)).Normalized();

	const uint64_t maxShiftDepth = GeoPatchID::MAX_SHIFT_DEPTH;

	m_patches[0] = new GeoPatch(s_patchContext, this, p1, p2, p3, p4, 0, (0i64 << maxShiftDepth));
	m_patches[1] = new GeoPatch(s_patchContext, this, p4, p3, p7, p8, 0, (1i64 << maxShiftDepth));
	m_patches[2] = new GeoPatch(s_patchContext, this, p1, p4, p8, p5, 0, (2i64 << maxShiftDepth));
	m_patches[3] = new GeoPatch(s_patchContext, this, p2, p1, p5, p6, 0, (3i64 << maxShiftDepth));
	m_patches[4] = new GeoPatch(s_patchContext, this, p3, p2, p6, p7, 0, (4i64 << maxShiftDepth));
	m_patches[5] = new GeoPatch(s_patchContext, this, p8, p7, p6, p5, 0, (5i64 << maxShiftDepth));
	for (int i=0; i<6; i++) {
		for (int j=0; j<4; j++) {
			m_patches[i]->edgeFriend[j] = m_patches[geo_sphere_edge_friends[i][j]];
		}
	}
	for (int i=0; i<6; i++) {
		m_patches[i]->vertices = new vector3d[s_patchContext->NUMVERTICES()];
		m_patches[i]->normals = new vector3d[s_patchContext->NUMVERTICES()];
		m_patches[i]->colors = new vector3d[s_patchContext->NUMVERTICES()];
	}
	for (int i=0; i<6; i++) m_patches[i]->GenerateMesh();
	for (int i=0; i<6; i++) m_patches[i]->GenerateEdgeNormalsAndColors();
	for (int i=0; i<6; i++) m_patches[i]->UpdateVBOs();
}

static const float g_ambient[4] = { 0, 0, 0, 1.0 };

static void DrawAtmosphereSurface(Graphics::Renderer *renderer,
	const vector3d &campos, float rad, Graphics::Material *mat)
{
	const int LAT_SEGS = 20;
	const int LONG_SEGS = 20;
	vector3d yaxis = campos.Normalized();
	vector3d zaxis = vector3d(1.0,0.0,0.0).Cross(yaxis).Normalized();
	vector3d xaxis = yaxis.Cross(zaxis);
	const matrix4x4d m = matrix4x4d::MakeRotMatrix(xaxis, yaxis, zaxis).InverseOf();

	glPushMatrix();
	glScalef(rad, rad, rad);
	glMultMatrixd(&m[0]);

	// what is this? Well, angle to the horizon is:
	// acos(planetRadius/viewerDistFromSphereCentre)
	// and angle from this tangent on to atmosphere is:
	// acos(planetRadius/atmosphereRadius) ie acos(1.0/1.01244blah)
	double endAng = acos(1.0/campos.Length())+acos(1.0/rad);
	double latDiff = endAng / double(LAT_SEGS);

	double rot = 0.0;
	float sinCosTable[LONG_SEGS+1][2];
	for (int i=0; i<=LONG_SEGS; i++, rot += 2.0*M_PI/double(LONG_SEGS)) {
		sinCosTable[i][0] = float(sin(rot));
		sinCosTable[i][1] = float(cos(rot));
	}

	/* Tri-fan above viewer */
	Graphics::VertexArray va(Graphics::ATTRIB_POSITION);
	va.Add(vector3f(0.f, 1.f, 0.f));
	for (int i=0; i<=LONG_SEGS; i++) {
		va.Add(vector3f(
			sin(latDiff)*sinCosTable[i][0],
			cos(latDiff),
			-sin(latDiff)*sinCosTable[i][1]));
	}
	renderer->DrawTriangles(&va, mat, Graphics::TRIANGLE_FAN);

	/* and wound latitudinal strips */
	double lat = latDiff;
	for (int j=1; j<LAT_SEGS; j++, lat += latDiff) {
		Graphics::VertexArray v(Graphics::ATTRIB_POSITION);
		float cosLat = cos(lat);
		float sinLat = sin(lat);
		float cosLat2 = cos(lat+latDiff);
		float sinLat2 = sin(lat+latDiff);
		for (int i=0; i<=LONG_SEGS; i++) {
			v.Add(vector3f(sinLat*sinCosTable[i][0], cosLat, -sinLat*sinCosTable[i][1]));
			v.Add(vector3f(sinLat2*sinCosTable[i][0], cosLat2, -sinLat2*sinCosTable[i][1]));
		}
		renderer->DrawTriangles(&v, mat, Graphics::TRIANGLE_STRIP);
	}

	glPopMatrix();
}

void GeoSphere::Update()
{
	if(NULL==m_patches[0] && mSplitResult.empty()) {
		BuildFirstPatches();
	} else if(mSplitRequestDescriptions.empty()) {
		ProcessSplitResults();
		for (int i=0; i<6; i++) {
			m_patches[i]->LODUpdate(m_tempCampos);
		}
	}
}

void GeoSphere::Render(Graphics::Renderer *renderer, vector3d campos, const float radius, const float scale) 
{
	if(NULL==m_patches[0]) {
		return;
	}

	glPushMatrix();
	glTranslated(-campos.x, -campos.y, -campos.z);
	Graphics::Frustum frustum = Graphics::Frustum::FromGLState();

	// no frustum test of entire geosphere, since Space::Render does this
	// for each body using its GetBoundingRadius() value

	//First draw - create materials (they do not change afterwards)
	if (!m_surfaceMaterial.Valid())
		SetUpMaterials();

	if (Graphics::AreShadersEnabled()) {
		matrix4x4d modelMatrix;
		glGetDoublev (GL_MODELVIEW_MATRIX, &modelMatrix[0]);

		//Update material parameters
		//XXX no need to calculate AP every frame
		m_atmosphereParameters = m_sbody->CalcAtmosphereParams();
		m_atmosphereParameters.center = modelMatrix * vector3d(0.0, 0.0, 0.0);
		m_atmosphereParameters.planetRadius = radius;
		m_atmosphereParameters.scale = scale;

		m_surfaceMaterial->specialParameter0 = &m_atmosphereParameters;

		if (m_atmosphereParameters.atmosDensity > 0.0) {
			m_atmosphereMaterial->specialParameter0 = &m_atmosphereParameters;

			renderer->SetBlendMode(Graphics::BLEND_ALPHA_ONE);
			renderer->SetDepthWrite(false);
			// make atmosphere sphere slightly bigger than required so
			// that the edges of the pixel shader atmosphere jizz doesn't
			// show ugly polygonal angles
			DrawAtmosphereSurface(renderer, campos, m_atmosphereParameters.atmosRadius*1.01, m_atmosphereMaterial.Get());
			renderer->SetDepthWrite(true);
			renderer->SetBlendMode(Graphics::BLEND_SOLID);
		}
	}
	glPopMatrix();

	Color ambient;
	Color &emission = m_surfaceMaterial->emissive;

	// save old global ambient
	const Color oldAmbient = renderer->GetAmbientColor();

	if ((m_sbody->GetSuperType() == SystemBody::SUPERTYPE_STAR) || (m_sbody->type == SystemBody::TYPE_BROWN_DWARF)) {
		// stars should emit light and terrain should be visible from distance
		ambient.r = ambient.g = ambient.b = 0.2f;
		ambient.a = 1.0f;
		emission.r = StarSystem::starRealColors[m_sbody->type][0];
		emission.g = StarSystem::starRealColors[m_sbody->type][1];
		emission.b = StarSystem::starRealColors[m_sbody->type][2];
		emission.a = 1.f;
	}

	else {
		// give planet some ambient lighting if the viewer is close to it
		double camdist = campos.Length();
		camdist = 0.1 / (camdist*camdist);
		// why the fuck is this returning 0.1 when we are sat on the planet??
		// JJ: Because campos is relative to a unit-radius planet - 1.0 at the surface
		// XXX oh well, it is the value we want anyway...
		ambient.r = ambient.g = ambient.b = float(camdist);
		ambient.a = 1.0f;
	}

	renderer->SetAmbientColor(ambient);
	// this is pretty much the only place where a non-renderer is allowed to call Apply()
	// to be removed when someone rewrites terrain
	m_surfaceMaterial->Apply();

	for (int i=0; i<6; i++) {
		m_patches[i]->Render(campos, frustum);
	}

	m_surfaceMaterial->Unapply();

	renderer->SetAmbientColor(oldAmbient);

	// store this for later usage in the update method.
	m_tempCampos = campos;
}

void GeoSphere::SetUpMaterials()
{
	// Request material for this star or planet, with or without
	// atmosphere. Separate material for surface and sky.
	Graphics::MaterialDescriptor surfDesc;
	const Uint32 effect_flags = m_terrain->GetSurfaceEffects();
	if (effect_flags & Terrain::EFFECT_LAVA)
		surfDesc.effect = Graphics::EFFECT_GEOSPHERE_TERRAIN_WITH_LAVA;
	else if (effect_flags & Terrain::EFFECT_WATER)
		surfDesc.effect = Graphics::EFFECT_GEOSPHERE_TERRAIN_WITH_WATER;
	else
		surfDesc.effect = Graphics::EFFECT_GEOSPHERE_TERRAIN;

	if ((m_sbody->type == SystemBody::TYPE_BROWN_DWARF) ||
		(m_sbody->type == SystemBody::TYPE_STAR_M)) {
		//dim star (emits and receives light)
		surfDesc.lighting = true;
		surfDesc.atmosphere = false;
	}
	else if (m_sbody->GetSuperType() == SystemBody::SUPERTYPE_STAR) {
		//normal star
		surfDesc.lighting = false;
		surfDesc.atmosphere = false;
	} else {
		//planetoid with or without atmosphere
		const SystemBody::AtmosphereParameters ap(m_sbody->CalcAtmosphereParams());
		surfDesc.lighting = true;
		surfDesc.atmosphere = (ap.atmosDensity > 0.0);
	}
	m_surfaceMaterial.Reset(Pi::renderer->CreateMaterial(surfDesc));

	//Shader-less atmosphere is drawn in Planet
	if (Graphics::AreShadersEnabled()) {
		Graphics::MaterialDescriptor skyDesc;
		skyDesc.effect = Graphics::EFFECT_GEOSPHERE_SKY;
		skyDesc.lighting = true;
		m_atmosphereMaterial.Reset(Pi::renderer->CreateMaterial(skyDesc));
	}
}
