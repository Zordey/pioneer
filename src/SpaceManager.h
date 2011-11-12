#ifndef _SPACEMANAGER_H
#define _SPACEMANAGER_H

// SpaceManager takes care of creating and destroying spaces as the player
// moves from system to hyperspace to system

#include "vector3.h"
#include "SystemPath.h"

class Space;
class Player;
class HyperspaceCloud;

class SpaceManager {
public:
	enum State {
		STATE_NONE,
		STATE_NORMAL,
		STATE_HYPERSPACE,
	};

	SpaceManager(Player *player) : m_player(player), m_state(STATE_NONE), m_space(0), m_wantHyperspace(false) {}

	State GetState() const { return m_state; }
	Space *GetSpace() const { return m_space; }

	void CreateSpaceForDockedStart(const SystemPath &path);
	void CreateSpaceForFreeStart(const SystemPath &path, const vector3d &pos);

	void WantHyperspace();

	void TimeStep(float step);

	float GetHyperspaceProgress() const { return m_hyperspaceProgress; }
	double GetHyperspaceDuration() const { return m_hyperspaceDuration; }
	double GetHyperspaceEndTime() const { return m_hyperspaceEndTime; }

private:
	void SwitchToHyperspace();
	void SwitchToNormalSpace();

	Player *m_player;

	State m_state;
	Space *m_space;

	bool m_wantHyperspace;

	std::list<HyperspaceCloud*> m_hyperspaceClouds;
	SystemPath m_hyperspaceSource;
	float m_hyperspaceProgress;
	double m_hyperspaceDuration;
	double m_hyperspaceEndTime;
};

#endif
