#ifndef _GAMEUI_FACE_H
#define _GAMEUI_FACE_H

#include "ui/Context.h"
#include "SmartPtr.h"
#include "gui/GuiTexturedQuad.h"

namespace GameUI {

class Face : public UI::Widget {
public:
	Face(UI::Context *context, Uint32 flags = 0, Uint32 seed = 0);

	virtual UI::Point PreferredSize() { return UI::Point(INT_MAX); }
	virtual void Layout();
	virtual void Draw();

	enum Flags { // <enum scope='GameUI::Face' name=GameUIFaceFlags>
		RAND        = 0,
		MALE        = (1<<0),
		FEMALE      = (1<<1),
		GENDER_MASK   = 0x03,   // <enum skip>

		ARMOUR = (1<<2),
	};

private:
	Uint32 m_flags;
	Uint32 m_seed;

	ScopedPtr<Gui::TexturedQuad> m_quad;
};

}

#endif
