#ifndef _NEWMODEL_COLORMAP_H
#define _NEWMODEL_COLORMAP_H
/*
 * Color look-up texture generator for newmodel pattern system
 */
#include "libs.h"
#include "graphics/Texture.h"

namespace Graphics { class Renderer; }

namespace Newmodel {

class ColorMap {
public:
	void Generate(Graphics::Renderer *r, const Color4ub &a, const Color4ub &b, const Color4ub &c);
	Graphics::Texture *GetTexture();

private:
	RefCountedPtr<Graphics::Texture> m_texture;
	void AddColor(int width, const Color4ub &c, std::vector<unsigned char> &out);
};

}

#endif
