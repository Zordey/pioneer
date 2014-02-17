<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITEXTENTRY_H
#define _GUITEXTENTRY_H

#include "GuiWidget.h"
#include <string>

namespace Text { class TextureFont; }

namespace Gui {
	class TextEntry: public Widget {
	public:
		enum NewlineMode {
			IgnoreNewline,
			AcceptNewline,
			AcceptCtrlNewline
		};

		TextEntry();
		virtual ~TextEntry();
		virtual void GetSizeRequested(float size[2]);
		virtual void Draw();
		virtual bool OnMouseDown(MouseButtonEvent *e);
		void SetText(const std::string &text);
		std::string GetText() const { return m_text; }
		void SetCursorPos(int pos) { m_cursPos = Clamp(pos, 0, signed(m_text.size())); }
		int GetCursorPos() const { return m_cursPos; };
<<<<<<< HEAD
		virtual bool OnKeyPress(const SDL_keysym *);
=======
		virtual bool OnKeyDown(const SDL_Keysym *);
		virtual void OnTextInput(Uint32 unicode);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		virtual void Show() { GrabFocus(); Widget::Show(); }
		virtual void GrabFocus();
		void Unfocus();
		NewlineMode GetNewlineMode() const { return m_newlineMode; }
		void SetNewlineMode(NewlineMode mode) { m_newlineMode = mode; }

<<<<<<< HEAD
		// XXX probably a bad idea to use a signal with a return type
		// (by default, the return value will be whatever is returned by the
		//  last functor that's called when emitting the signal...
		//  you can provide your own 'accumulator' type though, to combine
		//  return values in different ways)
		sigc::signal<bool, const SDL_keysym*> onFilterKeys;
		sigc::signal<void, const SDL_keysym*> onKeyPress;
=======
		sigc::signal<void, const SDL_Keysym*> onKeyPress;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		sigc::signal<void> onValueChanged;
	private:

		void OnRawMouseDown(MouseButtonEvent *e);

		std::string m_text;
		int m_cursPos;
		int m_scroll;
		RefCountedPtr<Text::TextureFont> m_font;
		NewlineMode m_newlineMode;
		int m_newlineCount;

		bool m_justFocused;
		sigc::connection m_clickout;
	};
}

#endif /* _GUITEXTENTRY_H */
