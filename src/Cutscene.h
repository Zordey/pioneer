// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _CUTSCENE_H
#define _CUTSCENE_H

#include "libs.h"
#include "graphics/Renderer.h"
#include "graphics/Light.h"

class ModelBase;

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
	ModelBase *m_model;
	ModelParams m_modelParams;
	std::vector<Graphics::Light> m_lights;
};

#endif
