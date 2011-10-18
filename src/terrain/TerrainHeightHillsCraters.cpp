#include "Terrain.h"
#include "TerrainNoise.h"
#include "TerrainComponent.h"

using namespace TerrainNoise;
using namespace TerrainComponent;

template <>
double TerrainHeightFractal<TerrainHeightHillsCraters>::GetHeight(const vector3d &p)
{
	double continents = octavenoise(GetFracDef(0), 0.5, p) - m_sealevel;
	if (continents < 0) return 0;
	// == TERRAIN_HILLS_NORMAL except river_octavenoise
	double n = 0.3 * continents;
	double distrib = river_octavenoise(GetFracDef(2), 0.5, p);
	double m = GetFracDef(1).amplitude * river_octavenoise(GetFracDef(1), 0.5*distrib, p);
	// cliffs at shore
	if (continents < 0.001) n += m * continents * 1000.0f;
	else n += m;
	n += crater_function(GetFracDef(3), p);
	n += crater_function(GetFracDef(4), p);
	n *= m_maxHeight;
	return (n > 0.0 ? n : 0.0);
}

template <>
void TerrainHeightFractal<TerrainHeightHillsCraters>::InitFracDef(MTRand &rand)
{
}
