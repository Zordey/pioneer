#ifndef _MATERIAL_H
#define _MATERIAL_H

#include "libs.h"
#include <RefCounted.h>

class Texture;
namespace Render {
	class Shader;
}

/*
 * Materials define shading parameters. For example, when you
 * want to draw unlit geometry, define a material with the
 * 'unlit' flag set.
 * It is possible to override the shader choice with the
 * shader parameter (this is a hack, since Render::Shader is GL2 specific)
 */
class Material : public RefCounted {
public:
	Material();

	Texture *texture0;
	//Texture *texture1;
	Color diffuse;
	//Color ambient;
	//Color specular;
	//etc. Implement stuff when you need it, and also support
	//in renderers

	//this could be replaced with shade model: flat, phong etc.
	bool unlit;
	//in practice disables backface culling
	bool twoSided;
	// ignore material color and use vertex colors instead
	bool vertexColors;

	//custom glsl prog
	Render::Shader *shader;
};

#endif
