#include "NModel.h"
#include "CollisionVisitor.h"
#include "graphics/Renderer.h"

namespace Newmodel {

class LabelUpdateVisitor : public NodeVisitor {
public:
	virtual void ApplyLabel(Label3D &l) {
		l.SetText(label);
	}

	std::string label;
};

NModel::NModel(const std::string &name)
: Model()
, m_lastTime(0.0)
, m_boundingRadius(10.f)
, m_name(name)
{
	m_root.Reset(new Group());
	m_root->SetName(name);
}

NModel::~NModel()
{
	while(!m_animations.empty()) delete m_animations.back(), m_animations.pop_back();
}

void NModel::Render(Graphics::Renderer *renderer, const matrix4x4f &trans, LmrObjParams *params)
{
	renderer->SetBlendMode(Graphics::BLEND_SOLID);
	renderer->SetTransform(trans);
	//using the entire model bounding radius for all nodes at the moment.
	//BR could also be a property of Node.
	params->boundingRadius = GetDrawClipRadius();

	//render in two passes, if this is the top-level model
	if (params->nodemask & MASK_IGNORE) {
		m_root->Render(renderer, trans, params);
	} else {
		params->nodemask = NODE_SOLID;
		m_root->Render(renderer, trans, params);
		params->nodemask = NODE_TRANSPARENT;
		m_root->Render(renderer, trans, params);
	}
}

RefCountedPtr<CollMesh> NModel::CreateCollisionMesh(const LmrObjParams *p)
{
	CollisionVisitor cv;
	m_root->Accept(cv);
	m_collMesh = RefCountedPtr<CollMesh>(cv.CreateCollisionMesh());
	m_boundingRadius = cv.m_boundingRadius;
	return m_collMesh;
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

Group * const NModel::GetTagByIndex(const unsigned int i) const
{
	if (m_tags.empty() || i > m_tags.size()-1) return 0;
	return m_tags.at(i);
}

Group * const NModel::FindTagByName(const std::string &name) const
{
	for (TagContainer::const_iterator it = m_tags.begin();
		it != m_tags.end();
		++it)
	{
		assert(!(*it)->GetName().empty()); //tags must have a name
		if ((*it)->GetName() == name) return (*it);
	}
	return 0;
}

void NModel::AddTag(const std::string &name, Group *node)
{
	if (FindTagByName(name)) return;
	node->SetName(name);
	m_root->AddChild(node);
	m_tags.push_back(node);
}

void NModel::SetPattern(unsigned int index)
{
	for (MaterialContainer::const_iterator it = m_materials.begin();
		it != m_materials.end();
		++it)
	{
		//Set pattern only on a material that supports it
		//XXX hacky using the descriptor
		if ((*it).second->GetDescriptor().usePatterns) {
			(*it).second->texture3 = m_patterns.at(index).texture.Get();
			m_colorMap.SetSmooth(m_patterns.at(index).smoothColor);
		}
	}
}

void NModel::SetColors(Graphics::Renderer *r, const std::vector<Color4ub> &colors)
{
	assert(colors.size() == 3); //primary, seconday, trim
	m_colorMap.Generate(r, colors.at(0), colors.at(1), colors.at(2));
	for (MaterialContainer::const_iterator it = m_materials.begin();
		it != m_materials.end();
		++it)
	{
		//Set colortexture only on a material that uses patterns
		//XXX hacky using the descriptor
		if ((*it).second->GetDescriptor().usePatterns) {
			(*it).second->texture4 = m_colorMap.GetTexture();
		}
	}
}

void NModel::SetDecalTexture(Graphics::Texture *t, unsigned int index)
{
	index = std::min(index, MAX_DECAL_MATERIALS-1);
	if (m_decalMaterials[index].Valid())
		m_decalMaterials[index]->texture0 = t;
}

void NModel::SetLabel(const std::string &text)
{
	LabelUpdateVisitor vis;
	vis.label = text;
	m_root->Accept(vis);
}

void NModel::UpdateAnimations(const double time) //change this to use timestep or something
{
	for (unsigned int i=0; i<m_activeAnimations.size(); i++) {
		m_activeAnimations[i]->Evaluate(time - m_lastTime);
	}
	m_lastTime =  time;
}

int NModel::PlayAnimation(const std::string &name, Animation::Direction dir)
{
	int success = 0;
	m_activeAnimations.clear();
	//should also go through submodels
	for (unsigned int i=0; i<m_animations.size(); i++) {
		Animation *anim = m_animations[i];
		if (anim->GetName() == name) {
			anim->Play(dir);
			m_activeAnimations.push_back(anim);
			success++;
		}
	}
	return success;
}

void NModel::StopAnimations()
{
	for (unsigned int i=0; i<m_animations.size(); i++) {
		m_animations[i]->Stop();
	}
}

}
