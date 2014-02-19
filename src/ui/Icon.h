<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_ICON_H
#define UI_ICON_H

#include "Widget.h"
#include "IniConfig.h"
#include "SmartPtr.h"
#include "vector2.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"

namespace UI {

class Icon: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Draw();

	Icon *SetColor(const Color &c) { m_color = c; return this; }

protected:
	friend class Context;
	Icon(Context *context, const std::string &iconName);

private:
	static IniConfig                         s_config;

	static RefCountedPtr<Graphics::Texture>  s_texture;
	static vector2f                          s_texScale;

	static RefCountedPtr<Graphics::Material> s_material;

	Point m_texPos;
	Color m_color;
};

}

#endif
