<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _MATRIXTRANSFORM_H
#define _MATRIXTRANSFORM_H
/*
 * Applies a matrix transform to child nodes
 */
#include "Group.h"
#include "matrix4x4.h"
namespace Graphics { class Renderer; }

namespace SceneGraph {
class MatrixTransform : public Group {
public:
	MatrixTransform(Graphics::Renderer *r, const matrix4x4f &m);
	MatrixTransform(const MatrixTransform&, NodeCopyCache *cache = 0);
	virtual Node *Clone(NodeCopyCache *cache = 0);
	virtual const char *GetTypeName() const { return "MatrixTransform"; }
	virtual void Accept(NodeVisitor &v);
<<<<<<< HEAD
=======
	virtual Node* GatherTransforms(const std::string &, const matrix4x4f &, matrix4x4f &);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void Render(const matrix4x4f &trans, const RenderData *rd);
	const matrix4x4f &GetTransform() const { return m_transform; }
	void SetTransform(const matrix4x4f &m) { m_transform = m; }

protected:
	virtual ~MatrixTransform() { }

private:
	matrix4x4f m_transform;
};
}
#endif
