<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

// DEPRECATED due to new ui system

#ifndef _SHIPSPINNERWIDGET_H
#define _SHIPSPINNERWIDGET_H

#include "gui/Gui.h"
#include "graphics/Light.h"
#include "scenegraph/SceneGraph.h"
#include "scenegraph/ModelSkin.h"
#include "SmartPtr.h"
<<<<<<< HEAD
=======
#include "Shields.h"

class Shields;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

class ShipSpinnerWidget : public Gui::Widget {
public:
	ShipSpinnerWidget(SceneGraph::Model *model, const SceneGraph::ModelSkin &skin, float width, float height);

	virtual void Draw();
	virtual void GetSizeRequested(float size[2]) { size[0] = m_width; size[1] = m_height; }

private:
	float m_width;
	float m_height;

<<<<<<< HEAD
	ScopedPtr<SceneGraph::Model> m_model;
	SceneGraph::ModelSkin m_skin;

	Graphics::Light m_light;
=======
	std::unique_ptr<SceneGraph::Model> m_model;
	SceneGraph::ModelSkin m_skin;

	Graphics::Light m_light;
	std::unique_ptr<Shields> m_shields;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif
