<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "GuiTexturedQuad.h"
#include "graphics/Renderer.h"
#include "graphics/Material.h"
#include "graphics/VertexArray.h"
#include "GuiScreen.h"

using namespace Graphics;

namespace Gui {

void TexturedQuad::Draw(Graphics::Renderer *renderer, const vector2f &pos, const vector2f &size, const vector2f &texPos, const vector2f &texSize, const Color &tint)
{
<<<<<<< HEAD
    Graphics::VertexArray va(ATTRIB_POSITION | ATTRIB_UV0);

	va.Add(vector3f(pos.x,        pos.y,        0.0f), vector2f(texPos.x,           texPos.y));
	va.Add(vector3f(pos.x,        pos.y+size.y, 0.0f), vector2f(texPos.x,           texPos.y+texSize.y));
	va.Add(vector3f(pos.x+size.x, pos.y,        0.0f), vector2f(texPos.x+texSize.x, texPos.y));
	va.Add(vector3f(pos.x+size.x, pos.y+size.y, 0.0f), vector2f(texPos.x+texSize.x, texPos.y+texSize.y));

	// Create material on first use. Bit of a hack.
	if (!m_material.Valid()) {
		Graphics::MaterialDescriptor desc;
		desc.textures = 1;
		m_material.Reset(renderer->CreateMaterial(desc));
		m_material->texture0 = m_texture.Get();
	}
	m_material->diffuse = tint;
	renderer->DrawTriangles(&va, m_material.Get(), TRIANGLE_STRIP);
=======
	PROFILE_SCOPED()
	if(!m_va.get()) {
		PROFILE_SCOPED_RAW("!m_va.get()")
		m_va.reset(new Graphics::VertexArray(ATTRIB_POSITION | ATTRIB_UV0));

		m_va->Add(vector3f(pos.x,        pos.y,        0.0f), vector2f(texPos.x,           texPos.y));
		m_va->Add(vector3f(pos.x,        pos.y+size.y, 0.0f), vector2f(texPos.x,           texPos.y+texSize.y));
		m_va->Add(vector3f(pos.x+size.x, pos.y,        0.0f), vector2f(texPos.x+texSize.x, texPos.y));
		m_va->Add(vector3f(pos.x+size.x, pos.y+size.y, 0.0f), vector2f(texPos.x+texSize.x, texPos.y+texSize.y));
	} else {
		m_va->Set(0, vector3f(pos.x,        pos.y,        0.0f), vector2f(texPos.x,           texPos.y));
		m_va->Set(1, vector3f(pos.x,        pos.y+size.y, 0.0f), vector2f(texPos.x,           texPos.y+texSize.y));
		m_va->Set(2, vector3f(pos.x+size.x, pos.y,        0.0f), vector2f(texPos.x+texSize.x, texPos.y));
		m_va->Set(3, vector3f(pos.x+size.x, pos.y+size.y, 0.0f), vector2f(texPos.x+texSize.x, texPos.y+texSize.y));
	}

	// Create material on first use. Bit of a hack.
	if (!m_material) {
		PROFILE_SCOPED_RAW("!material")
		Graphics::MaterialDescriptor desc;
		desc.textures = 1;
		m_material.reset(renderer->CreateMaterial(desc));
		m_material->texture0 = m_texture.Get();
	}
	m_material->diffuse = tint;
	renderer->DrawTriangles(m_va.get(), m_material.get(), TRIANGLE_STRIP);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

}
