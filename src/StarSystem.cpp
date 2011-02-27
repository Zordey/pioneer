#include "StarSystem.h"
#include "Sector.h"
#include "Serializer.h"
#include "NameGenerator.h"

#define CELSIUS	273.15
//#define DEBUG_DUMP

// minimum moon mass a little under Europa's
static const fixed MIN_MOON_MASS = fixed(1,30000); // earth masses
static const fixed MIN_MOON_DIST = fixed(15,10000); // AUs
static const fixed MAX_MOON_DIST = fixed(2, 100); // AUs
// if binary stars have separation s, planets can have stable
// orbits at (0.5 * s * SAFE_DIST_FROM_BINARY)
static const fixed SAFE_DIST_FROM_BINARY = fixed(5,1);
static const fixed PLANET_MIN_SEPARATION = fixed(135,100);

// very crudely
static const fixed AU_SOL_RADIUS = fixed(305,65536);
static const fixed AU_EARTH_RADIUS = fixed(3, 65536);

// indexed by enum type turd  
float StarSystem::starColors[][3] = {
	{ 0, 0, 0 }, // gravpoint
	{ 0.5, 0.0, 0.0 }, // brown dwarf
	{ 1.0, 0.2, 0.0 }, // M
	{ 1.0, 0.6, 0.1 }, // K
	{ 1.0, 1.0, 0.4 }, // G
	{ 1.0, 1.0, 0.8 }, // F
	{ 1.0, 1.0, 1.0 }, // A
	{ 0.7, 0.7, 1.0 }, // B
	{ 1.0, 0.7, 1.0 }, // O
	{ 1.0, 0.2, 0.0 }, // red giant
	{ 0.4, 0.4, 0.8 }, // white dwarf
};

// indexed by enum type turd  
float StarSystem::starRealColors[][3] = {
	{ 0, 0, 0 }, // gravpoint
	{ 0.5, 0.0, 0.0 }, // brown dwarf
	{ 1.0, 0.5, 0.2 }, // M
	{ 1.0, 1.0, 0.4 }, // K
	{ 1.0, 1.0, 0.95 }, // G
	{ 1.0, 1.0, 1.0 }, // F
	{ 1.0, 1.0, 1.0 }, // A
	{ 0.8, 0.8, 1.0 }, // B
	{ 1.0, 0.8, 1.0 },  // O
	{ 1.0, 0.5, 0.2 }, // red giant
	{ 1.0, 1.0, 1.0 }, // white dwarf
};

double StarSystem::starLuminosities[] = {
	0,
	0.0003, // brown dwarf
	0.08, // M0
	0.38, // K0
	1.2, // G0
	5.1, // F0
	24.0, // A0
	24000.0, // B0
	200000.0, // O5
	200000.0, // red giant
	0.1, // white dwarf
};

static const struct StarTypeInfo {
	SBody::BodySuperType supertype;
	int mass[2]; // min,max % sol for stars, unused for planets
	int radius; // % sol radii for stars, % earth radii for planets
	int tempMin, tempMax;
} starTypeInfo[] = {
	{
		SBody::SUPERTYPE_NONE, {}, 0,
	}, {
		SBody::SUPERTYPE_STAR,
		{2,8}, 30,
		1000, 2000
	}, {
		SBody::SUPERTYPE_STAR,
		{10,47}, 50,
		2000, 3500
	}, {
		SBody::SUPERTYPE_STAR,
		{50,78}, 90,
		3500, 5000
	}, { 
		SBody::SUPERTYPE_STAR,
		{80,110}, 110,
		5000, 6000
	}, {
		SBody::SUPERTYPE_STAR,
		{115,170}, 140,
		6000, 7500
	}, {
		SBody::SUPERTYPE_STAR,
		{180,320}, 210,
		7500, 10000
	}, {
		SBody::SUPERTYPE_STAR,
		{400,1800}, 700,
		10000, 30000
	}, {
		SBody::SUPERTYPE_STAR,
		{2000,4000}, 1600,
		30000, 60000
	}, {
		SBody::SUPERTYPE_STAR,
		{60,1000}, 15000,
		2000, 3500
	}, {
		SBody::SUPERTYPE_STAR,
		{20,100}, 1, 
		4000, 40000
	}
/*	}, {
		SBody::SUPERTYPE_GAS_GIANT,
		{}, 950, "Medium gas giant",
	}, {
		SBody::SUPERTYPE_GAS_GIANT,
		{}, 1110, "Large gas giant",
	}, {
		SBody::SUPERTYPE_GAS_GIANT,
		{}, 1500, "Very large gas giant",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 1, "Asteroid",
		"icons/object_planet_asteroid.png"
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 2, "Large asteroid",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 26, "Small, rocky dwarf planet", // moon radius
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 26, "Small, rocky dwarf planet", // dwarf2 for moon-like colours
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 52, "Small, rocky planet with a thin atmosphere", // mars radius
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Rocky frozen planet with a thin nitrogen atmosphere", // earth radius
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Dead world that once housed it's own intricate ecosystem.", // earth radius
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Rocky planet with a carbon dioxide atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Rocky planet with a methane atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Water world with vast oceans and a thick nitrogen atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Rocky planet with a thick carbon dioxide atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Rocky planet with a thick methane atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "Highly volcanic world",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 100, "World with indigenous life and an oxygen atmosphere",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 60, "Marginal terraformed world with minimal plant life",
	}, {
		SBody::SUPERTYPE_ROCKY_PLANET,
		{}, 90, "Fully terraformed world with introduced species from numerous successful colonies",
	}, {
		SBody::SUPERTYPE_STARPORT,
		{}, 0, "Orbital starport",
	}, {
		SBody::SUPERTYPE_STARPORT,
		{}, 0, "Starport",
	}*/
};

SBody::BodySuperType SBody::GetSuperType() const
{
	switch (type) {
		case TYPE_BROWN_DWARF:
		case TYPE_STAR_M:
		case TYPE_STAR_K:
		case TYPE_STAR_G:
		case TYPE_STAR_F:
		case TYPE_STAR_A:
		case TYPE_STAR_B:
		case TYPE_STAR_O:
		case TYPE_STAR_M_GIANT:
		case TYPE_WHITE_DWARF:
		     return SUPERTYPE_STAR;
		case TYPE_PLANET_GAS_GIANT:
		     return SUPERTYPE_GAS_GIANT;
		case TYPE_PLANET_ASTEROID:
		case TYPE_PLANET_TERRESTRIAL:
		     return SUPERTYPE_ROCKY_PLANET;
		case TYPE_STARPORT_ORBITAL:
		case TYPE_STARPORT_SURFACE:
		     return SUPERTYPE_STARPORT;
		case TYPE_GRAVPOINT:
		     return SUPERTYPE_NONE;
	}
}

std::string SBody::GetAstroDescription()
{
	switch (type) {
	case TYPE_BROWN_DWARF: return "Brown dwarf sub-stellar object";
	case TYPE_STAR_M: return "Type 'M' red star";
	case TYPE_STAR_K: return "Type 'K' orange star";
	case TYPE_STAR_G: return "Type 'G' yellow star";
	case TYPE_STAR_F: return "Type 'F' white star";
	case TYPE_STAR_A: return "Type 'A' hot white star";
	case TYPE_STAR_B: return "Bright type 'B' blue star";
	case TYPE_STAR_O: return "Hot, massive type 'O' star";
	case TYPE_STAR_M_GIANT: return "Red giant star";
	case TYPE_WHITE_DWARF: return "White dwarf stellar remnant";
	case TYPE_PLANET_GAS_GIANT:
		if (mass > 800) return "Very large gas giant";
		if (mass > 300) return "Large gas giant";
		if (mass > 80) return "Medium gas giant";
		else return "Small gas giant";
	case TYPE_PLANET_ASTEROID: return "Asteroid";
	case TYPE_PLANET_TERRESTRIAL: {
		std::string s;
		if (mass > fixed(2,1)) s = "Massive";
		else if (mass > fixed(3,2)) s = "Large";
		else if (mass < fixed(1,10)) s = "Tiny";
		else if (mass < fixed(1,5)) s = "Small";

		if (m_volcanicity > fixed(1,2)) {
			if (s.size()) s += ", highly volcanic";
			else s = "Highly volcanic";
		}

		if (m_volatileIces + m_volatileLiquid > fixed(1,5)) {
			if (m_volatileIces > m_volatileLiquid) {
				s += " ice world";
			} else {
				s += " ocean world";
			}
		} else {
			s += " rocky planet";
		}

		if (m_volatileGas < fixed(1,100)) {
			s += " with no significant atmosphere";
		} else {
			std::string thickness;
			if (m_volatileGas < fixed(1,10)) thickness = "tenuous";
			else if (m_volatileGas < fixed(1,5)) thickness = "thin";
			else if (m_volatileGas < fixed(2,1)) {}
			else if (m_volatileGas < fixed(4,1)) thickness = "thick";
			else thickness = "very dense";

			if (m_atmosOxidizing < fixed(1,2)) {
				if (mass > fixed(3,1)) {
					s += " with a "+thickness+" Hydrogen atmosphere";
				} else {
					s += " with a "+thickness+" Methane atmosphere";
				}
			} else {
				if (m_life > fixed(1,2)) {
					s += " with a "+thickness+" Oxygen atmosphere";
				} else {
					s += " with a "+thickness+" Carbon Dioxide atmosphere";
				}
			}
		}

		if (m_life > fixed(1,7)) {
			s += " and advanced indigenous life.";
		} else if (m_life > fixed(0)) {
			s += " and indigenous microbial life.";
		} else {
			s += ".";
		}
		
		return s;
	}
	case TYPE_STARPORT_ORBITAL:
		return "Orbital starport";
	case TYPE_STARPORT_SURFACE:
		return "Starport";
	case TYPE_GRAVPOINT:
		return "<unknown>";
	}
}

const char *SBody::GetIcon()
{
	switch (type) {
	case TYPE_BROWN_DWARF: return "icons/object_brown_dwarf.png";
	case TYPE_STAR_M: return "icons/object_star_m.png";
	case TYPE_STAR_K: return "icons/object_star_k.png";
	case TYPE_STAR_G: return "icons/object_star_g.png";
	case TYPE_STAR_F: return "icons/object_star_f.png";
	case TYPE_STAR_A: return "icons/object_star_a.png";
	case TYPE_STAR_B: return "icons/object_star_b.png";
	case TYPE_STAR_O: return "icons/object_star_o.png";
	case TYPE_STAR_M_GIANT: return "icons/object_star_m_giant.png";
	case TYPE_WHITE_DWARF: return "icons/object_white_dwarf.png";
	case TYPE_PLANET_GAS_GIANT:
		if (mass > 800) return "icons/object_planet_large_gas_giant.png";
		if (mass > 300) return "icons/object_planet_large_gas_giant.png";
		if (mass > 80) return "icons/object_planet_medium_gas_giant.png";
		else return "icons/object_planet_small_gas_giant.png";
	case TYPE_PLANET_ASTEROID:
		return "icons/object_planet_asteroid.png";
	case TYPE_PLANET_TERRESTRIAL:
		if (m_life > fixed(1,7)) return "icons/object_planet_life.png";
		if (m_life > fixed(1,1)) return "icons/object_planet_life3.png";
		if (mass < fixed(1,100)) return "icons/object_planet_dwarf.png";
		if (mass < fixed(1,10)) return "icons/object_planet_small.png";
		if (m_volatileLiquid == 0) return "icons/object_planet_desert.png";
		if (m_volatileLiquid > fixed(1,2)) return "icons/object_planet_water_n2.png";
		if (m_volatileGas > fixed(1,2)) {
			if (m_atmosOxidizing < fixed(1,2)) return "icons/object_planet_methane.png";
			else return "icons/object_planet_co2.png";
		}
		if (m_volcanicity > fixed(1,8)) return "icons/object_planet_volcanic.png";
		return "icons/object_planet_small.png";
		/*
		"icons/object_planet_water_n1.png"
		"icons/object_planet_life3.png"
		"icons/object_planet_life2.png"
		*/
	case TYPE_STARPORT_ORBITAL:
		return "icons/object_orbital_starport.png";
	case TYPE_GRAVPOINT:
	case TYPE_STARPORT_SURFACE:
		return 0;
	}
}

/*
 * Position a surface starport anywhere. Space.cpp::MakeFrameFor() ensures it
 * is on dry land (discarding this position if necessary)
 */
static void position_settlement_on_planet(SBody *b)
{
	MTRand r(b->seed);
	// used for orientation on planet surface
	double r2 = r.Double(); 	// function parameter evaluation order is implementation-dependent
	double r1 = r.Double();		// can't put two rands in the same expression
	b->orbit.rotMatrix = matrix4x4d::RotateZMatrix(2*M_PI*r1) *
			matrix4x4d::RotateYMatrix(2*M_PI*r2);
}

double SBody::GetMaxChildOrbitalDistance() const
{
	double max = 0;
	for (unsigned int i=0; i<children.size(); i++) {
		if (children[i]->orbMax.ToDouble() > max) {
			max = children[i]->orbMax.ToDouble();	
		}
	}
	return AU * max;
}


static inline Sint64 isqrt(Sint64 a)
{
	Sint64 ret=0;
	Sint64 s;
	Sint64 ret_sq=-a-1;
	for(s=62; s>=0; s-=2){
		Sint64 b;
		ret+= ret;
		b=ret_sq + ((2*ret+1)<<s);
		if(b<0){
			ret_sq=b;
			ret++;
		}
	}
	return ret;
}


/*
 * These are the nice floating point surface temp calculating turds.
 *
static const double boltzman_const = 5.6704e-8;
static double calcEnergyPerUnitAreaAtDist(double star_radius, double star_temp, double object_dist)
{
	const double total_solar_emission = boltzman_const *
		star_temp*star_temp*star_temp*star_temp*
		4*M_PI*star_radius*star_radius;

	return total_solar_emission / (4*M_PI*object_dist*object_dist);
}

// bond albedo, not geometric
static double CalcSurfaceTemp(double star_radius, double star_temp, double object_dist, double albedo, double greenhouse)
{
	const double energy_per_meter2 = calcEnergyPerUnitAreaAtDist(star_radius, star_temp, object_dist);
	const double surface_temp = pow(energy_per_meter2*(1-albedo)/(4*(1-greenhouse)*boltzman_const), 0.25);
	return surface_temp;
}
*/
/*
 * Instead we use these butt-ugly overflow-prone spat of ejaculate:
 */
/*
 * star_radius in sol radii
 * star_temp in kelvin,
 * object_dist in AU
 * return Watts/m^2
 */
static fixed calcEnergyPerUnitAreaAtDist(fixed star_radius, int star_temp, fixed object_dist)
{
	fixed temp = star_temp * fixed(1,10000);
	const fixed total_solar_emission =
		temp*temp*temp*temp*star_radius*star_radius;
	
	return fixed(1744665451,100000)*(total_solar_emission / (object_dist*object_dist));
}

static int CalcSurfaceTemp(const SBody *primary, fixed distToPrimary, fixed albedo, fixed greenhouse)
{
	fixed energy_per_meter2;
	if (primary->type == SBody::TYPE_GRAVPOINT) {
		// binary. take energies of both stars
		energy_per_meter2 = calcEnergyPerUnitAreaAtDist(primary->children[0]->radius,
			primary->children[0]->averageTemp, distToPrimary);
		energy_per_meter2 += calcEnergyPerUnitAreaAtDist(primary->children[1]->radius,
			primary->children[1]->averageTemp, distToPrimary);
	} else {
		energy_per_meter2 = calcEnergyPerUnitAreaAtDist(primary->radius, primary->averageTemp, distToPrimary);
	}
	const fixed surface_temp_pow4 = energy_per_meter2*(1-albedo)/(1-greenhouse);
	return (int)isqrt(isqrt((surface_temp_pow4.v>>fixed::FRAC)*4409673));
}

vector3d Orbit::OrbitalPosAtTime(double t)
{
	const double e = eccentricity;
	// mean anomaly
	const double M = 2*M_PI*t / period;
	// eccentric anomaly
	// NR method to solve for E: M = E-sin(E)
	double E = M;
	for (int iter=5; iter > 0; --iter) {
		E = E - (E-e*(sin(E))-M) / (1.0 - e*cos(E));
	}
	// heliocentric distance
	double r = semiMajorAxis * (1.0 - e*cos(E));
	// true anomaly (angle of orbit position)
	double cos_v = (cos(E) - e) / (1.0 - e*cos(E));
	double sin_v = (sqrt(1.0-e*e)*sin(E))/ (1.0 - e*cos(E));

	vector3d pos = vector3d(-cos_v*r, sin_v*r, 0);
	pos = rotMatrix * pos;
	return pos;
}

vector3d Orbit::EvenSpacedPosAtTime(double t)
{
	const double e = eccentricity;
	const double M = 2*M_PI*t;
	const double v = 2*atan(sqrt((1+e)/(1-e)) * tan(M/2.0));
	const double r = semiMajorAxis * (1 - e*e) / (1 + e*cos(v));
	vector3d pos = vector3d(-cos(v)*r, sin(v)*r, 0);
	pos = rotMatrix * pos;
	return pos;
}

double calc_orbital_period(double semiMajorAxis, double centralMass)
{
	return 2.0*M_PI*sqrt((semiMajorAxis*semiMajorAxis*semiMajorAxis)/(G*centralMass));
}

EXPORT_OOLUA_FUNCTIONS_0_NON_CONST(SBodyPath)
EXPORT_OOLUA_FUNCTIONS_8_CONST(SBodyPath,
		GetBodyName, GetSeed, GetSystem, GetParent, GetType, GetSuperType,
		GetNumChildren, GetNthChild)

SBodyPath::SBodyPath(): SysLoc()
{
	sbodyId = 0;
}
SBodyPath::SBodyPath(int sectorX, int sectorY, int systemNum): SysLoc(sectorX, sectorY, systemNum)
{
	sbodyId = 0;
}

void SBodyPath::Serialize(Serializer::Writer &wr) const
{
	SysLoc::Serialize(wr);
	wr.Int32(sbodyId);
}

void SBodyPath::Unserialize(Serializer::Reader &rd, SBodyPath *path)
{
	SysLoc::Unserialize(rd, path);
	path->sbodyId = rd.Int32();
}

const char *SBodyPath::GetBodyName() const
{
	return GetSBody()->name.c_str();
}

int SBodyPath::GetNumChildren() const
{
	return GetSBody()->children.size();
}

Uint32 SBodyPath::GetSeed() const
{
	return GetSBody()->seed;
}

int SBodyPath::GetType() const
{
	return (int)GetSBody()->type;
}

int SBodyPath::GetSuperType() const
{
	return (int)GetSBody()->GetSuperType();
}

const SBody *SBodyPath::GetSBody() const
{
	const StarSystem *s = Sys();
	return s->GetBodyByPath(this);
}
	
SBodyPath *SBodyPath::GetParent() const {
	SBodyPath *p = new SBodyPath;
	const StarSystem *sys = Sys();
	sys->GetPathOf(sys->GetBodyByPath(this)->parent, p);
	return p;
}

SBodyPath *SBodyPath::GetNthChild(int n) const
{
	const StarSystem *sys = Sys();
	const SBody *sbody = GetSBody();
	if ((n < 1) || (n > sbody->children.size())) {
		return 0;
	}
	SBodyPath *p = new SBodyPath;
	sys->GetPathOf(sbody->children[n-1], p);
	return p;
}

template <class T>
static void shuffle_array(MTRand &rand, T *array, int len)
{
	for (int i=0; i<len; i++) {
		int pos = rand.Int32(len);
		T temp = array[i];
		array[i] = array[pos];
		array[pos] = temp;
	}
}

/*
 * Doesn't try very hard
 */
bool StarSystem::GetRandomStarportNearButNotIn(MTRand &rand, SBodyPath *outDest) const
{
	int sx = this->SectorX() + rand.Int32(3) - 1;
	int sy = this->SectorY() + rand.Int32(3) - 1;
	Sector sec(sx, sy);
	const int numSys = sec.m_systems.size();
	int *idxs = new int[numSys];
	// examine the systems in random order
	for (int i=0; i<numSys; i++) idxs[i] = i;
	shuffle_array<int>(rand, idxs, numSys);

	for (int i=0; i<numSys; i++) {
		if ((sx == this->SectorX()) &&
		    (sy == this->SectorY()) &&
		    (idxs[i] == this->SystemIdx())) continue;

		StarSystem *sys = new StarSystem(sx, sy, idxs[i]);

		const int numStations = sys->m_spaceStations.size();
		if (numStations) {
			sys->GetPathOf(sys->m_spaceStations[rand.Int32(numStations)],
					outDest);
			delete sys;
			return true;
		}
		delete sys;
	}
	return false;
}

SBody *StarSystem::GetBodyByPath(const SBodyPath *path) const
{
	assert((m_loc.sectorX == path->sectorX) || (m_loc.sectorY == path->sectorY) ||
	       (m_loc.systemNum == path->systemNum));
	assert(path->sbodyId < m_bodies.size());

	return m_bodies[path->sbodyId];
}

void StarSystem::GetPathOf(const SBody *sbody, SBodyPath *path) const
{
	*path = SBodyPath();

	path->sectorX = m_loc.sectorX;
	path->sectorY = m_loc.sectorY;
	path->systemNum = m_loc.systemNum;
	path->sbodyId = sbody->id;
}

/*
struct CustomSBody {
	const char *name; // null to end system
	SBody::BodyType type;
	int primaryIdx;  // -1 for primary
	fixed radius; // in earth radii for planets, sol radii for stars
	fixed mass; // earth masses or sol masses
	int averageTemp; // kelvin
	fixed semiMajorAxis; // in AUs
	fixed eccentricity;
};
*/
void StarSystem::CustomGetKidsOf(SBody *parent, const std::list<CustomSBody> *children, int *outHumanInfestedness, MTRand &rand)
{
	for (std::list<CustomSBody>::const_iterator i = children->begin(); i != children->end(); i++) {
		const CustomSBody *csbody = &(*i);

		SBody *kid = NewBody();
		kid->type = csbody->type;
		kid->parent = parent;
		kid->seed = rand.Int32();
		kid->radius = csbody->radius;
		kid->mass = csbody->mass;
		kid->averageTemp = csbody->averageTemp;
		kid->name = csbody->name;

		kid->m_metallicity    = csbody->metallicity;
		kid->m_volatileGas    = csbody->volatileGas;
		kid->m_volatileLiquid = csbody->volatileLiquid;
		kid->m_volatileIces   = csbody->volatileIces;
		kid->m_volcanicity    = csbody->volcanicity;
		kid->m_atmosOxidizing = csbody->atmosOxidizing;
		kid->m_life           = csbody->life;

		kid->rotationPeriod = csbody->rotationPeriod;
		kid->eccentricity = csbody->eccentricity;
		kid->axialTilt = csbody->axialTilt;
		kid->semiMajorAxis = csbody->semiMajorAxis;
		kid->orbit.eccentricity = csbody->eccentricity.ToDouble();
		kid->orbit.semiMajorAxis = csbody->semiMajorAxis.ToDouble() * AU;
		kid->orbit.period = calc_orbital_period(kid->orbit.semiMajorAxis, parent->GetMass());
		if (csbody->heightMapFilename.length() > 0) kid->heightMapFilename = csbody->heightMapFilename.c_str();

		if (kid->type == SBody::TYPE_STARPORT_SURFACE) {
			kid->orbit.rotMatrix = matrix4x4d::RotateYMatrix(csbody->longitude) *
				matrix4x4d::RotateXMatrix(-0.5*M_PI + csbody->latitude);
		} else {
			if (kid->orbit.semiMajorAxis < 1.2 * parent->GetRadius()) {
				Error("%s's orbit is too close to its parent", csbody->name.c_str());
			}
			kid->orbit.rotMatrix = matrix4x4d::RotateYMatrix(rand.Double(2*M_PI)) *
				matrix4x4d::RotateXMatrix(-0.5*M_PI + csbody->latitude);
		}
		if (kid->GetSuperType() == SBody::SUPERTYPE_STARPORT) {
			(*outHumanInfestedness)++;
		}
		parent->children.push_back(kid);

		// perihelion and aphelion (in AUs)
		kid->orbMin = csbody->semiMajorAxis - csbody->eccentricity*csbody->semiMajorAxis;
		kid->orbMax = 2*csbody->semiMajorAxis - kid->orbMin;

		CustomGetKidsOf(kid, &csbody->children, outHumanInfestedness, rand);
	}

}

void StarSystem::GenerateFromCustom(const CustomSystem *customSys, MTRand &rand)
{
	const CustomSBody *csbody = &customSys->sBody;

	rootBody = NewBody();
	rootBody->type = csbody->type;
	rootBody->parent = NULL;
	rootBody->seed = rand.Int32();
	rootBody->radius = csbody->radius;
	rootBody->mass = csbody->mass;
	rootBody->averageTemp = csbody->averageTemp;
	rootBody->name = csbody->name;

	int humanInfestedness = 0;
	CustomGetKidsOf(rootBody, &csbody->children, &humanInfestedness, rand);
	Populate(false);

}

void StarSystem::MakeStarOfType(SBody *sbody, SBody::BodyType type, MTRand &rand)
{
	sbody->type = type;
	sbody->radius = fixed(starTypeInfo[type].radius, 100);
	sbody->mass = fixed(rand.Int32(starTypeInfo[type].mass[0],
				starTypeInfo[type].mass[1]), 100);
	sbody->averageTemp = rand.Int32(starTypeInfo[type].tempMin,
				starTypeInfo[type].tempMax);
}

void StarSystem::MakeRandomStar(SBody *sbody, MTRand &rand)
{
	SBody::BodyType type = (SBody::BodyType)rand.Int32((int)SBody::TYPE_STAR_MIN, (int)SBody::TYPE_STAR_MAX);
	MakeStarOfType(sbody, type, rand);
}

void StarSystem::MakeStarOfTypeLighterThan(SBody *sbody, SBody::BodyType type, fixed maxMass, MTRand &rand)
{
	int tries = 16;
	do {
		MakeStarOfType(sbody, type, rand);
	} while ((sbody->mass > maxMass) && (--tries));
}

void StarSystem::MakeBinaryPair(SBody *a, SBody *b, fixed minDist, MTRand &rand)
{
	fixed m = a->mass + b->mass;
	fixed a0 = b->mass / m;
	fixed a1 = a->mass / m;
	a->eccentricity = rand.NFixed(3);
	int mul = 1;

	do {
		switch (rand.Int32(3)) {
			case 2: a->semiMajorAxis = fixed(rand.Int32(100,10000), 100); break;
			case 1: a->semiMajorAxis = fixed(rand.Int32(10,1000), 100); break;
			default:
			case 0: a->semiMajorAxis = fixed(rand.Int32(1,100), 100); break;
		}
		a->semiMajorAxis *= mul;
		mul *= 2;
	} while (a->semiMajorAxis < minDist);

	a->orbit.eccentricity = a->eccentricity.ToDouble();
	a->orbit.semiMajorAxis = AU * (a->semiMajorAxis * a0).ToDouble();
	a->orbit.period = 60*60*24*365* a->semiMajorAxis.ToDouble() * sqrt(a->semiMajorAxis.ToDouble() / m.ToDouble());
	
	const float rotX = -0.5*M_PI;//(float)(rand.Double()*M_PI/2.0);
	const float rotY = (float)rand.Double(M_PI);
	a->orbit.rotMatrix = matrix4x4d::RotateYMatrix(rotY) * matrix4x4d::RotateXMatrix(rotX);
	b->orbit.rotMatrix = matrix4x4d::RotateYMatrix(rotY-M_PI) * matrix4x4d::RotateXMatrix(rotX);

	b->orbit.eccentricity = a->eccentricity.ToDouble();
	b->orbit.semiMajorAxis = AU * (a->semiMajorAxis * a1).ToDouble();
	b->orbit.period = a->orbit.period;
	
	fixed orbMin = a->semiMajorAxis - a->eccentricity*a->semiMajorAxis;
	fixed orbMax = 2*a->semiMajorAxis - orbMin;
	a->orbMin = orbMin;
	b->orbMin = orbMin;
	a->orbMax = orbMax;
	b->orbMax = orbMax;
}

SBody::SBody()
{
	heightMapFilename = 0;
}

/*
 * As my excellent comrades have pointed out, choices that depend on floating
 * point crap will result in different universes on different platforms.
 *
 * We must be sneaky and avoid floating point in these places.
 */
StarSystem::StarSystem(int sector_x, int sector_y, int system_idx)
{
	unsigned long _init[5] = { system_idx, sector_x, sector_y, UNIVERSE_SEED, 0 };
	memset(m_tradeLevel, 0, sizeof(m_tradeLevel));
	m_loc.sectorX = sector_x;
	m_loc.sectorY = sector_y;
	m_loc.systemNum = system_idx;
	rootBody = 0;
	if (system_idx == -1) return;

	Sector s = Sector(sector_x, sector_y);
	if (system_idx >= s.m_systems.size()) return;
	m_seed = s.m_systems[system_idx].seed;
	m_name = s.m_systems[system_idx].name;
	_init[4] = m_seed;
	MTRand rand;
	rand.seed(_init, 5);

	if (s.m_systems[system_idx].customSys) {
		const CustomSystem *custom = s.m_systems[system_idx].customSys;
		if (custom->shortDesc.length() > 0) m_shortDesc = custom->shortDesc;
		if (custom->longDesc.length() > 0) m_longDesc = custom->longDesc;
		if (!custom->IsRandom()) {
			GenerateFromCustom(s.m_systems[system_idx].customSys, rand);
			return;
		}
	}

	SBody *star[4];
	SBody *centGrav1, *centGrav2;

	const int numStars = s.m_systems[system_idx].numStars;
	assert((numStars >= 1) && (numStars <= 4));

	if (numStars == 1) {
		SBody::BodyType type = s.m_systems[system_idx].starType[0];
		star[0] = NewBody();
		star[0]->parent = NULL;
		star[0]->name = s.m_systems[system_idx].name;
		star[0]->orbMin = 0;
		star[0]->orbMax = 0;
		MakeStarOfType(star[0], type, rand);
		rootBody = star[0];
		m_numStars = 1;
	} else {
		centGrav1 = NewBody();
		centGrav1->type = SBody::TYPE_GRAVPOINT;
		centGrav1->parent = NULL;
		centGrav1->name = s.m_systems[system_idx].name+" A,B";
		rootBody = centGrav1;

		SBody::BodyType type = s.m_systems[system_idx].starType[0];
		star[0] = NewBody();
		star[0]->name = s.m_systems[system_idx].name+" A";
		star[0]->parent = centGrav1;
		MakeStarOfType(star[0], type, rand);
		
		star[1] = NewBody();
		star[1]->name = s.m_systems[system_idx].name+" B";
		star[1]->parent = centGrav1;
		MakeStarOfTypeLighterThan(star[1], s.m_systems[system_idx].starType[1],
				star[0]->mass, rand);

		centGrav1->mass = star[0]->mass + star[1]->mass;
		centGrav1->children.push_back(star[0]);
		centGrav1->children.push_back(star[1]);
try_that_again_guvnah:
		MakeBinaryPair(star[0], star[1], fixed(0), rand);

		m_numStars = 2;

		if (numStars > 2) {
			if (star[0]->orbMax > fixed(100,1)) {
				// reduce to < 100 AU...
				goto try_that_again_guvnah;
			}
			// 3rd and maybe 4th star
			if (numStars == 3) {
				star[2] = NewBody();
				star[2]->name = s.m_systems[system_idx].name+" C";
				star[2]->orbMin = 0;
				star[2]->orbMax = 0;
				MakeStarOfTypeLighterThan(star[2], s.m_systems[system_idx].starType[2],
					star[0]->mass, rand);
				centGrav2 = star[2];
				m_numStars = 3;
			} else {
				centGrav2 = NewBody();
				centGrav2->type = SBody::TYPE_GRAVPOINT;
				centGrav2->name = s.m_systems[system_idx].name+" C,D";
				centGrav2->orbMax = 0;

				star[2] = NewBody();
				star[2]->name = s.m_systems[system_idx].name+" C";
				star[2]->parent = centGrav2;
				MakeStarOfTypeLighterThan(star[2], s.m_systems[system_idx].starType[2],
					star[0]->mass, rand);
				
				star[3] = NewBody();
				star[3]->name = s.m_systems[system_idx].name+" D";
				star[3]->parent = centGrav2;
				MakeStarOfTypeLighterThan(star[3], s.m_systems[system_idx].starType[3],
					star[2]->mass, rand);

				MakeBinaryPair(star[2], star[3], fixed(0), rand);
				centGrav2->mass = star[2]->mass + star[3]->mass;
				centGrav2->children.push_back(star[2]);
				centGrav2->children.push_back(star[3]);
				m_numStars = 4;
			}
			SBody *superCentGrav = NewBody();
			superCentGrav->type = SBody::TYPE_GRAVPOINT;
			superCentGrav->parent = NULL;
			superCentGrav->name = s.m_systems[system_idx].name;
			centGrav1->parent = superCentGrav;
			centGrav2->parent = superCentGrav;
			rootBody = superCentGrav;
			const fixed minDist = star[0]->orbMax + star[2]->orbMax;
			MakeBinaryPair(centGrav1, centGrav2, 4*minDist, rand);
			superCentGrav->children.push_back(centGrav1);
			superCentGrav->children.push_back(centGrav2);

		}
	}

	for (int i=0; i<m_numStars; i++) MakePlanetsAround(star[i], rand);

	if (m_numStars > 1) MakePlanetsAround(centGrav1, rand);
	if (m_numStars == 4) MakePlanetsAround(centGrav2, rand);

	Populate(true);

#ifdef DEBUG_DUMP
	Dump();
#endif /* DEBUG_DUMP */
}

#ifdef DEBUG_DUMP
struct thing_t {
	SBody* obj;
	vector3d pos;
	vector3d vel;
};
void StarSystem::Dump()
{
	std::vector<SBody*> obj_stack;
	std::vector<vector3d> pos_stack;
	std::vector<thing_t> output;
	
	SBody *obj = rootBody;
	vector3d pos = vector3d(0.0);

	while (obj) {
		vector3d p2 = pos;
		if (obj->parent) {
			p2 = pos + obj->orbit.OrbitalPosAtTime(1.0);
			pos = pos + obj->orbit.OrbitalPosAtTime(0.0);
		}

		if ((obj->type != SBody::TYPE_GRAVPOINT) &&
		    (obj->GetSuperType() != SBody::SUPERTYPE_STARPORT)) {
			struct thing_t t;
			t.obj = obj;
			t.pos = pos;
			t.vel = (p2-pos);
			output.push_back(t);
		}
		for (std::vector<SBody*>::iterator i = obj->children.begin();
				i != obj->children.end(); ++i) {
			obj_stack.push_back(*i);
			pos_stack.push_back(pos);
		}
		if (obj_stack.size() == 0) break;
		pos = pos_stack.back();
		obj = obj_stack.back();
		pos_stack.pop_back();
		obj_stack.pop_back();
	}

	FILE *f = fopen("starsystem.dump", "w");
	fprintf(f, "%d bodies\n", output.size());
	fprintf(f, "0 steps\n");
	for (std::vector<thing_t>::iterator i = output.begin();
			i != output.end(); ++i) {
		fprintf(f, "B:%lf,%lf:%lf,%lf,%lf,%lf:%lf:%d:%lf,%lf,%lf\n",
				(*i).pos.x, (*i).pos.y, (*i).pos.z,
				(*i).vel.x, (*i).vel.y, (*i).vel.z,
				(*i).obj->GetMass(), 0,
				1.0, 1.0, 1.0);
	}
	fclose(f);
	printf("Junk dumped to starsystem.dump\n");
}
#endif /* DEBUG_DUMP */

/*
 * http://en.wikipedia.org/wiki/Hill_sphere
 */
fixed SBody::CalcHillRadius() const
{
	if (GetSuperType() <= SUPERTYPE_STAR) {
		return fixed(0);
	} else {
		// playing with precision since these numbers get small
		// masses in earth masses
		fixedf<32> mprimary = parent->GetMassInEarths();

		fixedf<48> a = semiMajorAxis;
		fixedf<48> e = eccentricity;

		return fixed(a * (fixedf<48>(1,1)-e) *
				fixedf<48>::CubeRootOf(fixedf<48>(
						mass / (fixedf<32>(3,1)*mprimary))));
		
		//fixed hr = semiMajorAxis*(fixed(1,1) - eccentricity) *
		//  fixedcuberoot(mass / (3*mprimary));
	}
}

static fixed mass_from_disk_area(fixed a, fixed b, fixed max)
{
	// so, density of the disk with distance from star goes like so: 1 - x/discMax
	//
	// --- 
	//    ---
	//       --- <- zero at discMax
	//
	// Which turned into a disc becomes 2*pi*x - (2*pi*x*x)/discMax
	// Integral of which is: pi*x*x - (2/(3*discMax))*pi*x*x*x
	//
	// Because get_disc_density divides total_mass by
	// mass_from_disk_area(0, discMax, discMax) to find density, the
	// constant factors (pi) in this equation drop out.
	//
	b = (b > max ? max : b);
	assert(b>=a);
	assert(a<=max);
	assert(b<=max);
	assert(a>=0);
	fixed one_over_3max = fixed(2,1)/(3*max);
	return (b*b - one_over_3max*b*b*b) -
		(a*a - one_over_3max*a*a*a);
}

static fixed get_disc_density(SBody *primary, fixed discMin, fixed discMax, fixed percentOfPrimaryMass)
{
	discMax = std::max(discMax, discMin);
	fixed total = mass_from_disk_area(discMin, discMax, discMax);
	return primary->GetMassInEarths() * percentOfPrimaryMass / total;
}

void StarSystem::MakePlanetsAround(SBody *primary, MTRand &rand)
{
	fixed discMin = fixed(0);
	fixed discMax = fixed(5000,1);
	fixed discDensity;

	SBody::BodySuperType superType = primary->GetSuperType();

	if (superType <= SBody::SUPERTYPE_STAR) {
		if (primary->type == SBody::TYPE_GRAVPOINT) {
			/* around a binary */
			discMin = primary->children[0]->orbMax * SAFE_DIST_FROM_BINARY;
		} else {
			/* correct thing is roche limit, but lets ignore that because
			 * it depends on body densities and gives some strange results */
			discMin = 4 * primary->radius * AU_SOL_RADIUS;
		}
		if (primary->type == SBody::TYPE_WHITE_DWARF) {
			// white dwarfs will have started as stars < 8 solar
			// masses or so, so pick discMax according to that
			discMax = 100 * rand.NFixed(2);		// rand-splitting again
			discMax *= fixed::SqrtOf(fixed(1,2) + fixed(8,1)*rand.Fixed());
		} else {
			discMax = 100 * rand.NFixed(2)*fixed::SqrtOf(primary->mass);
		}
		// having limited discMin by bin-separation/fake roche, and
		// discMax by some relation to star mass, we can now compute
		// disc density
		discDensity = rand.Fixed() * get_disc_density(primary, discMin, discMax, fixed(2,100));

		if ((superType == SBody::SUPERTYPE_STAR) && (primary->parent)) {
			// limit planets out to 10% distance to star's binary companion
			discMax = std::min(discMax, primary->orbMin * fixed(1,10));
		}

		/* in trinary and quaternary systems don't bump into other pair... */
		if (m_numStars >= 3) {
			discMax = std::min(discMax, fixed(5,100)*rootBody->children[0]->orbMin);
		}
	} else {
		fixed primary_rad = primary->radius * AU_EARTH_RADIUS;
		discMin = 4 * primary_rad;
		/* use hill radius to find max size of moon system. for stars botch it */
		discMax = std::min(discMax, fixed(1,20)*primary->CalcHillRadius());
		
		discDensity = rand.Fixed() * get_disc_density(primary, discMin, discMax, fixed(1,500));
	}

	//fixed discDensity = 20*rand.NFixed(4);

	//printf("Around %s: Range %f -> %f AU\n", primary->name.c_str(), discMin.ToDouble(), discMax.ToDouble());

	fixed initialJump = rand.NFixed(5);
	fixed pos = (fixed(1,1) - initialJump)*discMin + (initialJump*discMax);

	while (pos < discMax) {
		// periapsis, apoapsis = closest, farthest distance in orbit
		fixed periapsis = pos + pos*0.5*rand.NFixed(2);/* + jump */;
		fixed ecc = rand.NFixed(3);
		fixed semiMajorAxis = periapsis / (fixed(1,1) - ecc);
		fixed apoapsis = 2*semiMajorAxis - periapsis;
		if (apoapsis > discMax) break;

		fixed mass;
		{
			const fixed a = pos;
			const fixed b = fixed(135,100)*apoapsis;
			mass = mass_from_disk_area(a, b, discMax);
			mass *= rand.Fixed() * discDensity;
		}

		SBody *planet = NewBody();
		planet->eccentricity = ecc;
		planet->axialTilt = fixed(100,157)*rand.NFixed(2);
		planet->semiMajorAxis = semiMajorAxis;
		planet->type = SBody::TYPE_PLANET_TERRESTRIAL;
		planet->seed = rand.Int32();
		planet->tmp = 0;
		planet->parent = primary;
		planet->mass = mass;
		planet->rotationPeriod = fixed(rand.Int32(1,200), 24);

		planet->orbit.eccentricity = ecc.ToDouble();
		planet->orbit.semiMajorAxis = semiMajorAxis.ToDouble() * AU;
		planet->orbit.period = calc_orbital_period(planet->orbit.semiMajorAxis, primary->GetMass());

		double r1 = rand.Double(2*M_PI);		// function parameter evaluation order is implementation-dependent
		double r2 = rand.NDouble(5);			// can't put two rands in the same expression
		planet->orbit.rotMatrix = matrix4x4d::RotateYMatrix(r1) *
			matrix4x4d::RotateXMatrix(-0.5*M_PI + r2*M_PI/2.0);

		planet->orbMin = periapsis;
		planet->orbMax = apoapsis;
		primary->children.push_back(planet);

		/* minimum separation between planets of 1.35 */
		pos = apoapsis * fixed(135,100);
	}

	int idx=0;
	bool make_moons = superType <= SBody::SUPERTYPE_STAR;
	
	for (std::vector<SBody*>::iterator i = primary->children.begin(); i != primary->children.end(); ++i) {
		// planets around a binary pair [gravpoint] -- ignore the stars...
		if ((*i)->GetSuperType() == SBody::SUPERTYPE_STAR) continue;
		// Turn them into something!!!!!!!
		char buf[8];
		if (superType <= SBody::SUPERTYPE_STAR) {
			// planet naming scheme
			snprintf(buf, sizeof(buf), " %c", 'b'+idx);
		} else {
			// moon naming scheme
			snprintf(buf, sizeof(buf), " %d", 1+idx);
		}
		(*i)->name = primary->name+buf;
		(*i)->PickPlanetType(this, rand);
		if (make_moons) MakePlanetsAround(*i, rand);
		idx++;
	}
}

/*
 * For moons distance from star is not orbMin, orbMax.
 */
const SBody *SBody::FindStarAndTrueOrbitalRange(fixed &orbMin, fixed &orbMax)
{
	const SBody *planet = this;
	const SBody *star = this->parent;

	assert(star);

	/* while not found star yet.. */
	while (star->GetSuperType() > SBody::SUPERTYPE_STAR) {
		planet = star;
		star = star->parent;
	}

	orbMin = planet->orbMin;
	orbMax = planet->orbMax;
	return star;
}

void SBody::PickPlanetType(StarSystem *system, MTRand &rand)
{
	fixed albedo = fixed(0);
	fixed greenhouse = fixed(0);

	fixed minDistToStar, maxDistToStar, averageDistToStar;
	const SBody *star = FindStarAndTrueOrbitalRange(minDistToStar, maxDistToStar);
	averageDistToStar = (minDistToStar+maxDistToStar)>>1;

	/* first calculate blackbody temp (no greenhouse effect, zero albedo) */
	int bbody_temp = CalcSurfaceTemp(star, averageDistToStar, albedo, greenhouse);
	
	averageTemp = bbody_temp;
	radius = fixed::CubeRootOf(mass);
	
	m_metallicity = system->m_metallicity * rand.Fixed();
	// harder to be volcanic when you are tiny (you cool down)
	m_volcanicity = std::min(fixed(1,1), mass) * rand.Fixed();
	m_atmosOxidizing = rand.Fixed();
	m_life = fixed(0);
	m_volatileGas = fixed(0);
	m_volatileLiquid = fixed(0);
	m_volatileIces = fixed(0);

	// pick body type
	if (mass > 317*13) {
		// more than 13 jupiter masses can fuse deuterium - is a brown dwarf
		type = SBody::TYPE_BROWN_DWARF;
		averageTemp = averageTemp + rand.Int32(starTypeInfo[type].tempMin,
					starTypeInfo[type].tempMax);
		// prevent mass exceeding 65 jupiter masses or so, when it becomes a star
		// XXX since TYPE_BROWN_DWARF is supertype star, mass is now in
		// solar masses. what a fucking mess
		mass = std::min(mass, fixed(317*65, 1)) / 332998;
	} else if (mass > 6) {
		type = SBody::TYPE_PLANET_GAS_GIANT;
	} else if (mass > fixed(1, 15000)) {
		type = SBody::TYPE_PLANET_TERRESTRIAL;

		fixed amount_volatiles = fixed(2,1)*rand.Fixed();
		if (rand.Int32(3)) amount_volatiles *= mass;
		// total atmosphere loss
		if (rand.Fixed() > mass) amount_volatiles = fixed(0);

		//printf("Amount volatiles: %f\n", amount_volatiles.ToFloat());
		// fudge how much of the volatiles are in which state
		greenhouse = fixed(0);
		albedo = fixed(0);
		// CO2 sublimation
		if (averageTemp > 195) greenhouse += amount_volatiles * fixed(1,3);
		else albedo += fixed(2,6);
		// H2O liquid
		if (averageTemp > 273) greenhouse += amount_volatiles * fixed(1,5);
		else albedo += fixed(3,6);
		// H2O boils
		if (averageTemp > 373) greenhouse += amount_volatiles * fixed(1,3);

		averageTemp = CalcSurfaceTemp(star, averageDistToStar, albedo, greenhouse);

		const fixed proportion_gas = averageTemp / (fixed(100,1) + averageTemp);
		m_volatileGas = proportion_gas * amount_volatiles;

		const fixed proportion_liquid = (fixed(1,1)-proportion_gas) * (averageTemp / (fixed(50,1) + averageTemp));
		m_volatileLiquid = proportion_liquid * amount_volatiles;

		const fixed proportion_ices = fixed(1,1) - (proportion_gas + proportion_liquid);
		m_volatileIces = proportion_ices * amount_volatiles;

		//printf("temp %dK, gas:liquid:ices %f:%f:%f\n", averageTemp, proportion_gas.ToFloat(),
		//		proportion_liquid.ToFloat(), proportion_ices.ToFloat());

		if ((m_volatileLiquid > fixed(0)) &&
		    (averageTemp > CELSIUS-60) &&
		    (averageTemp < CELSIUS+200)) {
			// try for life
			int minTemp = CalcSurfaceTemp(star, maxDistToStar, albedo, greenhouse);
			int maxTemp = CalcSurfaceTemp(star, minDistToStar, albedo, greenhouse);

			if ((star->type != TYPE_BROWN_DWARF) &&
			    (star->type != TYPE_WHITE_DWARF) &&
			    (star->type != TYPE_STAR_O) &&
			    (minTemp > CELSIUS-10) && (minTemp < CELSIUS+90) &&
			    (maxTemp > CELSIUS-10) && (maxTemp < CELSIUS+90)) {
				m_life = rand.Fixed();
			}
		}
	} else {
		type = SBody::TYPE_PLANET_ASTEROID;
	}
}

void StarSystem::MakeShortDescription(MTRand &rand)
{
	m_econType = 0;
	if ((m_industrial > m_metallicity) && (m_industrial > m_agricultural)) {
		m_econType = ECON_INDUSTRY;
	} else if (m_metallicity > m_agricultural) {
		m_econType = ECON_MINING;
	} else {
		m_econType = ECON_AGRICULTURE;
	}

	/* Total population is in billions */
	if (m_totalPop == 0) {
		int dist = isqrt(1 + m_loc.sectorX*m_loc.sectorX + m_loc.sectorY*m_loc.sectorY);
		if (rand.Int32(dist) > 20) {
			m_shortDesc = "Unexplored system.";
		} else {
			m_shortDesc = "Small-scale prospecting. No registered settlements.";
		}
	} else if (m_totalPop < fixed(1,10)) {
		switch (m_econType) {
			case ECON_INDUSTRY: m_shortDesc = "Small industrial outpost."; break;
			case ECON_MINING: m_shortDesc = "Some established mining."; break;
			case ECON_AGRICULTURE: m_shortDesc = "Young farming colony."; break;
		}
	} else if (m_totalPop < fixed(1,2)) {
		switch (m_econType) {
			case ECON_INDUSTRY: m_shortDesc = "Industrial colony."; break;
			case ECON_MINING: m_shortDesc = "Mining colony."; break;
			case ECON_AGRICULTURE: m_shortDesc = "Outdoor agricultural world."; break;
		}
	} else if (m_totalPop < fixed(5,1)) {
		switch (m_econType) {
			case ECON_INDUSTRY: m_shortDesc = "Heavy industry."; break;
			case ECON_MINING: m_shortDesc = "Extensive mining operations."; break;
			case ECON_AGRICULTURE: m_shortDesc = "Thriving outdoor world."; break;
		}
	} else {
		switch (m_econType) {
			case ECON_INDUSTRY: m_shortDesc = "Industrial hub system."; break;
			case ECON_MINING: m_shortDesc = "Vast strip-mining colony."; break;
			case ECON_AGRICULTURE: m_shortDesc = "High population outdoor world."; break;
		}
	}
}

/* percent */
#define MAX_COMMODITY_BASE_PRICE_ADJUSTMENT 25

void StarSystem::Populate(bool addSpaceStations)
{
	unsigned long _init[5] = { m_loc.systemNum, m_loc.sectorX, m_loc.sectorY, UNIVERSE_SEED };
	MTRand rand;
	rand.seed(_init, 4);

	/* Various system-wide characteristics */
	m_humanProx = fixed(3,1) / isqrt(9 + 10*(m_loc.sectorX*m_loc.sectorX + m_loc.sectorY*m_loc.sectorY));
	m_techlevel = (m_humanProx*5).ToInt32() + rand.Int32(-2,2);
	m_techlevel = Clamp(m_techlevel, 1, 5);
	m_econType = ECON_INDUSTRY;
	m_industrial = rand.Fixed();
	m_agricultural = 0;

	/* system attributes */
	m_totalPop = fixed(0);
	rootBody->PopulateStage1(this, m_totalPop);
	if (m_totalPop == 0) m_techlevel = 0;
	
//	printf("Trading rates:\n");
	// So now we have balances of trade of various commodities.
	// Lets use black magic to turn these into percentage base price
	// alterations
	int maximum = 0;
	for (int i=(int)Equip::FIRST_COMMODITY; i<=(int)Equip::LAST_COMMODITY; i++) {
		maximum = std::max(abs(m_tradeLevel[i]), maximum);
	}
	if (maximum) for (int i=(int)Equip::FIRST_COMMODITY; i<=(int)Equip::LAST_COMMODITY; i++) {
		m_tradeLevel[i] = (m_tradeLevel[i] * MAX_COMMODITY_BASE_PRICE_ADJUSTMENT) / maximum;
		m_tradeLevel[i] += rand.Int32(-5, 5);
	}
	
	for (int i=(int)Equip::FIRST_COMMODITY; i<=(int)Equip::LAST_COMMODITY; i++) {
		Equip::Type t = (Equip::Type)i;
		const EquipType &type = EquipType::types[t];
//		printf("%s: %d%%\n", type.name, m_tradeLevel[t]);
	}
//	printf("System total population %.3f billion, tech level %d\n", m_totalPop.ToFloat(), m_techlevel);
	Polit::GetSysPolitStarSystem(this, m_totalPop, m_polit);

	if (addSpaceStations) {
		rootBody->PopulateAddStations(this);
	}

	MakeShortDescription(rand);
}

/*
 * Set natural resources, tech level, industry strengths and population levels
 */
void SBody::PopulateStage1(StarSystem *system, fixed &outTotalPop)
{
	for (unsigned int i=0; i<children.size(); i++) {
		children[i]->PopulateStage1(system, outTotalPop);
	}
	unsigned long _init[5] = { system->m_loc.systemNum, system->m_loc.sectorX,
			system->m_loc.sectorY, UNIVERSE_SEED, this->seed };
	MTRand rand;
	rand.seed(_init, 5);

	m_population = fixed(0);

	/* Bad type of planet for settlement */
	if ((averageTemp > CELSIUS+100) || (averageTemp < 100) ||
	    (type != SBody::TYPE_PLANET_TERRESTRIAL)) {
		return;
	}

	m_agricultural = fixed(0);

	if (m_life > fixed(9,10)) {
		m_agricultural = Clamp(fixed(1,1) - fixed(CELSIUS+25-averageTemp, 40), fixed(0), fixed(1,1));
		system->m_agricultural += 2*m_agricultural;
	} else if (m_life > fixed(1,2)) {
		m_agricultural = Clamp(fixed(1,1) - fixed(CELSIUS+30-averageTemp, 50), fixed(0), fixed(1,1));
		system->m_agricultural += 1*m_agricultural;
	} else {
		// don't bother populating crap planets
		if (m_metallicity < fixed(5,10)) return;
	}

	const int NUM_CONSUMABLES = 10;
	const Equip::Type consumables[NUM_CONSUMABLES] = { 
		Equip::AIR_PROCESSORS,
		Equip::GRAIN,
		Equip::FRUIT_AND_VEG,
		Equip::ANIMAL_MEAT,
		Equip::LIQUOR,
		Equip::CONSUMER_GOODS,
		Equip::MEDICINES,
		Equip::HAND_WEAPONS,
		Equip::NARCOTICS,
		Equip::LIQUID_OXYGEN
	};

	/* Commodities we produce (mining and agriculture) */
	for (int i=(int)Equip::FIRST_COMMODITY; i<(int)Equip::LAST_COMMODITY; i++) {
		Equip::Type t = (Equip::Type)i;
		const EquipType &type = EquipType::types[t];
		if (type.techLevel > system->m_techlevel) continue;

		fixed affinity = fixed(1,1);
		if (type.econType & ECON_AGRICULTURE) {
			affinity *= 2*m_agricultural;
		}
		if (type.econType & ECON_INDUSTRY) affinity *= system->m_industrial;
		// make industry after we see if agriculture and mining are viable
		if (type.econType & ECON_MINING) {
			affinity *= m_metallicity;
		}
		affinity *= rand.Fixed();
		// producing consumables is wise
		for (int j=0; j<NUM_CONSUMABLES; j++) {
			if (i == consumables[j]) affinity *= 2; break;
		}
		assert(affinity >= 0);
		/* workforce... */
		m_population += affinity * system->m_humanProx;
		
		int howmuch = (affinity * 256).ToInt32();

		system->m_tradeLevel[t] += -2*howmuch;
		for (int i=0; i<EQUIP_INPUTS; i++) {
			if (!type.inputs[i]) continue;
			system->m_tradeLevel[type.inputs[i]] += howmuch;
		}
	}

	if (m_population > fixed(1,10)) NameGenerator::PlanetName(rand);
	
	// Add a bunch of things people consume
	for (int i=0; i<NUM_CONSUMABLES; i++) {
		Equip::Type t = consumables[i];
		if (m_life > fixed(1,2)) {
			// life planets can make this jizz probably
			if ((t == Equip::AIR_PROCESSORS) ||
			    (t == Equip::LIQUID_OXYGEN) ||
			    (t == Equip::GRAIN) ||
			    (t == Equip::FRUIT_AND_VEG) ||
			    (t == Equip::ANIMAL_MEAT)) {
				continue;
			}
		}
		system->m_tradeLevel[t] += rand.Int32(32,128);
	}
	// well, outdoor worlds should have way more people
	m_population = fixed(1,10)*m_population + m_population*m_agricultural;

//	printf("%s: pop %.3f billion\n", name.c_str(), m_population.ToFloat());

	outTotalPop += m_population;
}

void SBody::PopulateAddStations(StarSystem *system)
{
	for (unsigned int i=0; i<children.size(); i++) {
		children[i]->PopulateAddStations(system);
	}
	unsigned long _init[5] = { system->m_loc.systemNum, system->m_loc.sectorX,
			system->m_loc.sectorY, this->seed, UNIVERSE_SEED };
	MTRand rand;
	rand.seed(_init, 5);

	if (m_population < fixed(1,1000)) return;

	fixed pop = m_population + rand.Fixed();

	fixed orbMax = fixed(1,4)*this->CalcHillRadius();
	fixed orbMin = 4 * this->radius * AU_EARTH_RADIUS;
	if (children.size()) orbMax = std::min(orbMax, fixed(1,2) * children[0]->orbMin);

	// starports - orbital
	pop -= rand.Fixed();
	if ((orbMin < orbMax) && (pop >= 0)) {
	
		SBody *sp = system->NewBody();
		sp->type = SBody::TYPE_STARPORT_ORBITAL;
		sp->seed = rand.Int32();
		sp->tmp = 0;
		sp->parent = this;
		sp->rotationPeriod = fixed(1,3600);
		sp->averageTemp = this->averageTemp;
		sp->mass = 0;
		sp->name = NameGenerator::Surname(rand) + " Spaceport";
		/* just always plonk starports in near orbit */
		sp->semiMajorAxis = orbMin;
		sp->eccentricity = fixed(0);
		sp->axialTilt = fixed(0);
		sp->orbit.eccentricity = 0;
		sp->orbit.semiMajorAxis = sp->semiMajorAxis.ToDouble()*AU;
		sp->orbit.period = calc_orbital_period(sp->orbit.semiMajorAxis, this->mass.ToDouble() * EARTH_MASS);
		sp->orbit.rotMatrix = matrix4x4d::Identity();
		children.insert(children.begin(), sp);
		system->m_spaceStations.push_back(sp);
		sp->orbMin = sp->semiMajorAxis;
		sp->orbMax = sp->semiMajorAxis;

		pop -= rand.Fixed();
		if (pop > 0) {
			SBody *sp2 = system->NewBody();
			*sp2 = *sp;
			sp2->orbit.rotMatrix = matrix4x4d::RotateZMatrix(M_PI);
			sp2->name = NameGenerator::Surname(rand) + " Spaceport";
			children.insert(children.begin(), sp2);
			system->m_spaceStations.push_back(sp2);
		}
	}
	// starports - surface
	pop = m_population + rand.Fixed();
	int max = 6;
	while (max-- > 0) {
		pop -= rand.Fixed();
		if (pop < 0) break;

		SBody *sp = system->NewBody();
		sp->type = SBody::TYPE_STARPORT_SURFACE;
		sp->seed = rand.Int32();
		sp->tmp = 0;
		sp->parent = this;
		sp->averageTemp = this->averageTemp;
		sp->mass = 0;
		sp->name = NameGenerator::Surname(rand) + " Starport";
		memset(&sp->orbit, 0, sizeof(Orbit));
		position_settlement_on_planet(sp);
		children.insert(children.begin(), sp);
		system->m_spaceStations.push_back(sp);
	}
}

StarSystem::~StarSystem()
{
	if (rootBody) delete rootBody;
}

bool StarSystem::IsSystem(int sector_x, int sector_y, int system_idx)
{
	return (sector_x == m_loc.sectorX) && (sector_y == m_loc.sectorY) && (system_idx == m_loc.systemNum);
}

SBody::~SBody()
{
	for (std::vector<SBody*>::iterator i = children.begin(); i != children.end(); ++i) {
		delete (*i);
	}
}

void StarSystem::Serialize(Serializer::Writer &wr, StarSystem *s)
{
	if (s) {
		wr.Byte(1);
		wr.Int32(s->m_loc.sectorX);
		wr.Int32(s->m_loc.sectorY);
		wr.Int32(s->m_loc.systemNum);
	} else {
		wr.Byte(0);
	}
}

StarSystem *StarSystem::Unserialize(Serializer::Reader &rd)
{
	if (rd.Byte()) {
		int sec_x = rd.Int32();
		int sec_y = rd.Int32();
		int sys_idx = rd.Int32();
		return new StarSystem(sec_x, sec_y, sys_idx);
	} else {
		return 0;
	}
}

#define STARSYS_MAX_CACHED 8
static std::list<StarSystem*> s_cachedSystems;

StarSystem *StarSystem::GetCached(const SysLoc &loc)
{
	for (std::list<StarSystem*>::iterator i = s_cachedSystems.begin();
			i != s_cachedSystems.end(); ++i) {
		if ((*i)->m_loc == loc) {
			// move to front of cache to indicate it is hot
			StarSystem *s = *i;
			s_cachedSystems.erase(i);
			s_cachedSystems.push_front(s);
			return s;
		}
	}
	StarSystem *s = new StarSystem(loc.sectorX, loc.sectorY, loc.systemNum);
	s_cachedSystems.push_front(s);
	return s;
}

void StarSystem::ShrinkCache()
{
	int n=0;
	for (std::list<StarSystem*>::iterator i = s_cachedSystems.begin();
			i != s_cachedSystems.end(); ++i, n++) {
		if (n >= STARSYS_MAX_CACHED) {
			while (i != s_cachedSystems.end()) {
				delete *i;
				i = s_cachedSystems.erase(i);
			}
			break;
		}
	}
}
