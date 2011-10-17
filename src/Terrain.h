#ifndef TERRAIN_H
#define TERRAIN_H
#include "libs.h"
#include "StarSystem.h"

#define TERRAIN_MAX_OCTAVES 24

struct fracdef_t {
	double amplitude;
	double frequency;
	double lacunarity;
	int octaves;
};

class Terrain {
	public:
	enum TerrainFractal {
		TERRAIN_NONE,
		TERRAIN_HILLS_NORMAL,
		TERRAIN_HILLS_DUNES,
		TERRAIN_HILLS_RIDGED,
		TERRAIN_HILLS_RIVERS,
		TERRAIN_HILLS_CRATERS,
		TERRAIN_HILLS_CRATERS2,
		TERRAIN_MOUNTAINS_NORMAL,
		TERRAIN_MOUNTAINS_RIDGED,
		TERRAIN_MOUNTAINS_RIVERS,
		TERRAIN_MOUNTAINS_CRATERS,
		TERRAIN_MOUNTAINS_CRATERS2,
		TERRAIN_MOUNTAINS_VOLCANO,
		TERRAIN_MOUNTAINS_RIVERS_VOLCANO,
		TERRAIN_RUGGED_LAVA,
		TERRAIN_H2O_SOLID,
		TERRAIN_H2O_SOLID_CANYONS,
		TERRAIN_RUGGED_DESERT,
		TERRAIN_ASTEROID,
		TERRAIN_FLAT,
		TERRAIN_MAX = TERRAIN_FLAT
	};

	enum ColorFractal {
		COLOR_NONE,
		COLOR_STAR_BROWN_DWARF,
		COLOR_STAR_WHITE_DWARF,
		COLOR_STAR_M,
		COLOR_STAR_K,
		COLOR_STAR_G,
		COLOR_GG_JUPITER,
		COLOR_GG_SATURN,
		COLOR_GG_SATURN2,
		COLOR_GG_URANUS,
		COLOR_GG_NEPTUNE,
		COLOR_GG_NEPTUNE2,
		COLOR_EARTHLIKE,
		COLOR_DEAD_WITH_H2O,
		COLOR_ICEWORLD,
		COLOR_DESERT,
		COLOR_ROCK,
		COLOR_ROCK2,
		COLOR_ASTEROID,
		COLOR_VOLCANIC,
		COLOR_METHANE,
		COLOR_TFGOOD,
		COLOR_TFPOOR,
		COLOR_BANDED_ROCK,
		COLOR_SOLID,
		COLOR_MAX = COLOR_SOLID
	};

	bool textures;
	int m_fracnum;
	double m_fracmult;

	Terrain(const SBody *body);
	~Terrain() {
		if (m_heightMap) delete [] m_heightMap;
		m_heightMap = 0;
	}
	Terrain(): m_terrainType(TERRAIN_NONE), m_colorType(COLOR_NONE) {
		m_heightMap = 0;
	}


	double GetHeightHillsNormal(const vector3d &p);
	double GetHeightHillsDunes(const vector3d &p);
	double GetHeightHillsRidged(const vector3d &p);
	double GetHeightHillsRivers(const vector3d &p);
	double GetHeightHillsCraters(const vector3d &p);
	double GetHeightHillsCraters2(const vector3d &p);
	double GetHeightMountainsNormal(const vector3d &p);
	double GetHeightMountainsRidged(const vector3d &p);
	double GetHeightMountainsRivers(const vector3d &p);
	double GetHeightMountainsCraters(const vector3d &p);
	double GetHeightMountainsCraters2(const vector3d &p);
	double GetHeightMountainsVolcano(const vector3d &p);
	double GetHeightMountainsRiversVolcano(const vector3d &p);
	double GetHeightRuggedLava(const vector3d &p);
	double GetHeightWaterSolid(const vector3d &p);
	double GetHeightWaterSolidCanyons(const vector3d &p);
	double GetHeightRuggedDesert(const vector3d &p);
	double GetHeightAsteroid(const vector3d &p);
	double GetHeightFlat(const vector3d &p);
	
	double GetHeight(const vector3d &p);


	vector3d GetColorStarBrownDwarf(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorStarWhiteDwarf(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorStarM(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorStarK(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorStarG(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGJupiter(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGSaturn(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGSaturn2(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGUranus(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGNeptune(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorGGNeptune2(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorEarthlike(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorDeadWithWater(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorIce(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorDesert(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorRock(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorRock2(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorAsteroid(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorVolcanic(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorMethane(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorTFGood(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorTFPoor(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorBandedRock(const vector3d &p, double height, const vector3d &norm);
	vector3d GetColorSolid(const vector3d &p, double height, const vector3d &norm);

	vector3d GetColor(const vector3d &p, double height, const vector3d &norm);


	void GetAtmosphereFlavor(Color *outColor, double *outDensity) const {
		*outColor = m_atmosColor;
		*outDensity = m_atmosDensity;
	}
	double GetMaxHeight() const { return m_maxHeight; }

	void ChangeDetailLevel();

	private:
	void PickTerrain(MTRand &rand);
	void PickAtmosphere();
	void InitFractalType(MTRand &rand);
	int GetRawHeightMapVal(int x, int y);
	double GetHeightMapVal(const vector3d &pt);
	void InitHeightMap();

	void SetFracDef(unsigned int index, double featureHeightMeters, double featureWidthMeters, MTRand &rand, double smallestOctaveMeters = 20.0);
	inline const fracdef_t &GetFracDef(unsigned int index) { return m_fracdef[index]; }

	const SBody *m_body;

	TerrainFractal m_terrainType;
	ColorFractal m_colorType;
	Uint32 m_seed;

	Color m_atmosColor;
	double m_atmosDensity;
	double m_sealevel; // 0 - no water, 1 - 100% coverage
	double m_icyness; // 0 - 1 (0% to 100% cover)
	double m_volcanic;
	
	/** for sbodies with a heightMap we load this turd
	 * and use it instead of perlin height function */
	Sint16 *m_heightMap;
	int m_heightMapSizeX;
	int m_heightMapSizeY;

	/** General attributes */
	double m_maxHeight;
	double m_maxHeightInMeters;
	double m_invMaxHeight;
	double m_planetRadius;
	double m_planetEarthRadii;
	double m_noise1;
	double m_noise2;
	double m_noise3;

	double m_entropy[12];

	vector3d m_rockColor[8];
	vector3d m_darkrockColor[8];
	vector3d m_greyrockColor[8];
	vector3d m_plantColor[8];
	vector3d m_darkplantColor[8];
	vector3d m_sandColor[8];
	vector3d m_darksandColor[8];
	vector3d m_dirtColor[8];
	vector3d m_darkdirtColor[8];
	vector3d m_gglightColor[8];
	vector3d m_ggdarkColor[8];

	/* XXX you probably shouldn't increase this. If you are
	   using more than 10 then things will be slow as hell */
	fracdef_t m_fracdef[10];
};

#endif /* TERRAIN_H */
