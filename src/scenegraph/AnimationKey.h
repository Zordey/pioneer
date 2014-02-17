<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SCENEGRAPH_ANIMATIONKEY_H
#define _SCENEGRAPH_ANIMATIONKEY_H

#include "vector3.h"
#include "Quaternion.h"

namespace SceneGraph {

struct AnimationKey {
	double time;

	AnimationKey(double t) : time(t) { }
};

struct PositionKey : public AnimationKey {
	vector3f position;

	PositionKey(double t, const vector3f &pos)
	: AnimationKey(t)
	, position(pos) { }
};

struct RotationKey : public AnimationKey {
	Quaternionf rotation;

	RotationKey(double t, const Quaternionf &q)
	: AnimationKey(t)
	, rotation(q) { }
};

struct ScaleKey : public AnimationKey {
	vector3f scale;

	ScaleKey(double t, const vector3f &s)
	: AnimationKey(t)
	, scale(s) { }
};

}

#endif
