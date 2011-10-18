#ifndef TERRAIN_H
#define TERRAIN_H
#include "libs.h"
#include "StarSystem.h"

struct fracdef_t {
	fracdef_t() { amplitude = frequency = lacunarity = 0.0; octaves = 0; }
	double amplitude;
	double frequency;
	double lacunarity;
	int octaves;
};

class Terrain {
public:
	static Terrain *InstanceTerrain(const SBody *body);
	virtual ~Terrain() {}

	void SetFracDef(unsigned int index, double featureHeightMeters, double featureWidthMeters, MTRand &rand, double smallestOctaveMeters = 20.0);
	inline const fracdef_t &GetFracDef(unsigned int index) { return m_fracdef[index]; }

	virtual double GetHeight(const vector3d &p) = 0;
	virtual vector3d GetColor(const vector3d &p, double height, const vector3d &norm) = 0;

	void GetAtmosphereFlavor(Color *outColor, double *outDensity) const {
		*outColor = m_atmosColor;
		*outDensity = m_atmosDensity;
	}
	double GetMaxHeight() const { return m_maxHeight; }

	void ChangeDetailLevel();

protected:
	Terrain() {}

	bool textures;
	int m_fracnum;
	double m_fracmult;

	void PickTerrain(MTRand &rand);
	void PickAtmosphere();
	void InitFractalType(MTRand &rand);
	int GetRawHeightMapVal(int x, int y);
	double GetHeightMapVal(const vector3d &pt);
	void InitHeightMap();

	const SBody *m_body;

	/*
	TerrainFractal m_terrainType;
	ColorFractal m_colorType;
	*/
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


template <typename HeightFractal>
class TerrainHeightFractal : virtual public Terrain {
public:
	virtual double GetHeight(const vector3d &p);
};

template <typename ColorFractal>
class TerrainColorFractal : virtual public Terrain {
public:
	virtual vector3d GetColor(const vector3d &p, double height, const vector3d &norm);
};


template <typename HeightFractal, typename ColorFractal>
class TerrainGenerator : virtual public Terrain, public TerrainHeightFractal<HeightFractal>, public TerrainColorFractal<ColorFractal> {
};


class TerrainHeightAsteroid;
class TerrainHeightFlat;
class TerrainHeightHillsCraters2;
class TerrainHeightHillsCraters;
class TerrainHeightHillsDunes;
class TerrainHeightHillsNormal;
class TerrainHeightHillsRidged;
class TerrainHeightHillsRivers;
class TerrainHeightMountainsCraters2;
class TerrainHeightMountainsCraters;
class TerrainHeightMountainsNormal;
class TerrainHeightMountainsRidged;
class TerrainHeightMountainsRivers;
class TerrainHeightMountainsRiversVolcano;
class TerrainHeightMountainsVolcano;
class TerrainHeightRuggedDesert;
class TerrainHeightRuggedLava;
class TerrainHeightWaterSolidCanyons;
class TerrainHeightWaterSolid;

class TerrainColorAsteroid;
class TerrainColorBandedRock;
class TerrainColorDeadWithWater;
class TerrainColorDesert;
class TerrainColorEarthLike;
class TerrainColorGGJupiter;
class TerrainColorGGNeptune2;
class TerrainColorGGNeptune;
class TerrainColorGGSaturn2;
class TerrainColorGGSaturn;
class TerrainColorGGUranus;
class TerrainColorIce;
class TerrainColorMethane;
class TerrainColorRock2;
class TerrainColorRock;
class TerrainColorSolid;
class TerrainColorStarBrownDwarf;
class TerrainColorStarG;
class TerrainColorStarK;
class TerrainColorStarM;
class TerrainColorStarWhiteDwarf;
class TerrainColorTFGood;
class TerrainColorTFPoor;
class TerrainColorVolcanic;

	/*
	Terrain(const SBody *body);
	virtual ~Terrain() {
		if (m_heightMap) delete [] m_heightMap;
		m_heightMap = 0;
	}
	*/


	/*
	double GetHeight(const vector3d &p);

	vector3d GetColor(const vector3d &p, double height, const vector3d &norm);
	*/



#endif /* TERRAIN_H */
