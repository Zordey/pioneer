#ifndef _NEWMODEL_BILLBOARD_H
#define _NEWMODEL_BILLBOARD_H
/*
 * One or more billboard sprites, meant for lights mostly
 */
#include "Node.h"

namespace Newmodel {

class Billboard : public Node {
public:
	Billboard(const std::vector<vector3f>&, RefCountedPtr<Graphics::Material>, float size);
	virtual void Render(Graphics::Renderer *r, const matrix4x4f &trans, RenderData *rd);

private:
	std::vector<vector3f> m_points;
	float m_size;
	RefCountedPtr<Graphics::Material> m_material;
};

}

#endif
