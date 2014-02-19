<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ColorBackground.h"
#include "Context.h"
#include "graphics/Renderer.h"
#include "graphics/VertexArray.h"
#include "graphics/Material.h"

namespace UI {

ColorBackground::ColorBackground(Context *context, const Color &color) :
<<<<<<< HEAD
	Single(context)
{
	Graphics::MaterialDescriptor desc;
	m_material.Reset(GetContext()->GetRenderer()->CreateMaterial(desc));
	m_material->diffuse = color;
=======
	Single(context),
	m_color(color)
{
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void ColorBackground::Draw()
{
<<<<<<< HEAD
	const Point &size = GetSize();

	Graphics::VertexArray va(Graphics::ATTRIB_POSITION);
	va.Add(vector3f(0,      0,      0));
	va.Add(vector3f(0,      size.y, 0));
	va.Add(vector3f(size.x, 0,      0));
	va.Add(vector3f(size.x, size.y, 0));

	GetContext()->GetRenderer()->DrawTriangles(&va, m_material.Get(), Graphics::TRIANGLE_STRIP);

=======
	GetContext()->GetSkin().DrawRectColor(m_color, Point(), GetSize());
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Container::Draw();
}

}
