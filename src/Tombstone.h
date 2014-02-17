<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _TOMBSTONE_H
#define _TOMBSTONE_H

#include "Cutscene.h"

class Tombstone : public Cutscene {
public:
	Tombstone(Graphics::Renderer *r, int width, int height);
	virtual void Draw(float time);
};

#endif
