<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITEXTLAYOUT_H
#define _GUITEXTLAYOUT_H

#include "text/TextureFont.h"

namespace Gui {
class TextLayout {
public:
	enum ColourMarkupMode {
		ColourMarkupNone, // treats markup as normal text
		ColourMarkupSkip, // skips markup tags
		ColourMarkupUse   // interprets markup tags
	};
	explicit TextLayout(const char *_str, RefCountedPtr<Text::TextureFont> font = RefCountedPtr<Text::TextureFont>(0), ColourMarkupMode markup = ColourMarkupUse);
	void Render(float layoutWidth, const Color &color = Color::WHITE) const;
	void MeasureSize(const float layoutWidth, float outSize[2]) const;
<<<<<<< HEAD
	void _RenderRaw(float layoutWidth, const Color &color) const;
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void _MeasureSizeRaw(const float layoutWidth, float outSize[2]) const;
	~TextLayout() { free(str); }
	void SetJustified(bool v) { m_justify = v; }
private:
<<<<<<< HEAD
=======
	void _RenderRaw(float layoutWidth, const Color &color) const;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	struct word_t {
		char *word;
		float advx;
		word_t(char *_word, float _advx): word(_word), advx(_advx) {}
	};
	std::list<word_t> words;
	char *str;
	bool m_justify;
	ColourMarkupMode m_colourMarkup;

	RefCountedPtr<Text::TextureFont> m_font;
};
}

#endif /* _GUITEXTLAYOUT_H */
