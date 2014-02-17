<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Material.h"

namespace Graphics {

Material::Material() :
	texture0(0),
	texture1(0),
	texture2(0),
	texture3(0),
	texture4(0),
<<<<<<< HEAD
=======
	heatGradient(0),
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	diffuse(Color::WHITE),
	specular(Color::BLACK),
	emissive(Color::BLACK),
	shininess(100), //somewhat sharp
	twoSided(false),
	specialParameter0(0)
{
}

MaterialDescriptor::MaterialDescriptor()
: effect(EFFECT_DEFAULT)
, alphaTest(false)
<<<<<<< HEAD
, atmosphere(false)
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
, glowMap(false)
, lighting(false)
, specularMap(false)
, twoSided(false)
, usePatterns(false)
, vertexColors(false)
, textures(0)
, dirLights(0)
<<<<<<< HEAD
=======
, quality(0)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
}

bool operator==(const MaterialDescriptor &a, const MaterialDescriptor &b)
{
	return (
		a.effect == b.effect &&
		a.alphaTest == b.alphaTest &&
<<<<<<< HEAD
		a.atmosphere == b.atmosphere &&
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		a.glowMap == b.glowMap &&
		a.lighting == b.lighting &&
		a.specularMap == b.specularMap &&
		a.twoSided == b.twoSided &&
		a.usePatterns == b.usePatterns &&
		a.vertexColors == b.vertexColors &&
		a.textures == b.textures &&
<<<<<<< HEAD
		a.dirLights == b.dirLights
=======
		a.dirLights == b.dirLights &&
		a.quality == b.quality
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	);
}

}
