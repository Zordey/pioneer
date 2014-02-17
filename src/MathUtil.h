<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _MATHUTIL_H
#define _MATHUTIL_H

#include "vector3.h"

namespace MathUtil {

// random point on a sphere, distributed uniformly by area
vector3d RandomPointOnSphere(double minRadius, double maxRadius);
inline vector3d RandomPointOnSphere(double radius) { return RandomPointOnSphere(radius, radius); }

vector3d RandomPointInCircle(double minRadius, double maxRadius);
inline vector3d RandomPointInCircle(double radius) { return RandomPointInCircle(0.0, radius); }
inline vector3d RandomPointOnCircle(double radius) { return RandomPointInCircle(radius, radius); }

}

#endif
