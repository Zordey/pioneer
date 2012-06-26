#ifndef _STATICGEOMETRY_H
#define _STATICGEOMETRY_H
/*
 * Geometry node containing one StaticMesh. Nothing fancy.
 */
#include "Node.h"
#include "Aabb.h"
#include "graphics/Renderer.h"
#include "graphics/StaticMesh.h"
#include "SmartPtr.h"

namespace Newmodel {

class NodeVisitor;

class StaticGeometry : public Node
{
public:
	StaticGeometry();
	Graphics::StaticMesh *GetMesh() { return m_mesh.Get(); }
	virtual void Accept(NodeVisitor &nv);
	virtual void Render(Graphics::Renderer *r, const matrix4x4f &trans, RenderData *rd);
	Aabb m_boundingBox;
	Graphics::BlendMode m_blendMode;

protected:
	~StaticGeometry();
	void DrawBoundingBox(Graphics::Renderer *r, const Aabb &bb);
	ScopedPtr<Graphics::StaticMesh> m_mesh;
};

}
#endif