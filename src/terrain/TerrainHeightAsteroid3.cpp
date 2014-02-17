<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Terrain.h"
#include "TerrainNoise.h"
#include "TerrainFeature.h"

using namespace TerrainNoise;
using namespace TerrainFeature;

// Banded/Ridged pattern mountainous terrain, could pass for desert

template <>
const char *TerrainHeightFractal<TerrainHeightAsteroid3>::GetHeightFractalName() const { return "Asteroid3"; }

template <>
TerrainHeightFractal<TerrainHeightAsteroid3>::TerrainHeightFractal(const SystemBody *body) : Terrain(body)
{
}

template <>
double TerrainHeightFractal<TerrainHeightAsteroid3>::GetHeight(const vector3d &p) const
{
	double n = octavenoise(8, 0.5, 4.0, p) * ridged_octavenoise(8, 0.5, 4.0, p);

	return (n > 0.0? m_maxHeight*n : 0.0);
}
