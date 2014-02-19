<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _COLLMESH_H
#define _COLLMESH_H
#include "RefCounted.h"
#include "Aabb.h"
#include "collider/GeomTree.h"

<<<<<<< HEAD
class CollMesh : public RefCounted {
public:
	CollMesh() : m_geomTree(0) { }
	virtual ~CollMesh() {
		delete m_geomTree;
	}
	virtual Aabb &GetAabb() { return m_aabb; }
	virtual double GetRadius() const { return m_aabb.GetRadius(); }
	virtual void SetRadius(double v) { m_aabb.radius = std::max(v, 0.1); } //0 radius = trouble
	virtual GeomTree *GetGeomTree() const { return m_geomTree; }
	void SetGeomTree(GeomTree *t) { m_geomTree = t; }

	std::vector<vector3f> m_vertices;
	std::vector<int> m_indices; //XXX should be unsigned!!
	std::vector<unsigned int> m_flags; //1 per triangle
=======
//This simply stores the collision GeomTrees
//and AABB.
class CollMesh : public RefCounted {
public:
	CollMesh()
	: m_geomTree(0)
	, m_totalTris(0)
	{ }
	virtual ~CollMesh() {
		for (auto it = m_dynGeomTrees.begin(); it != m_dynGeomTrees.end(); ++it)
			delete *it;
		delete m_geomTree;
	}
	virtual Aabb &GetAabb() { return m_aabb; }

	virtual double GetRadius() const { return m_aabb.GetRadius(); }
	virtual void SetRadius(double v) {
		//0 radius = trouble
		m_aabb.radius = std::max(v, 0.1);
	}

	virtual GeomTree *GetGeomTree() const { return m_geomTree; }
	void SetGeomTree(GeomTree *t) {
		assert(t);
		m_geomTree = t;
	}

	const std::vector<GeomTree*> &GetDynGeomTrees() const { return m_dynGeomTrees; }
	void AddDynGeomTree(GeomTree *t) {
		assert(t);
		m_dynGeomTrees.push_back(t);
	}

	//for statistics
	unsigned int GetNumTriangles() const { return m_totalTris; }
	void SetNumTriangles(unsigned int i) { m_totalTris = i; }
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

protected:
	Aabb m_aabb;
	GeomTree *m_geomTree;
<<<<<<< HEAD
=======
	std::vector<GeomTree*> m_dynGeomTrees;
	unsigned int m_totalTris;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif
