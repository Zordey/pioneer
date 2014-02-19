<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Gui.h"
#include "GuiGradient.h"

namespace Gui {

Gradient::Gradient(float width, float height, const Color &beginColor, const Color &endColor, Direction direction)
{
	SetSize(width, height);

<<<<<<< HEAD
	Color4ub c0(beginColor);
	Color4ub c1(endColor);
	const unsigned char data[4][4] = {
		{ c0.r, c0.g, c0.b, c0.a },
		{ c1.r, c1.g, c1.b, c1.a },
=======
	const Uint8 data[4][4] = {
		{ beginColor.r, beginColor.g, beginColor.b, beginColor.a },
		{ endColor.r, endColor.g, endColor.b, endColor.a },
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};

	const Graphics::TextureFormat format = Graphics::TEXTURE_RGBA_8888;

	vector2f size = direction == HORIZONTAL ? vector2f(2.0f,1.0f) : vector2f(1.0f,2.0f);
	Graphics::Texture *texture = Gui::Screen::GetRenderer()->CreateTexture(Graphics::TextureDescriptor(format, size));
	texture->Update(data, size, format);
<<<<<<< HEAD
	m_quad.Reset(new TexturedQuad(texture));
=======
	m_quad.reset(new TexturedQuad(texture));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Gradient::GetSizeRequested(float size[2])
{
	GetSize(size);
}

void Gradient::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float size[2];
	GetSize(size);

	m_quad->Draw(Gui::Screen::GetRenderer(), vector2f(0.0f), vector2f(size[0],size[1]));
}

}
