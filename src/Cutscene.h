<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _CUTSCENE_H
#define _CUTSCENE_H

#include "libs.h"
#include "graphics/Renderer.h"
#include "graphics/Light.h"

namespace SceneGraph { class Model; }
<<<<<<< HEAD
=======
class Shields;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

class Cutscene {
public:
	Cutscene(Graphics::Renderer *r, int width, int height)
	: m_aspectRatio(float(width)/float(height))
	, m_renderer(r)
	{
	}
	virtual ~Cutscene() {}

	virtual void Draw(float time) = 0;

protected:
	Color m_ambientColor;
	float m_aspectRatio;
	Graphics::Renderer *m_renderer;
	SceneGraph::Model *m_model;
<<<<<<< HEAD
=======
	Shields *m_shield;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	std::vector<Graphics::Light> m_lights;
};

#endif
