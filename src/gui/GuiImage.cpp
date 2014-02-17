<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "GuiImage.h"
#include "GuiScreen.h"
#include "graphics/TextureBuilder.h"

namespace Gui {

Image::Image(const char *filename):
	Widget(), m_color(Color::WHITE)
{
	InitTexture(filename);

	const Graphics::TextureDescriptor &descriptor = m_quad->GetTexture()->GetDescriptor();
	m_width = descriptor.dataSize.x*descriptor.texSize.x;
	m_height = descriptor.dataSize.y*descriptor.texSize.y;
	SetSize(m_width, m_height);
}

Image::Image(const char *filename, float renderWidth, float renderHeight):
	Widget(), m_color(Color::WHITE)
{
	InitTexture(filename);

	m_width = renderWidth;
	m_height = renderHeight;
	SetSize(m_width, m_height);
}

void Image::InitTexture(const char* filename)
{
	Graphics::TextureBuilder b = Graphics::TextureBuilder::UI(filename);
<<<<<<< HEAD
	m_quad.Reset(new TexturedQuad(b.GetOrCreateTexture(Gui::Screen::GetRenderer(), "ui")));
=======
	m_quad.reset(new TexturedQuad(b.GetOrCreateTexture(Gui::Screen::GetRenderer(), "ui")));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Image::GetSizeRequested(float size[2])
{
	size[0] = m_width;
	size[1] = m_height;
}

void Image::SetRenderDimensions(const float wide, const float high)
{
	m_width = wide;
	m_height = high;
}

void Image::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float allocSize[2];
	GetSize(allocSize);

	Graphics::Renderer *r = Gui::Screen::GetRenderer();
	r->SetBlendMode(Graphics::BLEND_ALPHA);
	m_quad->Draw(r, vector2f(0.0f), vector2f(allocSize[0],allocSize[1]), m_color);
}

}

