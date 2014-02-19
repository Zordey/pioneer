<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _BVHTREE_H
#define _BVHTREE_H

#include <assert.h>
#include <vector>
#include "../vector3.h"
#include "../Aabb.h"
#include "../utils.h"
<<<<<<< HEAD

#define MAX_SPLITPOS_RETRIES 15
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

struct BVHNode {
	Aabb aabb;

	/* if triIndicesStart == 0 then not leaf,
	 * kids[] valid */
	int numTris;
	int *triIndicesStart;

	BVHNode *kids[2];

	BVHNode() {
		kids[0] = 0;
		triIndicesStart = 0;
	}
	bool IsLeaf() const {
		return triIndicesStart != 0;
	}
};

class BVHTree {
public:
	typedef int objPtr_t;
	BVHTree(int numObjs, const objPtr_t *objPtrs, const Aabb *objAabbs);
	~BVHTree() {
		delete [] m_objPtrAlloc;
		delete [] m_bvhNodes;
	}
	BVHNode *GetRoot() { return m_root; }
private:
	void BuildNode(BVHNode *node,
			const objPtr_t *objPtrs,
			const Aabb *objAabbs,
			std::vector<objPtr_t> &activeObjIdxs);
	void MakeLeaf(BVHNode *node, const objPtr_t *objPtrs, std::vector<objPtr_t> &objs);
	BVHNode *AllocNode() {
		if (m_nodeAllocPos >= m_nodeAllocMax) Error("Out of space in m_bvhNodes.");
		return &m_bvhNodes[m_nodeAllocPos++];
	}
	BVHNode *m_root;
	objPtr_t *m_objPtrAlloc;
	size_t m_objPtrAllocPos;
	size_t m_objPtrAllocMax;

	BVHNode *m_bvhNodes;
	size_t m_nodeAllocPos;
	size_t m_nodeAllocMax;
};

#endif /* _BVHTREE_H */
