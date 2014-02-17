<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef SCENEGRAPH_NODECOPYCACHE_H
#define SCENEGRAPH_NODECOPYCACHE_H

#include "RefCounted.h"
#include <map>

namespace SceneGraph {

class Node;

class NodeCopyCache {
public:
	template <typename T> T *Copy(const T *origNode) {
		const bool doCache = origNode->GetRefCount() > 1;
		if (doCache) {
			std::map<const Node*,Node*>::const_iterator i = m_cache.find(origNode);
			if (i != m_cache.end())
				return static_cast<T*>((*i).second);
		}
		T *newNode = new T(*origNode, this);
		if (doCache)
			m_cache.insert(std::make_pair(origNode, newNode));
		return newNode;
	}

private:
	std::map<const Node*,Node*> m_cache;
};

}

#endif
