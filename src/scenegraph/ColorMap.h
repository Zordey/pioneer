<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SCENEGRAPH_COLORMAP_H
#define _SCENEGRAPH_COLORMAP_H
/*
 * Color look-up texture generator for newmodel pattern system
 */
#include "libs.h"
#include "graphics/Texture.h"
<<<<<<< HEAD
=======
#include <SDL_stdinc.h>
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace Graphics { class Renderer; }

namespace SceneGraph {

class ColorMap {
public:
	ColorMap();
	Graphics::Texture *GetTexture();
<<<<<<< HEAD
	void Generate(Graphics::Renderer *r, const Color4ub &a, const Color4ub &b, const Color4ub &c);
	void SetSmooth(bool);

private:
	void AddColor(int width, const Color4ub &c, std::vector<unsigned char> &out);
=======
	void Generate(Graphics::Renderer *r, const Color &a, const Color &b, const Color &c);
	void SetSmooth(bool);

private:
	void AddColor(int width, const Color &c, std::vector<Uint8> &out);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	bool m_smooth;
	RefCountedPtr<Graphics::Texture> m_texture;
};

}

#endif
