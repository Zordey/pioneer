<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _PLAYER_H
#define _PLAYER_H

#include "libs.h"
#include <list>
#include "HyperspaceCloud.h"
<<<<<<< HEAD
#include "MarketAgent.h"
#include "Ship.h"
#include "ShipController.h"
#include "galaxy/StarSystem.h"
=======
#include "Ship.h"
#include "ShipController.h"
#include "ShipCockpit.h"
#include "galaxy/StarSystem.h"

namespace Graphics { class Renderer; }
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace Graphics { class Renderer; }

class Player: public Ship, public MarketAgent {
public:
	OBJDEF(Player, Ship, PLAYER);
	Player(ShipType::Id shipId);
<<<<<<< HEAD
	Player() { }; //default constructor used before Load
	virtual void SetDockedWith(SpaceStation *, int port);
	virtual bool OnDamage(Object *attacker, float kgDamage);
=======
	Player() {}; //default constructor used before Load
	virtual void SetDockedWith(SpaceStation *, int port);
	virtual bool OnDamage(Object *attacker, float kgDamage, const CollisionContact& contactData);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	virtual bool SetWheelState(bool down); // returns success of state change, NOT state itself
	virtual Missile * SpawnMissile(ShipType::Id missile_type, int power=-1);
	virtual void SetAlertState(Ship::AlertState as);
	virtual void NotifyRemoved(const Body* const removedBody);

<<<<<<< HEAD
	/* MarketAgent stuff */
	int GetStock(Equip::Type t) const { assert(0); return 0; }
	bool CanBuy(Equip::Type t, bool verbose) const;
	bool CanSell(Equip::Type t, bool verbose) const;
	bool DoesSell(Equip::Type t) const { return true; }
	Sint64 GetPrice(Equip::Type t) const;

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	PlayerShipController *GetPlayerController() const;
	//XXX temporary things to avoid causing too many changes right now
	Body *GetCombatTarget() const;
	Body *GetNavTarget() const;
	Body *GetSetSpeedTarget() const;
	void SetCombatTarget(Body* const target, bool setSpeedTo = false);
	void SetNavTarget(Body* const target, bool setSpeedTo = false);

	virtual Ship::HyperjumpStatus StartHyperspaceCountdown(const SystemPath &dest);
	virtual void ResetHyperspaceCountdown();

<<<<<<< HEAD
=======
	// XXX cockpit is here for now because it has a physics component
	void InitCockpit();
	ShipCockpit* GetCockpit() const {return m_cockpit.get();}
	void OnCockpitActivated();

	virtual void StaticUpdate(const float timeStep);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
protected:
	virtual void Save(Serializer::Writer &wr, Space *space);
	virtual void Load(Serializer::Reader &rd, Space *space);

	virtual void OnEnterSystem();
	virtual void OnEnterHyperspace();

<<<<<<< HEAD
	/* MarketAgent stuff */
	void Bought(Equip::Type t);
	void Sold(Equip::Type t);
=======
private:
	std::unique_ptr<ShipCockpit> m_cockpit;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif /* _PLAYER_H */
