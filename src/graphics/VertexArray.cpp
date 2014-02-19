<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "VertexArray.h"

namespace Graphics {

VertexArray::VertexArray(AttributeSet attribs, int size)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_attribs = attribs;

	if (size > 0) {
		//would be rather weird without positions!
		if (attribs & ATTRIB_POSITION)
			position.reserve(size);
		if (attribs & ATTRIB_DIFFUSE)
			diffuse.reserve(size);
		if (attribs & ATTRIB_NORMAL)
			normal.reserve(size);
		if (attribs & ATTRIB_UV0)
			uv0.reserve(size);
	}
}

VertexArray::~VertexArray()
{

}

bool VertexArray::HasAttrib(VertexAttrib v) const
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return (m_attribs & v) != 0;
}

unsigned int VertexArray::GetNumVerts() const
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return position.size();
}

void VertexArray::Clear()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.clear();
	diffuse.clear();
	normal.clear();
	uv0.clear();
}

void VertexArray::Add(const vector3f &v)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
}

void VertexArray::Add(const vector3f &v, const Color &c)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
	diffuse.push_back(c);
}

void VertexArray::Add(const vector3f &v, const Color &c, const vector3f &n)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
	diffuse.push_back(c);
	normal.push_back(n);
}

void VertexArray::Add(const vector3f &v, const Color &c, const vector2f &uv)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
	diffuse.push_back(c);
	uv0.push_back(uv);
}

void VertexArray::Add(const vector3f &v, const vector2f &uv)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
	uv0.push_back(uv);
}

void VertexArray::Add(const vector3f &v, const vector3f &n, const vector2f &uv)
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	position.push_back(v);
	normal.push_back(n);
	uv0.push_back(uv);
}

<<<<<<< HEAD
=======
void VertexArray::Set(const Uint32 idx, const vector3f &v)
{
	PROFILE_SCOPED()
	position[idx] = v;
}

void VertexArray::Set(const Uint32 idx, const vector3f &v, const Color &c)
{
	PROFILE_SCOPED()
	position[idx] = v;
	diffuse[idx] = c;
}

void VertexArray::Set(const Uint32 idx, const vector3f &v, const Color &c, const vector3f &n)
{
	PROFILE_SCOPED()
	position[idx] = v;
	diffuse[idx] = c;
	normal[idx] = n;
}

void VertexArray::Set(const Uint32 idx, const vector3f &v, const Color &c, const vector2f &uv)
{
	PROFILE_SCOPED()
	position[idx] = v;
	diffuse[idx] = c;
	uv0[idx] = uv;
}

void VertexArray::Set(const Uint32 idx, const vector3f &v, const vector2f &uv)
{
	PROFILE_SCOPED()
	position[idx] = v;
	uv0[idx] = uv;
}

void VertexArray::Set(const Uint32 idx, const vector3f &v, const vector3f &n, const vector2f &uv)
{
	PROFILE_SCOPED()
	position[idx] = v;
	normal[idx] = n;
	uv0[idx] = uv;
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}
