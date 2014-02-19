<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUIEVENTS_H
#define _GUIEVENTS_H

namespace Gui {
	struct MouseButtonEvent {
		Uint8 isdown;
		Uint8 button;
		float x, y; // widget coords
		float screenX, screenY; // screen coords
<<<<<<< HEAD
=======
		enum {
			BUTTON_WHEELUP   = 0xfe,
			BUTTON_WHEELDOWN = 0xff
		};
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};
	struct MouseMotionEvent {
		float x, y; // widget coords
		float screenX, screenY; // screen coords
	};
}

#endif /* _GUIEVENTS_H */
