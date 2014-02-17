<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_SINGLE_H
#define UI_SINGLE_H

#include "Container.h"

namespace UI {

class Single : public Container {
public:
	virtual Point PreferredSize();
	virtual void Layout();

	Single *SetInnerWidget(Widget *widget);
	void RemoveInnerWidget();
	Widget *GetInnerWidget() const { return m_innerWidget; }

protected:
	Single(Context *context) : Container(context), m_innerWidget(0) {}

    virtual void RemoveWidget(Widget *widget);

private:
	Widget *m_innerWidget;
};

}

#endif
