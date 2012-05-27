#ifndef _MODEL_GROUP_H
#define _MODEL_GROUP_H

#include "Node.h"
#include <vector>

namespace Newmodel
{

class Group : public Node
{
public:
	Group() { }
	virtual void AddChild(Node *child);
	virtual bool RemoveChild(Node *node); //true on success
	virtual bool RemoveChildAt(unsigned int position); //true on success
	virtual void Accept(NodeVisitor &v);
	virtual void Render(Graphics::Renderer *r, const matrix4x4f &trans, RenderData *rd);
	unsigned int GetNumChildren() const { return m_children.size(); }
	virtual Node* FindNode(const std::string &);

protected:
	virtual ~Group();
	virtual void RenderChildren(Graphics::Renderer *r, const matrix4x4f &trans, RenderData *rd);
	std::vector<Node *> m_children;
};

}

#endif
