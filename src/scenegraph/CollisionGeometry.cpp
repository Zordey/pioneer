<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "CollisionGeometry.h"
#include "NodeVisitor.h"
#include "graphics/Surface.h"
<<<<<<< HEAD

namespace SceneGraph {

CollisionGeometry::CollisionGeometry(Graphics::Renderer *r, Graphics::Surface *s, unsigned int geomflag)
: Node(r)
, m_triFlag(geomflag)
=======
#include "NodeCopyCache.h"

namespace SceneGraph {
CollisionGeometry::CollisionGeometry(Graphics::Renderer *r, Graphics::Surface *s, unsigned int geomflag)
: Node(r)
, m_triFlag(geomflag)
, m_dynamic(false)
, m_geomTree(0)
, m_geom(0)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	CopyData(s->GetVertices()->position, s->GetIndices());
}

CollisionGeometry::CollisionGeometry(Graphics::Renderer *r, const std::vector<vector3f> &vts, const std::vector<unsigned short> &idx,
	unsigned int geomflag)
: Node(r)
, m_triFlag(geomflag)
<<<<<<< HEAD
=======
, m_dynamic(false)
, m_geomTree(0)
, m_geom(0)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	CopyData(vts, idx);
}

CollisionGeometry::CollisionGeometry(const CollisionGeometry &cg, NodeCopyCache *cache)
: Node(cg, cache)
, m_vertices(cg.m_vertices)
, m_indices(cg.m_indices)
, m_triFlag(cg.m_triFlag)
<<<<<<< HEAD
=======
, m_dynamic(cg.m_dynamic)
, m_geomTree(cg.m_geomTree)
, m_geom(cg.m_geom)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
}

CollisionGeometry::~CollisionGeometry()
{
}

Node* CollisionGeometry::Clone(NodeCopyCache *cache)
{
<<<<<<< HEAD
	return this; //collgeoms are shared
=======
	//static collgeoms are shared,
	//dynamic geoms are copied (they should be tiny)
	if (IsDynamic())
		return cache->Copy<CollisionGeometry>(this);
	else
		return this;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void CollisionGeometry::Accept(NodeVisitor &nv)
{
	nv.ApplyCollisionGeometry(*this);
}

void CollisionGeometry::CopyData(const std::vector<vector3f> &vts, const std::vector<unsigned short> &idx)
{
	//copy vertices and indices from surface. Add flag for every three indices.
	using std::vector;

	for (vector<vector3f>::const_iterator it = vts.begin(); it != vts.end(); ++it)
		m_vertices.push_back(*it);

	for (vector<unsigned short>::const_iterator it = idx.begin(); it != idx.end(); ++it)
		m_indices.push_back(*it);
}
<<<<<<< HEAD

}
=======
}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
