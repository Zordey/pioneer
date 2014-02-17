<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Intro.h"
#include "Pi.h"
#include "Lang.h"
#include "Easing.h"
#include "graphics/Renderer.h"
#include "graphics/TextureBuilder.h"
#include "graphics/Graphics.h"
#include "scenegraph/SceneGraph.h"
#include "scenegraph/ModelSkin.h"
#include <algorithm>

struct PiRngWrapper {
	unsigned int operator()(unsigned int n) {
		return Pi::rng.Int32(n);
	}
};

Intro::Intro(Graphics::Renderer *r, int width, int height)
: Cutscene(r, width, height)
{
	using Graphics::Light;

<<<<<<< HEAD
	m_background.Reset(new Background::Container(r, UNIVERSE_SEED));
	m_ambientColor = Color(0.f);

	const Color one = Color::WHITE;
	const Color two = Color(0.3f, 0.3f, 0.8f, 0.f);
	m_lights.push_back(Light(Graphics::Light::LIGHT_DIRECTIONAL, vector3f(0.f, 0.3f, 1.f), one, one));
	m_lights.push_back(Light(Graphics::Light::LIGHT_DIRECTIONAL, vector3f(0.f, -1.f, 0.f), two, Color::BLACK));

	SceneGraph::ModelSkin skin;
	skin.SetDecal("01_Badge");
	skin.SetLabel(Lang::PIONEER);

	for (std::vector<ShipType::Id>::const_iterator i = ShipType::player_ships.begin(); i != ShipType::player_ships.end(); ++i) {
		SceneGraph::Model *model = Pi::FindModel(ShipType::types[*i].modelName)->MakeInstance();
		skin.SetRandomColors(Pi::rng);
		skin.Apply(model);
		model->SetThrust(vector3f(0.f, 0.f, -0.6f), vector3f(0.f));
=======
	m_background.reset(new Background::Container(r, UNIVERSE_SEED));
	m_ambientColor = Color(0);

	const Color one = Color::WHITE;
	const Color two = Color(77, 77, 204, 0);
	m_lights.push_back(Light(Graphics::Light::LIGHT_DIRECTIONAL, vector3f(0.f, 0.3f, 1.f), one, one));
	m_lights.push_back(Light(Graphics::Light::LIGHT_DIRECTIONAL, vector3f(0.f, -1.f, 0.f), two, Color::BLACK));

	m_skin.SetDecal("pioneer");
	m_skin.SetLabel(Lang::PIONEER);

	for (std::vector<ShipType::Id>::const_iterator i = ShipType::player_ships.begin(); i != ShipType::player_ships.end(); ++i) {
		SceneGraph::Model *model = Pi::FindModel(ShipType::types[*i].modelName)->MakeInstance();
		model->SetThrust(vector3f(0.f, 0.f, -0.6f), vector3f(0.f));
		const Uint32 numMats = model->GetNumMaterials();
		for( Uint32 m=0; m<numMats; m++ ) {
			RefCountedPtr<Graphics::Material> mat = model->GetMaterialByIndex(m);
			mat->specialParameter0 = nullptr;
		}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		m_models.push_back(model);
	}

	PiRngWrapper rng;
	std::random_shuffle(m_models.begin(), m_models.end(), rng);

<<<<<<< HEAD
	m_state = STATE_SELECT;
	m_modelIndex = 0;
=======
	m_modelIndex = 0;

	const int w = Graphics::GetScreenWidth();
	const int h = Graphics::GetScreenHeight();

	// double-width viewport, centred, then offset 1/6th to centre on the left
	// 2/3rds of the screen, to the left of the menu
	m_spinnerLeft = int(float(w)*-.5f - float(w)/6.f);
	m_spinnerWidth = w*2;
	m_spinnerRatio = w*2.f/h;

	m_needReset = true;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Intro::~Intro()
{
	for (std::vector<SceneGraph::Model*>::iterator i = m_models.begin(); i != m_models.end(); ++i)
		delete (*i);
}

<<<<<<< HEAD
void Intro::Draw(float _time)
{
	switch (m_state) {
		case STATE_SELECT:
			m_model = m_models[m_modelIndex++];
			if (m_modelIndex == m_models.size()) m_modelIndex = 0;
			m_zoomBegin = -10000.0f;
			m_zoomEnd = -m_model->GetDrawClipRadius()*1.7f;
			m_dist = m_zoomBegin;
			m_state = STATE_ZOOM_IN;
			m_startTime = _time;
			break;

		case STATE_ZOOM_IN:
			m_dist = Clamp(Easing::Quad::EaseOut(_time-m_startTime, m_zoomBegin, m_zoomEnd-m_zoomBegin, 2.0f), m_zoomBegin, m_zoomEnd);
			if (_time-m_startTime > 2.0f) {
				m_state = STATE_WAIT;
				m_startTime = _time;
			}
			break;

		case STATE_WAIT:
			if (_time - m_startTime > 10.0f) {
				m_state = STATE_ZOOM_OUT;
				m_startTime = _time;
			}
			break;

		case STATE_ZOOM_OUT:
			m_dist = Clamp(Easing::Quad::EaseIn(_time-m_startTime, m_zoomEnd, m_zoomBegin-m_zoomEnd, 2.0f), m_zoomBegin, m_zoomEnd);
			if (_time-m_startTime > 2.0f) {
				m_state = STATE_SELECT;
				m_startTime = _time;
			}
			break;
	}

	m_renderer->SetPerspectiveProjection(75, m_aspectRatio, 1.f, 10000.f);
	m_renderer->SetTransform(matrix4x4f::Identity());

	glPushAttrib(GL_ALL_ATTRIB_BITS & (~GL_POINT_BIT));

	const Color oldSceneAmbientColor = m_renderer->GetAmbientColor();
=======
void Intro::Reset(float _time)
{
	m_model = m_models[m_modelIndex++];
	if (m_modelIndex == m_models.size()) m_modelIndex = 0;
	m_skin.SetRandomColors(Pi::rng);
	m_skin.Apply(m_model);
	m_model->SetPattern(Pi::rng.Int32(0, m_model->GetNumPatterns()));
	m_zoomBegin = -10000.0f;
	m_zoomEnd = -m_model->GetDrawClipRadius()*1.7f;
	m_dist = m_zoomBegin;
	m_startTime = _time;
	m_needReset = false;
}

// stage end times
static const float ZOOM_IN_END  = 2.0f;
static const float WAIT_END     = 12.0f;
static const float ZOOM_OUT_END = 14.0f;

void Intro::Draw(float _time)
{
	if (m_needReset)
		Reset(_time);

	float duration = _time-m_startTime;

	// zoom in
	if (duration < ZOOM_IN_END)
		m_dist = Clamp(Easing::Quad::EaseOut(duration, m_zoomBegin, m_zoomEnd-m_zoomBegin, 2.0f), m_zoomBegin, m_zoomEnd);

	// wait
	else if (duration < WAIT_END) {
		m_dist = m_zoomEnd;
	}

	// zoom out
	else if (duration < ZOOM_OUT_END)
		m_dist = Clamp(Easing::Quad::EaseIn(duration-WAIT_END, m_zoomEnd, m_zoomBegin-m_zoomEnd, 2.0f), m_zoomBegin, m_zoomEnd);

	// done
	else
		m_needReset = true;

	Graphics::Renderer::StateTicket ticket(m_renderer);

	m_renderer->SetPerspectiveProjection(75, m_aspectRatio, 1.f, 10000.f);
	m_renderer->SetTransform(matrix4x4f::Identity());

	m_renderer->SetDepthTest(true);
	m_renderer->SetDepthWrite(true);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_renderer->SetAmbientColor(m_ambientColor);
	m_renderer->SetLights(m_lights.size(), &m_lights[0]);

	// XXX all this stuff will be gone when intro uses a Camera
	// rotate background by time, and a bit extra Z so it's not so flat
	matrix4x4d brot = matrix4x4d::RotateXMatrix(-0.25*_time) * matrix4x4d::RotateZMatrix(0.6);
	m_background->Draw(m_renderer, brot);

<<<<<<< HEAD
	const float w = Graphics::GetScreenWidth()*(2.0/3.0);
	const float h = Graphics::GetScreenHeight();
	const float ratio = w/h;
	m_renderer->SetViewport(0, 0, w, h);
	m_renderer->SetPerspectiveProjection(75, ratio, 1.f, 10000.f);

	matrix4x4f trans =
		matrix4x4f::Translation(0, 0, m_dist) *
		matrix4x4f::RotateYMatrix(_time) *
		matrix4x4f::RotateZMatrix(0.6f*_time) *
		matrix4x4f::RotateXMatrix(_time*0.7f);
	m_model->Render(trans);

	m_renderer->SetAmbientColor(oldSceneAmbientColor);

	m_renderer->SetViewport(0, 0, Graphics::GetScreenWidth(), Graphics::GetScreenHeight());

	glPopAttrib();
=======
	m_renderer->SetViewport(m_spinnerLeft, 0, m_spinnerWidth, Graphics::GetScreenHeight());
	m_renderer->SetPerspectiveProjection(75, m_spinnerRatio, 1.f, 10000.f);

	matrix4x4f trans =
		matrix4x4f::Translation(0, 0, m_dist) *
		matrix4x4f::RotateXMatrix(DEG2RAD(-15.0f)) *
		matrix4x4f::RotateYMatrix(_time);
	m_model->Render(trans);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}
