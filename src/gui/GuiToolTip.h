<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUITOOLTIP_H
#define _GUITOOLTIP_H

#include "GuiWidget.h"
#include <string>

namespace Gui {
	class ToolTip: public Widget {
	public:
		ToolTip(Widget *owner, const char *text);
		ToolTip(Widget *owner, std::string &text);
		virtual void Draw();
		virtual ~ToolTip();
		virtual void GetSizeRequested(float size[2]);
		void SetText(const char *text);
		void SetText(std::string &text);
	private:
		void CalcSize();
		Widget *m_owner;
		std::string m_text;
		TextLayout *m_layout;
		Uint32 m_createdTime;
	};
}

#endif /* _GUITOOLTIP_H */
