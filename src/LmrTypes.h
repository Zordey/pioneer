#ifndef _LMRTYPES_H
#define _LMRTYPES_H

class EquipSet;

//this file might be temporary - but don't want to fight dependency issues right now
struct LmrMaterial {
	float diffuse[4];
	float specular[4];
	float emissive[4];
	float shininess;
	// make sure save and load routines in ShipFlavour are matching
};

struct LmrObjParams
{
	enum { LMR_ANIMATION_MAX = 10 };

	const char *animationNamespace; // the namespace to look up animation names in, from LuaConstants

	double time;
	int animStages[LMR_ANIMATION_MAX];
	double animValues[LMR_ANIMATION_MAX];
	const char *label;
	const EquipSet *equipment; // for ships
	int flightState;

	float linthrust[3];		// 1.0 to -1.0
	float angthrust[3];		// 1.0 to -1.0

	struct LmrMaterial pMat[3];

	//stuff added after newmodel
	int scrWidth;
	float boundingRadius; //updated by model and passed to submodels
	bool drawBoundingBoxes;

	LmrObjParams()
	: scrWidth(800)
	, boundingRadius(0.f)
	, drawBoundingBoxes(false)
	{ }
};
typedef LmrObjParams ModelParams;
typedef LmrObjParams RenderData;

#endif
