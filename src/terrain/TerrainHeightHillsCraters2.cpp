#include "Terrain.h"
#include "TerrainNoise.h"
#include "TerrainComponent.h"

using namespace TerrainNoise;
using namespace TerrainComponent;

template <>
double TerrainHeightFractal<TerrainHeightHillsCraters2>::GetHeight(const vector3d &p)
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
	n += crater_function(GetFracDef(5), p);
	n += crater_function(GetFracDef(6), p);
	n += crater_function(GetFracDef(7), p);
	n += crater_function(GetFracDef(8), p);
	n *= m_maxHeight;
	return (n > 0.0 ? n : 0.0);
}

template <>
void TerrainHeightFractal<TerrainHeightHillsCraters2>::InitFracDef(MTRand &rand)
{
	SetFracDef(0, m_maxHeightInMeters, rand.Double(1e6,1e7), rand);
	double height = m_maxHeightInMeters*0.6;
	SetFracDef(1, height, rand.Double(4.0, 20.0)*height, rand);
	SetFracDef(2, m_maxHeightInMeters, rand.Double(50.0, 100.0)*m_maxHeightInMeters, rand);
	SetFracDef(3, m_maxHeightInMeters*0.07, 11e5, rand, 1000.0*m_fracmult);
	SetFracDef(4, m_maxHeightInMeters*0.05, 98e4, rand, 800.0*m_fracmult);
	SetFracDef(5, m_maxHeightInMeters*0.05, 1e6, rand, 400.0*m_fracmult);
	SetFracDef(6, m_maxHeightInMeters*0.04, 99e4, rand, 200.0*m_fracmult);
	SetFracDef(7, m_maxHeightInMeters*0.05, 12e5, rand, 100.0*m_fracmult);
	SetFracDef(8, m_maxHeightInMeters*0.04, 9e5, rand, 100.0*m_fracmult);
}
