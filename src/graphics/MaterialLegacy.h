#ifndef _GRAPHICS_MATERIALLEGACY_H
#define _GRAPHICS_MATERIALLEGAC_H
#include "graphics/Material.h"

namespace Graphics {

class MaterialLegacy : public Material {
public:
	MaterialLegacy();

	virtual void Apply();
	virtual void Unapply();
};

class StarfieldMaterialLegacy : public MaterialLegacy {
public:
	StarfieldMaterialLegacy();

	virtual void Apply();
	virtual void Unapply();
};

};

#endif