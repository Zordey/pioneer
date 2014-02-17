<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _INTRO_H
#define _INTRO_H

#include "Cutscene.h"
#include "Background.h"
#include "ShipType.h"
<<<<<<< HEAD
=======
#include "scenegraph/ModelSkin.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

class Intro : public Cutscene {
public:
	Intro(Graphics::Renderer *r, int width, int height);
	~Intro();
	virtual void Draw(float time);

private:
<<<<<<< HEAD
	std::vector<SceneGraph::Model*> m_models;

	enum State {
		STATE_SELECT,
		STATE_ZOOM_IN,
		STATE_WAIT,
		STATE_ZOOM_OUT
	};
	State m_state;
=======
	void Reset(float time);
	bool m_needReset;

	std::vector<SceneGraph::Model*> m_models;
	SceneGraph::ModelSkin m_skin;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float m_startTime;

	unsigned int m_modelIndex;
	float m_zoomBegin, m_zoomEnd;
	float m_dist;

<<<<<<< HEAD
	ScopedPtr<Background::Container> m_background;
=======
	std::unique_ptr<Background::Container> m_background;

	int m_spinnerLeft;
	int m_spinnerWidth;
	float m_spinnerRatio;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

#endif
