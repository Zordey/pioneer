<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITOGGLEBUTTON_H
#define _GUITOGGLEBUTTON_H

#include "GuiWidget.h"
#include <string>

namespace Gui {
	class ToggleButton: public Button {
	public:
		ToggleButton();
		virtual void Draw();
		virtual ~ToggleButton() {}
		virtual void GetSizeRequested(float size[2]);
		virtual bool OnMouseDown(MouseButtonEvent *e);
		virtual void OnActivate();
		void SetPressed(bool s) { m_pressed = s; }
		bool GetPressed() { return m_pressed != 0; }

		sigc::signal<void, ToggleButton *, bool> onChange;
	private:
		bool m_pressed;
	};
}

#endif /* _GUITOGGLEBUTTON_H */
