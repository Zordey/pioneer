#include "Surface.h"

Surface::Surface(PrimitiveType t) :
	m_primitiveType(t),
	m_material(0),
	m_vertices(0)
{
}

Surface::~Surface()
{
	delete m_vertices;
}

void Surface::SetVertices(VertexArray *v)
{
	if (m_vertices) delete m_vertices;

	m_vertices = v;
}

int Surface::GetNumVerts() const
{
	if (m_vertices)
		return m_vertices->position.size();
	else
		return 0;
}
