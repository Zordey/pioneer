#include "Material.h"

namespace Graphics {

Material::Material() :
	texture0(0),
	diffuse(1.f), //default white
	emissive(Color::BLACK),
	unlit(false),
	twoSided(false),
	vertexColors(false),
	shader(0),
	newStyleHack(false)
{
}

MaterialDescriptor::MaterialDescriptor()
: effect(EFFECT_DEFAULT)
, lighting(false)
, vertexColors(false)
, twoSided(false)
{
}

}
