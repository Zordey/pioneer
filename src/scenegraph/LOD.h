<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LOD_H
#define _LOD_H
/*
 * Level of detail switch node
 */
#include "Group.h"

namespace SceneGraph {

class LOD : public Group {
public:
	LOD(Graphics::Renderer *r);
	LOD(const LOD&, NodeCopyCache *cache = 0);
	virtual Node *Clone(NodeCopyCache *cache = 0);
	virtual const char *GetTypeName() const { return "LOD"; }
	virtual void Accept(NodeVisitor &v);
	virtual void Render(const matrix4x4f &trans, const RenderData *rd);
	void AddLevel(float pixelRadius, Node *child);
	virtual void Save(NodeDatabase&) override;
	static LOD* Load(NodeDatabase&);

protected:
	virtual ~LOD() { }
	std::vector<unsigned int> m_pixelSizes; //same amount as children
};

}

#endif
