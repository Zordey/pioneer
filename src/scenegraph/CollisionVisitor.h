<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _COLLISIONVISITOR_H
#define _COLLISIONVISITOR_H
/*
<<<<<<< HEAD
 * Creates a new collision mesh based on bounding boxes
 * This is for uses when a precise collision mesh is not supplied
 * with the model
 * This can be improved to create a smarter cmesh if someone feels like it.
=======
 * Creates a new collision mesh from CollisionGeometry nodes
 * or the nodes' AABB, when no CGeoms found.
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
 */
#include "NodeVisitor.h"
#include "libs.h"
#include "CollMesh.h"

namespace SceneGraph {
<<<<<<< HEAD

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
class Group;
class MatrixTransform;
class StaticGeometry;

class CollisionVisitor : public NodeVisitor
{
public:
	CollisionVisitor();
	virtual void ApplyStaticGeometry(StaticGeometry &);
	virtual void ApplyMatrixTransform(MatrixTransform &);
	virtual void ApplyCollisionGeometry(CollisionGeometry &);
	//call after traversal complete
	RefCountedPtr<CollMesh> CreateCollisionMesh();
	float GetBoundingRadius() const { return m_boundingRadius; }

private:
<<<<<<< HEAD
=======
	void ApplyDynamicCollisionGeometry(CollisionGeometry &);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void AabbToMesh(const Aabb&);
	//geomtree is not built until all nodes are visited and
	//BuildCollMesh called
	RefCountedPtr<CollMesh> m_collMesh;
	std::vector<matrix4x4f> m_matrixStack;
	float m_boundingRadius;
<<<<<<< HEAD
};

=======
	bool m_properData;

	//temporary arrays for static geometry
	std::vector<vector3f> m_vertices;
	std::vector<Uint16> m_indices;
	std::vector<unsigned int> m_flags;

	unsigned int m_totalTris;
};
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}
#endif
