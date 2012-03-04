#include "GuiTexture.h"
#include "graphics/Renderer.h"
#include "graphics/Material.h"
#include "graphics/VertexArray.h"

using namespace Graphics;

namespace Gui {

Texture::Texture(Renderer *r, SDL_Surface *s) :
    Graphics::Texture(TARGET_2D, Format(Format::INTERNAL_RGBA, Format::DATA_RGBA, Format::DATA_UNSIGNED_BYTE), Options(Options::CLAMP, Options::LINEAR, false))
{
	CreateFromSurface(r, s, true);
}

Texture::Texture(Renderer *r, const std::string &filename) :
    Graphics::Texture(TARGET_2D, Format(Format::INTERNAL_RGBA, Format::DATA_RGBA, Format::DATA_UNSIGNED_BYTE), Options(Options::CLAMP, Options::LINEAR, false))
{
	CreateFromFile(r, filename, true);
}


void TexturedQuad::Draw(Renderer *renderer, const vector2f &pos, const vector2f &size, const vector2f &texPos, const vector2f &texSize, const Color &tint)
{
    VertexArray va(ATTRIB_POSITION | ATTRIB_UV0);

	va.Add(vector3f(pos.x,        pos.y,        0.0f), vector2f(texPos.x,           texPos.y));
	va.Add(vector3f(pos.x,        pos.y+size.y, 0.0f), vector2f(texPos.x,           texPos.y+texSize.y));
	va.Add(vector3f(pos.x+size.x, pos.y,        0.0f), vector2f(texPos.x+texSize.x, texPos.y));
	va.Add(vector3f(pos.x+size.x, pos.y+size.y, 0.0f), vector2f(texPos.x+texSize.x, texPos.y+texSize.y));

	Material m;
	m.unlit = true;
	m.texture0 = m_texture.Get();
	m.vertexColors = false;
	m.diffuse = tint;
	renderer->DrawTriangles(&va, &m, TRIANGLE_STRIP);
}

}
