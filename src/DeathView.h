<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef DEATH_VIEW_H
#define DEATH_VIEW_H

#include "libs.h"
#include "View.h"
#include "Camera.h"

class DeathView : public View {
public:
	DeathView();
	virtual ~DeathView();

	void Init();

	virtual void Update();
	virtual void Draw3D();

protected:
	virtual void OnSwitchTo();

private:
<<<<<<< HEAD
	ScopedPtr<Camera> m_cam;
=======
	std::unique_ptr<Camera> m_cam;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float m_cameraDist;
};

#endif
