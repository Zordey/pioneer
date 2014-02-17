<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_COLORBACKGROUND_H
#define UI_COLORBACKGROUND_H

#include "Single.h"
#include "Color.h"
#include "graphics/Material.h"

namespace UI {

class ColorBackground : public Single {
public:
	virtual void Draw();

<<<<<<< HEAD
	void SetColor(const Color &color) { m_material->diffuse = color; }
=======
	void SetColor(const Color &color) { m_color = color; }
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

protected:
	friend class Context;
	ColorBackground(Context *context, const Color &color);

private:
<<<<<<< HEAD
	ScopedPtr<Graphics::Material> m_material;
=======
	Color m_color;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

}

#endif
