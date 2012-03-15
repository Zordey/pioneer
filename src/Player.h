#ifndef _PLAYER_H
#define _PLAYER_H

#include "libs.h"
#include <list>
#include "HyperspaceCloud.h"
#include "MarketAgent.h"
#include "RefList.h"
#include "Ship.h"
#include "ShipController.h"
#include "StarSystem.h"

namespace Graphics { class Renderer; }

struct Mission : RefItem<Mission> {
	enum MissionState { // <enum scope='Mission' name=MissionStatus>
		ACTIVE,
		COMPLETED,
		FAILED,
	};

	std::string  type;
	std::string  client;
	SystemPath   location;
	double       due;
	Sint64       reward;
	MissionState status;
};

class Player: public Ship, public MarketAgent {
public:
	OBJDEF(Player, Ship, PLAYER);
	Player(ShipType::Type shipType);
	Player() { }; //default constructor used before Load
	virtual void Render(Graphics::Renderer *r, const vector3d &viewCoords, const matrix4x4d &viewTransform);
	virtual void SetDockedWith(SpaceStation *, int port);
	virtual bool OnDamage(Object *attacker, float kgDamage);
	virtual void OnHaveKilled(Body *guyWeKilled);
	int GetKillCount() const { return m_knownKillCount; }
	virtual bool SetWheelState(bool down); // returns success of state change, NOT state itself
	virtual bool FireMissile(int idx, Ship *target);
	virtual void SetAlertState(Ship::AlertState as);
	void SetNavTarget(Body* const target, bool setSpeedTo = false);
	Body *GetNavTarget() const { return m_navTarget; }
	void SetCombatTarget(Body* const target, bool setSpeedTo = false);
	Body *GetCombatTarget() const { return m_combatTarget; }
	Body *GetSetSpeedTarget() const { return m_setSpeedTarget; }
	virtual void NotifyRemoved(const Body* const removedBody);

	RefList<Mission> missions;

	virtual void PostLoadFixup(Space *space);

	/* MarketAgent stuff */
	int GetStock(Equip::Type t) const { assert(0); return 0; }
	bool CanBuy(Equip::Type t, bool verbose) const;
	bool CanSell(Equip::Type t, bool verbose) const;
	bool DoesSell(Equip::Type t) const { return true; }
	Sint64 GetPrice(Equip::Type t) const;

	//XXX temporary things
	bool IsMouseActive() const;
	double GetSetSpeed() const;
	FlightControlState GetFlightControlState() const;
	vector3d GetMouseDir() const;
	void SetFlightControlState(FlightControlState s);
	void SetMouseForRearView(bool enable);

protected:
	virtual void Save(Serializer::Writer &wr, Space *space);
	virtual void Load(Serializer::Reader &rd, Space *space);

	virtual void OnEnterSystem();
	virtual void OnEnterHyperspace();

	/* MarketAgent stuff */
	void Bought(Equip::Type t);
	void Sold(Equip::Type t);

private:
	Body* m_combatTarget;
	Body* m_navTarget;
	Body* m_setSpeedTarget;
	int m_killCount;
	int m_knownKillCount; // updated on docking

	int m_combatTargetIndex, m_navTargetIndex, m_setSpeedTargetIndex; // deserialisation
};

#endif /* _PLAYER_H */
