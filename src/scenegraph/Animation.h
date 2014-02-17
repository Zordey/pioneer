<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SCENEGRAPH_ANIMATION_H
#define _SCENEGRAPH_ANIMATION_H
/*
 * A named animation, such as "GearDown".
 * An animation has a number of channels, each of which
 * animate the position/rotation of a single MatrixTransform node
 */
#include "AnimationChannel.h"

namespace SceneGraph {

class Loader;
class Node;

class Animation {
public:
	Animation(const std::string &name, double duration);
	Animation(const Animation&);
	void UpdateChannelTargets(Node *root);
	double GetDuration() const { return m_duration; }
	const std::string &GetName() const { return m_name; }
	double GetProgress();
	void SetProgress(double); //0.0 -- 1.0, overrides m_time
	void Interpolate(); //update transforms according to m_time;

private:
	friend class Loader;
	double m_duration;
	double m_time;
	std::string m_name;
	std::vector<AnimationChannel> m_channels;
};

}

#endif
