#ifndef _FRUSTUM_H
#define _FRUSTUM_H

#include "libs.h"
#include "vector3.h"

namespace Render {

class Frustum {
public:
	// create from current gl state
	Frustum();

	// create for specified values
	Frustum(float width, float height, float fovAng);

	// apply the saved frustum
	void Enable();

	// restore the previous state
	void Disable();

	// test if point (sphere) is in the frustum
	bool TestPoint(const vector3d &p, double radius) const;
	// test if point (sphere) is in the frustum, ignoring the far plane
	bool TestPointInfinite(const vector3d &p, double radius) const;

	// project a point onto the near plane (typically the screen)
	bool ProjectPoint(vector3d &in, vector3d &out) const;

private:
	void InitFromGLState();

	struct Plane {
		double a, b, c, d;
		double DistanceToPoint(const vector3d &p) const {
			return a*p.x + b*p.y + c*p.z + d;
		}
	};

	GLdouble m_projMatrix[16];
	GLdouble m_modelMatrix[16];
	GLint m_viewport[4];

	Plane m_planes[6];
};

}

#endif
