<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_SMALLBUTTON_H
#define UI_SMALLBUTTON_H

#include "Widget.h"

namespace UI {

class SmallButton: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Layout();
	virtual void Draw();

protected:
	friend class Context;
	SmallButton(Context *context): Widget(context) {}
};

}

#endif
