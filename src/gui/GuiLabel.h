<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUILABEL_H
#define _GUILABEL_H

#include "GuiWidget.h"
#include "GuiTextLayout.h"
#include <string>
<<<<<<< HEAD
=======
#include <SDL_stdinc.h>
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace Text { class TextureFont; }

namespace Gui {
	class Label: public Widget {
	public:
		Label(const char *text, TextLayout::ColourMarkupMode colourMarkupMode = TextLayout::ColourMarkupUse);
		Label(const std::string &text, TextLayout::ColourMarkupMode colourMarkupMode = TextLayout::ColourMarkupUse);
		virtual void Draw();
		virtual ~Label();
		virtual void GetSizeRequested(float size[2]);
		void SetText(const char *text);
		void SetText(const std::string &text);
		Label *Shadow(bool isOn) { m_shadow = isOn; return this; }
<<<<<<< HEAD
		Label *Color(float r, float g, float b);
=======
		Label *Color(Uint8 r, Uint8 g, Uint8 b);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		Label *Color(const ::Color &);
	private:
		void Init(const std::string &text, TextLayout::ColourMarkupMode colourMarkupMode);
		void UpdateLayout();
		void RecalcSize();
		std::string m_text;
		::Color m_color;
		bool m_shadow;
		GLuint m_dlist;
		RefCountedPtr<Text::TextureFont> m_font;
		TextLayout *m_layout;
		TextLayout::ColourMarkupMode m_colourMarkupMode;
	};
}

#endif /* _GUILABEL_H */
