<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Uniform.h"
#include "graphics/TextureGL.h"

namespace Graphics {
namespace GL2 {

Uniform::Uniform()
: m_location(-1)
{
}

void Uniform::Init(const char *name, GLuint program)
{
	m_location = glGetUniformLocation(program, name);
}

void Uniform::Set(int i)
{
	if (m_location != -1)
		glUniform1i(m_location, i);
}

void Uniform::Set(float f)
{
	if (m_location != -1)
		glUniform1f(m_location, f);
}

void Uniform::Set(const vector3f &v)
{
	if (m_location != -1)
		glUniform3f(m_location, v.x, v.y, v.z);
}

void Uniform::Set(const vector3d &v)
{
	if (m_location != -1)
		glUniform3f(m_location, v.x, v.y, v.z); //yes, 3f
}

<<<<<<< HEAD
void Uniform::Set(const Color4f &c)
{
	if (m_location != -1)
		glUniform4f(m_location, c.r, c.g, c.b, c.a);
=======
void Uniform::Set(const Color &c)
{
	Color4f c4f = c.ToColor4f();
	if (m_location != -1)
		glUniform4f(m_location, c4f.r, c4f.g, c4f.b, c4f.a);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Uniform::Set(const int v[3])
{
	if (m_location != -1)
		glUniform3i(m_location, v[0],v[1],v[2]);
}

void Uniform::Set(const float m[9])
{
	if (m_location != -1)
		glUniformMatrix3fv(m_location, 1, false, m);
}

<<<<<<< HEAD
=======
void Uniform::Set(const matrix3x3f &m)
{
	if (m_location != -1)
		glUniformMatrix3fv(m_location, 1, false, &m[0]);
}

void Uniform::Set(const matrix4x4f &m)
{
	if (m_location != -1)
		glUniformMatrix4fv(m_location, 1, false, &m[0]);
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
void Uniform::Set(Texture *tex, unsigned int unit)
{
	if (m_location != -1 && tex) {
		glActiveTexture(GL_TEXTURE0 + unit);
		static_cast<TextureGL*>(tex)->Bind();
		glUniform1i(m_location, unit);
	}
}

}
}
