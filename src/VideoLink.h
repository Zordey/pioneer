<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _VIDEOLINK_H
#define _VIDEOLINK_H

#include "gui/Gui.h"

class VideoLink : public Gui::Widget {
public:
	VideoLink(float w, float h) : m_width(w), m_height(h) {}

	virtual void GetSizeRequested(float size[2]) {
		size[0] = m_width;
		size[1] = m_height;
	}

private:
	float m_width, m_height;
};

#endif
