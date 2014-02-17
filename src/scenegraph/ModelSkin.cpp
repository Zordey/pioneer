<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ModelSkin.h"
#include "Model.h"
#include "StringF.h"
#include "graphics/TextureBuilder.h"
<<<<<<< HEAD
=======
#include <SDL_stdinc.h>
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace SceneGraph {

ModelSkin::ModelSkin() :
<<<<<<< HEAD
	m_patternIndex(0),
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
    m_colors(3)
{
}

void ModelSkin::Apply(Model *model) const
{
<<<<<<< HEAD
	model->SetPattern(m_patternIndex);
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	model->SetColors(m_colors);
	for (unsigned int i = 0; i < MAX_DECAL_MATERIALS; i++) {
		if (m_decals[i].empty())
			model->ClearDecal(i);
		else
			model->SetDecalTexture(Graphics::TextureBuilder::Decal(stringf("textures/decals/%0.png", m_decals[i])).GetOrCreateTexture(model->GetRenderer(), "decal"), i);
	}
	model->SetLabel(m_label);
}

<<<<<<< HEAD
void ModelSkin::SetPattern(unsigned int index)
{
	m_patternIndex = index;
}

void ModelSkin::SetColors(const std::vector<Color4ub> &colors)
=======
void ModelSkin::SetColors(const std::vector<Color> &colors)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	assert(colors.size() == 3);
	m_colors = colors;
}

<<<<<<< HEAD
void ModelSkin::SetPrimaryColor(const Color4ub &color)
=======
void ModelSkin::SetPrimaryColor(const Color &color)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	m_colors[0] = color;
}

<<<<<<< HEAD
void ModelSkin::SetSecondaryColor(const Color4ub &color)
=======
void ModelSkin::SetSecondaryColor(const Color &color)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	m_colors[1] = color;
}

<<<<<<< HEAD
void ModelSkin::SetTrimColor(const Color4ub &color)
=======
void ModelSkin::SetTrimColor(const Color &color)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	m_colors[2] = color;
}

void ModelSkin::SetRandomColors(Random &rand)
{
	// primary colour is random, but try to avoid ridiculous extremes
<<<<<<< HEAD
	m_colors[0] = Color4ub(rand.Int32(192)+32, rand.Int32(192)+32, rand.Int32(192)+32);

	// secondary is the inverse of the primary, so has identical hue
	m_colors[1] = Color4ub(256-m_colors[0].r, 256-m_colors[0].g, 256-m_colors[0].b);

	// trim is a darker version of the primary
	m_colors[2] = Color4ub(
		std::max(m_colors[0].r,static_cast<unsigned char>(32))-32,
		std::max(m_colors[0].g,static_cast<unsigned char>(32))-32,
		std::max(m_colors[0].b,static_cast<unsigned char>(32))-32
=======
	m_colors[0] = Color(rand.Int32(192)+32, rand.Int32(192)+32, rand.Int32(192)+32);

	// secondary is the inverse of the primary, so has identical hue
	m_colors[1] = Color(256-m_colors[0].r, 256-m_colors[0].g, 256-m_colors[0].b);

	// trim is a darker version of the primary
	m_colors[2] = Color(
		std::max(m_colors[0].r,static_cast<Uint8>(32))-32,
		std::max(m_colors[0].g,static_cast<Uint8>(32))-32,
		std::max(m_colors[0].b,static_cast<Uint8>(32))-32
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	);
}

void ModelSkin::SetDecal(const std::string &name, unsigned int index)
{
	assert(index < MAX_DECAL_MATERIALS);
	m_decals[index] = name;
}

void ModelSkin::ClearDecal(unsigned int index)
{
	assert(index < MAX_DECAL_MATERIALS);
	m_decals[index] = "";
}

void ModelSkin::ClearDecals()
{
	for (unsigned int i = 0; i < MAX_DECAL_MATERIALS; i++)
		ClearDecal(i);
}

void ModelSkin::SetLabel(const std::string &label)
{
	m_label = label;
}

void ModelSkin::Load(Serializer::Reader &rd)
{
<<<<<<< HEAD
	m_patternIndex = rd.Int32();
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	for (unsigned int i = 0; i < 3; i++) {
		m_colors[i].r = rd.Byte();
		m_colors[i].g = rd.Byte();
		m_colors[i].b = rd.Byte();
	}
	for (unsigned int i = 0; i < MAX_DECAL_MATERIALS; i++)
		m_decals[i] = rd.String();
	m_label = rd.String();
}

void ModelSkin::Save(Serializer::Writer &wr) const
{
<<<<<<< HEAD
	wr.Int32(m_patternIndex);
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	for (unsigned int i = 0; i < 3; i++) {
		wr.Byte(m_colors[i].r);
		wr.Byte(m_colors[i].g);
		wr.Byte(m_colors[i].b);
	}
	for (unsigned int i = 0; i < MAX_DECAL_MATERIALS; i++)
		wr.String(m_decals[i]);
	wr.String(m_label);
}

}
