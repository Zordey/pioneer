#ifndef _SHIPTYPE_H
#define _SHIPTYPE_H

#include "libs.h"
#include "vector3.h"
#include "EquipType.h"
#include <vector>
#include <map>

struct lua_State;

struct ShipType {
	enum Thruster { // <enum scope='ShipType' name=ShipTypeThruster prefix=THRUSTER_>
		THRUSTER_REVERSE,
		THRUSTER_FORWARD,
		THRUSTER_UP,
		THRUSTER_DOWN,
		THRUSTER_LEFT,
		THRUSTER_RIGHT,
		THRUSTER_MAX // <enum skip>
	};
	enum {
		GUN_FRONT,
		GUN_REAR,
		GUNMOUNT_MAX = 2
	};
	enum Tag { // <enum scope='ShipType' name=ShipTypeTag prefix=TAG_>
		TAG_NONE,
		TAG_SHIP,
		TAG_STATIC_SHIP,
		TAG_MISSILE,
		TAG_MAX // <enum skip>
	};
	typedef std::string Type;

	////////
	Tag tag;
	std::string name;
	std::string lmrModelName;
	float linThrust[THRUSTER_MAX];
	float angThrust;
	struct GunMount {
		vector3f pos;
		vector3f dir;
	} gunMount[GUNMOUNT_MAX];
	int equipSlotCapacity[Equip::SLOT_MAX];
	int capacity; // tonnes
	int hullMass;
	int baseprice;
	Equip::Type hyperdrive;
	///////

	static std::string LADYBIRD;
	static std::string SIRIUS_INTERDICTOR;
	static std::string EAGLE_LRF;
	static std::string EAGLE_MK3;
	static std::string MISSILE_GUIDED;
	static std::string MISSILE_NAVAL;
	static std::string MISSILE_SMART;
	static std::string MISSILE_UNGUIDED;

	static std::map<Type, ShipType> types;
	static std::vector<Type> player_ships;
	static std::vector<Type> static_ships;
	static std::vector<Type> missile_ships;

	static const char *gunmountNames[GUNMOUNT_MAX];
	static void Init();
	static const ShipType *Get(const char *name) {
		std::map<Type, ShipType>::iterator t = types.find(name);
		if (t == types.end()) return 0;
		else return &(*t).second;
	}
};

class EquipSet {
public:
	EquipSet() {}

	void InitSlotSizes(const ShipType::Type t) {
		const ShipType &st = ShipType::types[t];
		for (int i=0; i<Equip::SLOT_MAX; i++) {
			// vector swap idiom (de-allocates unneeded space)
			std::vector<Equip::Type>(st.equipSlotCapacity[i]).swap(equip[i]);
		}
		onChange.emit(Equip::NONE);
	}
	int GetSlotSize(Equip::Slot s) const {
		return equip[s].size();
	}
	Equip::Type Get(Equip::Slot s) const {
		if (equip[s].size() == 0) return Equip::NONE;
		else return equip[s][0];
	}
	Equip::Type Get(Equip::Slot s, int idx) const {
		assert(idx >= 0);
		if (signed(equip[s].size()) <= idx) return Equip::NONE;
		else return equip[s][idx];
	}
	void Set(Equip::Slot s, int idx, Equip::Type e) {
		assert(idx >= 0);
		if (signed(equip[s].size()) <= idx) return;
		equip[s][idx] = e;
		onChange.emit(e);
	}
	int Add(Equip::Type e, int num) {
		assert(num >= 0);
		if (e == Equip::NONE) return 0;
		Equip::Slot s = Equip::types[e].slot;
		int numDone = 0;
		for (unsigned int i=0; (numDone < num) && (i < equip[s].size()); i++) {
			if (equip[s][i] == Equip::NONE) {
				equip[s][i] = e;
				numDone++;
			}
		}
		if (numDone) onChange.emit(e);
		return numDone;
	}
	int Add(Equip::Type e) {
		return Add(e, 1);
	}
	// returns number removed
	int Remove(Equip::Type e, int num) {
		assert(num >= 0);
		if (e == Equip::NONE) return 0;
		Equip::Slot s = Equip::types[e].slot;
		int numDone = 0;
		for (unsigned int i=0; (numDone < num) && (i < equip[s].size()); i++) {
			if (equip[s][i] == e) {
				equip[s][i] = Equip::NONE;
				numDone++;
			}
		}
		if (numDone) onChange.emit(e);
		return numDone;
	}
	int Count(Equip::Slot s, Equip::Type e) const {
		int num = 0;
		for (unsigned int i=0; i<equip[s].size(); i++) {
			if (equip[s][i] == e) num++;
		}
		return num;
	}
	int FreeSpace(Equip::Slot s) const {
		int free = 0;
		for (unsigned int i=0; i<equip[s].size(); i++) {
			if (equip[s][i] == Equip::NONE) free++;
		}
		return free;
	}

	sigc::signal<void,Equip::Type> onChange;
protected:
	std::vector<Equip::Type> equip[Equip::SLOT_MAX];
};


#endif /* _SHIPTYPE_H */
