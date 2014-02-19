<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SCENEGRAPH_THRUSTER_H
#define _SCENEGRAPH_THRUSTER_H
/*
 * Spaceship thruster
 */
#include "libs.h"
#include "Node.h"

namespace Graphics {
	class Renderer;
	class VertexArray;
	class Material;
	class RenderState;
}

namespace SceneGraph {

class Thruster : public Node {
public:
	Thruster(Graphics::Renderer *, bool linear, const vector3f &pos, const vector3f &dir);
	Thruster(const Thruster&, NodeCopyCache *cache = 0);
	Node *Clone(NodeCopyCache *cache = 0);
	virtual void Accept(NodeVisitor &v);
	virtual const char *GetTypeName() const { return "Thruster"; }
	virtual void Render(const matrix4x4f &trans, const RenderData *rd);
	virtual void Save(NodeDatabase&) override;
	static Thruster *Load(NodeDatabase&);

private:
<<<<<<< HEAD
	static Graphics::VertexArray* CreateGeometry();
	RefCountedPtr<Graphics::Material> m_tMat;
	ScopedPtr<Graphics::VertexArray> m_tVerts;
=======
	static Graphics::VertexArray* CreateThrusterGeometry();
	static Graphics::VertexArray* CreateGlowGeometry();
	RefCountedPtr<Graphics::Material> m_tMat;
	RefCountedPtr<Graphics::Material> m_glowMat;
	std::unique_ptr<Graphics::VertexArray> m_tVerts;
	std::unique_ptr<Graphics::VertexArray> m_glowVerts;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	bool linearOnly;
	vector3f dir;
	vector3f pos;
};

}

#endif
