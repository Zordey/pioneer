<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _MISSILE_H
#define _MISSILE_H

#include <list>
#include "libs.h"
#include "Ship.h"

class Missile: public Ship {
public:
	OBJDEF(Missile, Ship, MISSILE);
	Missile(ShipType::Id type, Body *owner, int power=-1);
	Missile() {}
	virtual ~Missile() {}
	void TimeStepUpdate(const float timeStep);
	virtual bool OnCollision(Object *o, Uint32 flags, double relVel);
<<<<<<< HEAD
	virtual bool OnDamage(Object *attacker, float kgDamage);
=======
	virtual bool OnDamage(Object *attacker, float kgDamage, const CollisionContact& contactData);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	virtual void NotifyRemoved(const Body* const removedBody);
	virtual void PostLoadFixup(Space *space);
	void ECMAttack(int power_val);
	Body *GetOwner() const { return m_owner; }
	bool IsArmed() const {return m_armed;}
	void Arm();
	void Disarm();

protected:
	virtual void Save(Serializer::Writer &wr, Space *space);
	virtual void Load(Serializer::Reader &rd, Space *space);
private:
	void Explode();

	int m_power;
	Body *m_owner;
	bool m_armed;

	int m_ownerIndex; // deserialisation
};

#endif /* _MISSILE_H */
