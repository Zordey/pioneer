<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _SECTOR_H
#define _SECTOR_H

#include "libs.h"
#include "galaxy/SystemPath.h"
#include "galaxy/StarSystem.h"
#include "galaxy/CustomSystem.h"
<<<<<<< HEAD
=======
#include "SectorCache.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#include <string>
#include <vector>

class Faction;

class Sector : public RefCounted {
	friend class SectorCache;

public:
	// lightyears
	static const float SIZE;
	~Sector();

	static float DistanceBetween(RefCountedPtr<const Sector> a, int sysIdxA, RefCountedPtr<const Sector> b, int sysIdxB);
	static void Init();

<<<<<<< HEAD
=======
	static SectorCache cache;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	// Sector is within a bounding rectangle - used for SectorView m_sectorCache pruning.
	bool WithinBox(const int Xmin, const int Xmax, const int Ymin, const int Ymax, const int Zmin, const int Zmax) const;
	bool Contains(const SystemPath sysPath) const;

	// get the SystemPath for this sector
	SystemPath GetSystemPath() const { return SystemPath(sx, sy, sz); }

	class System {
	public:
		System(int x, int y, int z, Uint32 si): customSys(0), population(-1), explored(false), sx(x), sy(y), sz(z), idx(si) {};
		~System() {};

		// Check that we've had our habitation status set

		// public members
		std::string name;
		vector3f p;
		int numStars;
		SystemBody::BodyType starType[4];
		Uint32 seed;
		const CustomSystem *customSys;
		Faction *faction;
		fixed population;
		bool explored;

		vector3f FullPosition() { return Sector::SIZE*vector3f(float(sx), float(sy), float(sz)) + p; };
		bool IsSameSystem(const SystemPath &b) const {
			return sx == b.sectorX && sy == b.sectorY && sz == b.sectorZ && idx == b.systemIndex;
		}

		int sx, sy, sz;
		Uint32 idx;
	};
	std::vector<System> m_systems;

private:
	Sector(const Sector&); // non-copyable
	Sector& operator=(const Sector&); // non-assignable

	int sx, sy, sz;
	void GetCustomSystems();
<<<<<<< HEAD
	std::string GenName(System &sys, int si, Random &rand);
=======
	const std::string GenName(System &sys, int si, Random &rand);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif /* _SECTOR_H */
