<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef GAMEUI_MODELSPINNER_H
#define GAMEUI_MODELSPINNER_H

#include "ui/Context.h"
#include "graphics/Light.h"
#include "scenegraph/SceneGraph.h"
#include "scenegraph/ModelSkin.h"
#include "SmartPtr.h"
<<<<<<< HEAD
=======
#include "Shields.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace GameUI {

class ModelSpinner : public UI::Widget {
public:
<<<<<<< HEAD
	ModelSpinner(UI::Context *context, SceneGraph::Model *model, const SceneGraph::ModelSkin &skin);
=======
	ModelSpinner(UI::Context *context, SceneGraph::Model *model, const SceneGraph::ModelSkin &skin, unsigned int pattern);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	virtual UI::Point PreferredSize() { return UI::Point(INT_MAX); }
	virtual void Layout();
	virtual void Update();
	virtual void Draw();

	SceneGraph::Model *GetModel() const { return m_model.get(); }

protected:
	virtual void HandleMouseDown(const UI::MouseButtonEvent &event);
	virtual void HandleMouseMove(const UI::MouseMotionEvent &event);

private:
<<<<<<< HEAD
	ScopedPtr<SceneGraph::Model> m_model;
	SceneGraph::ModelSkin m_skin;
=======
	std::unique_ptr<SceneGraph::Model> m_model;
	SceneGraph::ModelSkin m_skin;
	std::unique_ptr<Shields> m_shields;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	float m_rotX, m_rotY;

	Graphics::Light m_light;

	bool m_rightMouseButton;
};

}

#endif
