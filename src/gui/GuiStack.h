<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUISTACK_H
#define _GUISTACK_H

#include "GuiWidget.h"
#include "GuiContainer.h"
#include <stack>

namespace Gui {
	class Stack: public Container {
	public:
		Stack();
		virtual ~Stack();

		virtual void GetSizeRequested(float size[2]);
		virtual void OnChildResizeRequest(Widget *w);
		virtual void UpdateAllChildSizes();
		virtual void ShowAll();

		virtual Widget *Top();
		virtual int Size();
		virtual void Push(Widget *w);
		virtual void Pop();
		virtual void Clear();
		virtual void JumpTo(Widget *w);

	private:
		std::stack<Widget*> m_widgets;
	};
}

#endif
