﻿// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _TEXT_DISTANCEFIELDFONT_H
#define _TEXT_DISTANCEFIELDFONT_H
/*
 * Font rendering using a pregenerated signed distance field texture
 * to produce highly zoomable text.
 * Reads texture+definition generated by:
 * http://www.angelcode.com/products/bmfont/ combined with
 * http://bitsquid.blogspot.ca/2010/04/distance-field-based-rendering-of.html
 *
 * Note, this is meant for the model system Label3D: short text on a single line
 *
 * The font definitions are text files looking like this:
 *
 * info face="Ubuntu Mono" size=32 bold=0 italic=0 charset="" unicode=1 stretchH=100 smooth=1 aa=1 padding=8,8,8,8 spacing=1,1 outline=0
 * common lineHeight=32 base=26.5 scaleW=256 scaleH=256 pages=1 packed=0 alphaChnl=0 redChnl=4 greenChnl=4 blueChnl=4
 * page id=0 file="label3d.png"
 * chars count=96
 * char id=0 x=251.75 y=0 width=2 height=2.125 xoffset=-1 yoffset=30.875 xadvance=16 page=0 chnl=15
 * char id=32 x=253.875 y=0 width=2 height=2.125 xoffset=-1 yoffset=30.875 xadvance=16 page=0 chnl=15
 * (etc)
 */
#include "libs.h"
#include "StringRange.h"

namespace Graphics {
	class Texture;
	class VertexArray;
}

namespace Text {

class DistanceFieldFont : public RefCounted {
public:
	DistanceFieldFont(const std::string &definitionFileName, Graphics::Texture*);
	void GetGeometry(Graphics::VertexArray&, const std::string&, const vector2f &offset);
	Graphics::Texture *GetTexture() const { return m_texture; }
	Graphics::VertexArray *CreateVertexArray() const;

private:
	struct Glyph {
		vector2f uv;
		vector2f uvSize;
		vector2f size; //geometry size
		vector2f offset; //offset applied to the cursor position
		float xAdvance; //how much the cursor should be moved after a character
	};
	Graphics::Texture *m_texture;
	std::map<Uint32, Glyph> m_glyphs;
	vector2f m_sheetSize;
	float m_fontSize; //32 etc. Glyph size/advance will be scaled to 1/fontSize.

	void AddGlyph(Graphics::VertexArray &va, const vector2f &pos, const Glyph&, vector2f &bounds);
	void ParseChar(const StringRange& line);
	void ParseCommon(const StringRange& line);
	void ParseInfo(const StringRange& line);
};

}

#endif