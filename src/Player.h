#ifndef _PLAYER_H
#define _PLAYER_H

#include <list>
#include "libs.h"
#include "Ship.h"
#include "StarSystem.h"

struct Mission {
	enum MissionState { ACTIVE, COMPLETED, FAILED };

	int          ref;
	std::string  type;
	std::string  client;
	SBodyPath    location;
	double       due;
	Sint64       reward;
	MissionState status;
};

class Player: public Ship {
public:
	OBJDEF(Player, Ship, PLAYER);
	Player(ShipType::Type shipType);
	Player() { m_mouseActive = false; }
	virtual ~Player();
	void PollControls(const float timeStep);
	virtual void Render(const vector3d &viewCoords, const matrix4x4d &viewTransform);
	virtual void SetDockedWith(SpaceStation *, int port);
	void StaticUpdate(const float timeStep);
	enum FlightControlState { CONTROL_MANUAL, CONTROL_FIXSPEED, CONTROL_AUTOPILOT };
	FlightControlState GetFlightControlState() const { return m_flightControlState; }
	void SetFlightControlState(FlightControlState s);
	float GetSetSpeed() const { return m_setSpeed; }
	virtual bool OnDamage(Object *attacker, float kgDamage);
	virtual void OnHaveKilled(Body *guyWeKilled);
	int GetKillCount() const { return m_knownKillCount; }
	virtual bool SetWheelState(bool down); // returns success of state change, NOT state itself

	// test code
	virtual void TimeStepUpdate(const float timeStep);
	vector3d GetAccumTorque() { return m_accumTorque; }
	vector3d m_accumTorque;
	vector3d GetMouseDir() { return m_mouseDir; }

double m_mouseAcc;

	int AddMission(Mission &m);
	void UpdateMission(int ref, Mission &m);
	void RemoveMission(int ref);
	const Mission *GetMission(int ref);
	const std::list<Mission> &GetMissions() { return m_missions; }
	
protected:
	virtual void Save(Serializer::Writer &wr);
	virtual void Load(Serializer::Reader &rd);
private:
	vector3d m_mouseDir;
	double m_mouseX, m_mouseY;
	bool m_mouseActive;
	bool polledControlsThisTurn;
	enum FlightControlState m_flightControlState;
	double m_setSpeed;
	int m_killCount;
	int m_knownKillCount; // updated on docking
	std::list<Mission> m_missions;
};

#endif /* _PLAYER_H */
