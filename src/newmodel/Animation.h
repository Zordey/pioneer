#ifndef _NEWMODEL_ANIMATION_H
#define _NEWMODEL_ANIMATION_H
/*
 * A named animation, such as "GearDown".
 * An animation has a number of channels, each of which
 * animate the position/rotation of a single MatrixTransform node
 */
#include "AnimationChannel.h"

namespace Newmodel {

class Animation {
public:
	enum Direction {
		FORWARD,
		REVERSE
	};
	enum Behavior {
		ONCE,
		LOOP
	};
	Animation(const std::string &name, double duration, Behavior b);
	void Play(Direction = FORWARD);
	void Pause(); //pause or resume playback
	void Stop(); //abort playback and rewind
	void Evaluate(double time);
	std::vector<AnimationChannel> channels;
	double GetDuration() const { return m_duration; }
	double GetTicksPerSecond() const { return m_ticksPerSecond; }
	const std::string &GetName() const { return m_name; }
	const Behavior GetBehavior() const { return m_behavior; }
	void SetBehavior(Behavior b) { m_behavior = b; }

private:
	Behavior m_behavior;
	bool m_paused;
	Direction m_dir;
	double m_currentTime;
	double m_duration;
	double m_lastTime;
	double m_prevMTime;
	double m_ticksPerSecond;
	std::string m_name;
};

}

#endif
