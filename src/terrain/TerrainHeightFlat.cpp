#include "Terrain.h"

template <>
double TerrainHeightFractal<TerrainHeightFlat>::GetHeight(const vector3d &p)
{
	return 0.0;
}

template <>
TerrainHeightFractal<TerrainHeightFlat>::TerrainHeightFractal(const SBody *body) : Terrain(body)
{
}
