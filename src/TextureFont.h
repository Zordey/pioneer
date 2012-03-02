#ifndef _TEXTUREFONT_H
#define _TEXTUREFONT_H

#include "Font.h"
#include "Color.h"
#include "graphics/Texture.h"

namespace Graphics { class Renderer; }
namespace Gui { class TexturedQuad; }

class TextureFont : public Font {

private:

	class GlyphTexture : public Graphics::Texture {
	public:
		GlyphTexture(Uint8 *data, int width, int height);
		virtual void Bind();
	};

public:
	TextureFont(const FontConfig &fc);
	~TextureFont();

	void RenderString(Graphics::Renderer *r, const char *str, float x, float y, const Color &color = Color::WHITE);
	Color RenderMarkup(Graphics::Renderer *r, const char *str, float x, float y, const Color &color = Color::WHITE);
	void MeasureString(const char *str, float &w, float &h);
	void MeasureCharacterPos(const char *str, int charIndex, float &x, float &y) const;
	int PickCharacter(const char *str, float mouseX, float mouseY) const;

	// of Ms
	float GetHeight() const { return m_height; }
	float GetWidth() const { return m_width; }
	float GetDescender() const { return m_descender; }
	struct glfglyph_t {
		Gui::TexturedQuad *quad;
		float advx, advy;
		float width, height;
		int offx, offy;
	};
	const glfglyph_t &GetGlyph(Uint32 ch) { return m_glyphs[ch]; }

	static int GetGlyphCount() { return s_glyphCount; }
	static void ClearGlyphCount() { s_glyphCount = 0; }

private:
	void RenderGlyph(Graphics::Renderer *r, Uint32 chr, float x, float y, const Color &color);
	float m_height;
	float m_width;
	float m_descender;
	int m_texSize, m_pixSize;

	static int s_glyphCount;
	std::map<Uint32,glfglyph_t> m_glyphs;
};

#endif
