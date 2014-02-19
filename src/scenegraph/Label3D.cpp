<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Label3D.h"
#include "NodeVisitor.h"
#include "graphics/Renderer.h"
#include "graphics/VertexArray.h"

namespace SceneGraph {

Label3D::Label3D(Graphics::Renderer *r, RefCountedPtr<Text::DistanceFieldFont> font)
: Node(r, NODE_TRANSPARENT)
, m_font(font)
{
	Graphics::MaterialDescriptor matdesc;
	matdesc.textures = 1;
	matdesc.alphaTest = true;
	matdesc.lighting = true;
<<<<<<< HEAD
	m_geometry.Reset(font->CreateVertexArray());
	m_material.Reset(r->CreateMaterial(matdesc));
	m_material->texture0 = font->GetTexture();
	m_material->diffuse = Color::WHITE;
	m_material->emissive = Color(0.15f);
=======
	m_geometry.reset(font->CreateVertexArray());
	m_material.Reset(r->CreateMaterial(matdesc));
	m_material->texture0 = font->GetTexture();
	m_material->diffuse = Color::WHITE;
	m_material->emissive = Color(38);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_material->specular = Color::WHITE;

	Graphics::RenderStateDesc rsd;
	rsd.depthWrite = false;
	m_renderState = r->CreateRenderState(rsd);
}

Label3D::Label3D(const Label3D &label, NodeCopyCache *cache)
: Node(label, cache)
, m_material(label.m_material)
, m_font(label.m_font)
, m_renderState(label.m_renderState)
{
<<<<<<< HEAD
	m_geometry.Reset(m_font->CreateVertexArray());
=======
	m_geometry.reset(m_font->CreateVertexArray());
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Node* Label3D::Clone(NodeCopyCache *cache)
{
	return new Label3D(*this, cache);
}

void Label3D::SetText(const std::string &text)
{
	//regenerate geometry
	m_geometry->Clear();
	if (!text.empty())
<<<<<<< HEAD
		m_font->GetGeometry(*m_geometry.Get(), text, vector2f(0.f));
=======
		m_font->GetGeometry(*m_geometry, text, vector2f(0.f));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Label3D::Render(const matrix4x4f &trans, const RenderData *rd)
{
	Graphics::Renderer *r = GetRenderer();
	r->SetTransform(trans);
<<<<<<< HEAD
	r->DrawTriangles(m_geometry.Get(), m_material.Get());
=======
	r->DrawTriangles(m_geometry.get(), m_material.Get());
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Label3D::Accept(NodeVisitor &nv)
{
	nv.ApplyLabel(*this);
}

}
