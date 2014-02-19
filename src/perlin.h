<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _PERLIN_H
#define _PERLIN_H

#include "vector3.h"

double noise(const double x, const double y, const double z );
static inline double noise(const vector3d &p) {
	return noise(p.x, p.y, p.z);
}

#endif /* _PERLIN_H */
