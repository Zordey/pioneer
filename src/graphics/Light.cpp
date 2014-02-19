<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Light.h"

namespace Graphics {

Light::Light() :
	m_type(LIGHT_POINT),
	m_position(0.f),
<<<<<<< HEAD
	m_diffuse(Color(1.f)),
	m_specular(Color(0.f))
=======
	m_diffuse(Color(255)),
	m_specular(Color(0))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{

}

Light::Light(LightType t, const vector3f &p, const Color &d, const Color &s) :
	m_type(t),
	m_position(p),
	m_diffuse(d),
	m_specular(s)
{

}

}
