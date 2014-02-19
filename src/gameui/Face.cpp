<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Face.h"
#include "FileSystem.h"
#include "SDLWrappers.h"
#include "graphics/TextureBuilder.h"
<<<<<<< HEAD
=======
#include "FaceGenManager.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

using namespace UI;

namespace GameUI {

static const Uint32 FACE_WIDTH = 295;
static const Uint32 FACE_HEIGHT = 285;

<<<<<<< HEAD
// XXX these shouldn't really be hardcoded. it'd be much nicer to poke through
// the facegen/ dir and figure out what we've got available. that or some
// config file
static const Uint32 MAX_HEAD = 20;
static const Uint32 MAX_EYES = 20;
static const Uint32 MAX_NOSE = 20;
static const Uint32 MAX_MOUTH = 20;
static const Uint32 MAX_HAIR = 20;

static const Uint32 MAX_CLOTHES = 20;
static const Uint32 MAX_ARMOUR = 3;
static const Uint32 MAX_ACCESSORIES = 16;

static const Uint32 MAX_BACKGROUND = 18;

RefCountedPtr<Graphics::Material> Face::s_material;

static void _blit_image(SDL_Surface *s, const char *filename, int xoff, int yoff)
{
	SDLSurfacePtr is = LoadSurfaceFromFile(filename);
	// XXX what should this do if the image couldn't be loaded?
	if (! is) { return; }

	SDL_Rect destrec = { 0, 0, 0, 0 };
	destrec.x = ((FACE_WIDTH-is->w-1)/2)+xoff;
	destrec.y = yoff;
	SDL_BlitSurface(is.Get(), 0, s, &destrec);
}

static void _blit_image(const SDLSurfacePtr &s, const char *filename, int xoff, int yoff)
{
	_blit_image(s.Get(), filename, xoff, yoff);
}

Face::Face(Context *context, Uint32 flags, Uint32 seed) : Single(context)
{
	if (!seed) seed = time(0);
	Random rand(seed);
=======
RefCountedPtr<Graphics::Material> Face::s_material;

Face::Face(Context *context, Uint32 flags, Uint32 seed) : Single(context), m_preferredSize(INT_MAX)
{
	if (!seed) seed = time(0);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	m_flags = flags;
	m_seed = seed;

<<<<<<< HEAD
	int race = rand.Int32(0,2);

	int gender;
	switch (flags & GENDER_MASK) {
		case MALE:
			gender = 0;
			break;
		case FEMALE:
			gender = 1;
			break;
		case RAND:
		default:
			gender = rand.Int32(0,1);
			break;
	}

	int head  = rand.Int32(0,MAX_HEAD);
	int eyes  = rand.Int32(0,MAX_EYES);
	int nose  = rand.Int32(0,MAX_NOSE);
	int mouth = rand.Int32(0,MAX_MOUTH);
	int hair  = rand.Int32(0,MAX_HAIR);

	int clothes = rand.Int32(0,MAX_CLOTHES);

	int armour = rand.Int32(0,MAX_ARMOUR);

	int accessories = rand.Int32(0,MAX_ACCESSORIES);

	int background = rand.Int32(0,MAX_BACKGROUND);

	char filename[1024];

	SDLSurfacePtr faceim = SDLSurfacePtr::WrapNew(SDL_CreateRGBSurface(SDL_SWSURFACE, FACE_WIDTH, FACE_HEIGHT, 24, 0xff, 0xff00, 0xff0000, 0));

	snprintf(filename, sizeof(filename), "facegen/backgrounds/background_%d.png", background);
	_blit_image(faceim, filename, 0, 0);

	snprintf(filename, sizeof(filename), "facegen/race_%d/head/head_%d_%d.png", race, gender, head);
	_blit_image(faceim, filename, 0, 0);

	if (!(flags & ARMOUR)) {
		snprintf(filename, sizeof(filename), "facegen/clothes/cloth_%d_%d.png", gender, clothes);
		_blit_image(faceim, filename, 0, 135);
	}

	snprintf(filename, sizeof(filename), "facegen/race_%d/eyes/eyes_%d_%d.png", race, gender, eyes);
	_blit_image(faceim, filename, 0, 41);

	snprintf(filename, sizeof(filename), "facegen/race_%d/nose/nose_%d_%d.png", race, gender, nose);
	_blit_image(faceim, filename, 1, 89);

	snprintf(filename, sizeof(filename), "facegen/race_%d/mouth/mouth_%d_%d.png", race, gender, mouth);
	_blit_image(faceim, filename, 0, 155);

	if (!(flags & ARMOUR)) {
		snprintf(filename, sizeof(filename), "facegen/accessories/acc_%d.png", accessories);
		if (rand.Int32(0,1)>0)	_blit_image(faceim, filename, 0, 0);

		snprintf(filename, sizeof(filename), "facegen/race_%d/hair/hair_%d_%d.png", race, gender, hair);
		_blit_image(faceim, filename, 0, 0);
	}
	else {
		snprintf(filename, sizeof(filename), "facegen/clothes/armour_%d.png", armour);
		_blit_image(faceim, filename, 0, 0);
	}

	m_texture.Reset(Graphics::TextureBuilder(faceim, Graphics::LINEAR_CLAMP, true, true).CreateTexture(GetContext()->GetRenderer()));
=======
	SDLSurfacePtr faceim = SDLSurfacePtr::WrapNew(SDL_CreateRGBSurface(SDL_SWSURFACE, FACE_WIDTH, FACE_HEIGHT, 24, 0xff, 0xff00, 0xff0000, 0));

	Sint8 gender=0;
	FaceGenManager::BlitFaceIm(faceim, gender, flags, seed);

	m_texture.reset(Graphics::TextureBuilder(faceim, Graphics::LINEAR_CLAMP, true, true).CreateTexture(GetContext()->GetRenderer()));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	if (!s_material) {
		Graphics::MaterialDescriptor matDesc;
		matDesc.textures = 1;
		s_material.Reset(GetContext()->GetRenderer()->CreateMaterial(matDesc));
	}
<<<<<<< HEAD
=======

	m_preferredSize = UI::Point(FACE_WIDTH, FACE_HEIGHT);
	SetSizeControlFlags(UI::Widget::PRESERVE_ASPECT);
}

UI::Point Face::PreferredSize() {
	return m_preferredSize;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Face::Layout()
{
	Point size(GetSize());
	Point activeArea(std::min(size.x, size.y));
	Point activeOffset(std::max(0, (size.x-activeArea.x)/2), std::max(0, (size.y-activeArea.y)/2));
	SetActiveArea(activeArea, activeOffset);

	Widget *innerWidget = GetInnerWidget();
	if (!innerWidget) return;
	SetWidgetDimensions(innerWidget, activeOffset, activeArea);
	innerWidget->Layout();
}

void Face::Draw()
{
	const Point &offset = GetActiveOffset();
	const Point &area = GetActiveArea();

	const float x = offset.x;
	const float y = offset.y;
	const float sx = area.x;
	const float sy = area.y;

	const vector2f texSize = m_texture->GetDescriptor().texSize;

	Graphics::VertexArray va(Graphics::ATTRIB_POSITION | Graphics::ATTRIB_UV0);
	va.Add(vector3f(x,    y,    0.0f), vector2f(0.0f,      0.0f));
	va.Add(vector3f(x,    y+sy, 0.0f), vector2f(0.0f,      texSize.y));
	va.Add(vector3f(x+sx, y,    0.0f), vector2f(texSize.x, 0.0f));
	va.Add(vector3f(x+sx, y+sy, 0.0f), vector2f(texSize.x, texSize.y));

	Graphics::Renderer *r = GetContext()->GetRenderer();
<<<<<<< HEAD
	s_material->texture0 = m_texture.Get();
=======
	s_material->texture0 = m_texture.get();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	r->DrawTriangles(&va, s_material.Get(), Graphics::TRIANGLE_STRIP);

	Single::Draw();
}

<<<<<<< HEAD
=======
Face *Face::SetHeightLines(Uint32 lines)
{
	const Text::TextureFont *font = GetContext()->GetFont(GetFont()).Get();
	const float height = font->GetHeight() * lines;
	m_preferredSize = UI::Point(height * float(FACE_WIDTH) / float(FACE_HEIGHT), height);
	GetContext()->RequestLayout();
	return this;
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}
