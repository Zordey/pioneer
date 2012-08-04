#include "MaterialLegacy.h"
#include "TextureGL.h"

namespace Graphics {

MaterialLegacy::MaterialLegacy()
: Material()
{
}

void MaterialLegacy::Apply()
{
	glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);

	if (!vertexColors)
		glColor4f(diffuse.r, diffuse.g, diffuse.b, diffuse.a);

	if (unlit) {
		glDisable(GL_LIGHTING);
	} else {
		glEnable(GL_LIGHTING);
		glMaterialfv (GL_FRONT, GL_DIFFUSE, &diffuse[0]);
		//todo: the rest
	}
	if (twoSided) {
		glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
		glDisable(GL_CULL_FACE);
	}
	if (texture0)
		static_cast<TextureGL*>(texture0)->Bind();
}

void MaterialLegacy::Unapply()
{
	glPopAttrib();
	if (texture0)
		static_cast<TextureGL*>(texture0)->Unbind();
}

void StarfieldMaterialLegacy::Apply()
{
	//XXX this probably isn't enough to ensure correct appearance
	glPushAttrib(GL_LIGHTING_BIT | GL_ENABLE_BIT);
	glDisable(GL_POINT_SMOOTH); //too large if smoothing is on
	glPointSize(1.0f);
	glDisable(GL_LIGHTING);
}

}
