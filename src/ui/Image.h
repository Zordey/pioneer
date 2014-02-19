<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_IMAGE_H
#define UI_IMAGE_H

#include "Widget.h"
#include "SmartPtr.h"
#include "graphics/Material.h"
#include "graphics/Texture.h"

namespace UI {

class Image: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Draw();

	Image *SetHeightLines(Uint32 lines);

protected:
	friend class Context;
	Image(Context *context, const std::string &filename, Uint32 sizeControlFlags);

private:
	RefCountedPtr<Graphics::Texture> m_texture;
	RefCountedPtr<Graphics::Material> m_material;
	Point m_initialSize;
};

}

#endif
