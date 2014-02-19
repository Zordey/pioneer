<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ModelCache.h"
#include "scenegraph/SceneGraph.h"
<<<<<<< HEAD
=======
#include "Shields.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

ModelCache::ModelCache(Graphics::Renderer *r)
: m_renderer(r)
{

}

ModelCache::~ModelCache()
{
	Flush();
}

SceneGraph::Model *ModelCache::FindModel(const std::string &name)
{
	ModelMap::iterator it = m_models.find(name);

	if (it == m_models.end()) {
		try {
			SceneGraph::Loader loader(m_renderer);
			SceneGraph::Model *m = loader.LoadModel(name);
<<<<<<< HEAD
=======
			Shields::ReparentShieldNodes(m);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			m_models[name] = m;
			return m;
		} catch (SceneGraph::LoadingError &) {
			throw ModelNotFoundException();
		}
	}
	return it->second;
}

void ModelCache::Flush()
{
	for(ModelMap::iterator it = m_models.begin(); it != m_models.end(); ++it) {
		delete it->second;
	}
	m_models.clear();
}
