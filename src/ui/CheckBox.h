<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_CHECKBOX_H
#define UI_CHECKBOX_H

#include "Widget.h"

namespace UI {

class CheckBox: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Layout();
	virtual void Draw();

<<<<<<< HEAD
=======
	void Toggle();
	bool IsChecked() const;
	void SetState(bool state);

	sigc::signal<void, bool> onValueChanged;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
protected:
	friend class Context;
	CheckBox(Context *context): Widget(context), m_checked(false) {}

	void HandleClick();

private:
	bool m_checked;
};

}

#endif
