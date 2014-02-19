<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UIVIEW_H
#define UIVIEW_H

#include "View.h"

// wrapper to allow new UI to be switched to by the existing view system
// remove this once all existing views are ported to the new UI
class UIView : public View {
public:
	UIView(const char *templateName) : m_templateName(templateName) {}
	UIView() : m_templateName(0) {}

	virtual void Update() {}
	virtual void Draw3D() {}

protected:
	virtual void OnSwitchTo();
	virtual void OnSwitchFrom();

private:
	const char *m_templateName;
};

#endif
