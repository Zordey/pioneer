#include "NModel.h"
#include "CollisionVisitor.h"
#include "DrawVisitor.h"
#include "graphics/Renderer.h"

namespace Newmodel {

NModel::NModel(const std::string &name) : Model(),
	m_name(name)
{
	m_root.Reset(new Group());
}

NModel::~NModel()
{
}

void NModel::Render(Graphics::Renderer *renderer, const matrix4x4f &trans, const LmrObjParams *params)
{
	renderer->SetBlendMode(Graphics::BLEND_SOLID);
	renderer->SetTransform(trans);
	/*DrawVisitor vis(renderer);
	m_root->Accept(vis);*/
	m_root->Render(renderer, trans);
}

CollMesh *NModel::CreateCollisionMesh(const LmrObjParams *p)
{
	CollisionVisitor cv;
	m_root->Accept(cv);
	return cv.CreateCollisionMesh();
}

RefCountedPtr<Graphics::Material> NModel::GetMaterialByName(const std::string &name) const
{
	for (MaterialContainer::const_iterator it = m_materials.begin();
		it != m_materials.end();
		++it)
	{
		if ((*it).first == name) return (*it).second;
	}
	return RefCountedPtr<Graphics::Material>(); //return invalid
}

RefCountedPtr<Graphics::Material> NModel::GetMaterialByIndex(const int i) const
{
	return m_materials.at(Clamp(i, 0, int(m_materials.size())-1)).second;
}

}
