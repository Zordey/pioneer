<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Terrain.h"
#include "TerrainNoise.h"

using namespace TerrainNoise;

template <>
const char *TerrainColorFractal<TerrainColorMethane>::GetColorFractalName() const { return "Methane"; }

template <>
TerrainColorFractal<TerrainColorMethane>::TerrainColorFractal(const SystemBody *body) : Terrain(body)
{
}

template <>
vector3d TerrainColorFractal<TerrainColorMethane>::GetColor(const vector3d &p, double height, const vector3d &norm) const
{
	double n = m_invMaxHeight*height;
	if (n <= 0) return vector3d(.3,.0,.0);
	else return interpolate_color(n, vector3d(.3,.2,.0), vector3d(.6,.3,.0));
}

