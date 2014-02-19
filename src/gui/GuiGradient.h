<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUIGRADIENT_H
#define _GUIGRADIENT_H

#include "GuiWidget.h"
#include "graphics/Texture.h"
#include <map>

namespace Graphics { class Renderer; }

namespace Gui {

	/*
	 * Draw a horizontal or vertical gradient.
	 * Can also generate a gradient texture.
	 */
	class Gradient : public Gui::Widget {
	public:
		enum Direction {
			HORIZONTAL,
			VERTICAL
		};

		Gradient(float width, float height, const Color &beginColor, const Color &endColor, Direction direction = VERTICAL);

		virtual void Draw();
		virtual void GetSizeRequested(float size[2]);

	private:
<<<<<<< HEAD
		ScopedPtr<TexturedQuad> m_quad;
=======
		std::unique_ptr<TexturedQuad> m_quad;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};

}

#endif
