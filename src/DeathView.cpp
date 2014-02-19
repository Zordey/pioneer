<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "DeathView.h"
#include "Pi.h"
#include "Player.h"
#include "ShipCpanel.h"
#include "graphics/Graphics.h"

DeathView::DeathView(): View()
{
	float size[2];
	GetSizeRequested(size);

	SetTransparency(true);

	float znear;
	float zfar;
	Pi::renderer->GetNearFarRange(znear, zfar);

	const float fovY = Pi::config->Float("FOVVertical");
<<<<<<< HEAD
	m_cam.Reset(new Camera(Graphics::GetScreenWidth(), Graphics::GetScreenHeight(), fovY, znear, zfar));
=======
	m_cam.reset(new Camera(Graphics::GetScreenWidth(), Graphics::GetScreenHeight(), fovY, znear, zfar));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

DeathView::~DeathView() {}

void DeathView::Init()
{
	m_cameraDist = Pi::player->GetClipRadius() * 5.0;
	m_cameraContext->SetFrame(Pi::player->GetFrame());
	m_cameraContext->SetPosition(Pi::player->GetInterpPosition() + vector3d(0, 0, m_cameraDist));
	m_cameraContext->SetOrient(matrix3x3d::Identity());
}

void DeathView::OnSwitchTo()
{
	Pi::cpan->HideAll();
}

void DeathView::Update()
{
	assert(Pi::player->IsDead());

	m_cameraDist += 160.0 * Pi::GetFrameTime();
	m_cameraContext->SetPosition(Pi::player->GetInterpPosition() + vector3d(0, 0, m_cameraDist));
	m_cameraContext->BeginFrame();
	m_camera->Update();
}

void DeathView::Draw3D()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_cam->Draw(m_renderer);
}
