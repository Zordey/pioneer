#ifndef _GUIIMAGE_H
#define _GUIIMAGE_H

#include "GuiWidget.h"
#include "graphics/Drawables.h"
#include "Color.h"

namespace Gui {
	class Texture;

	class Image: public Widget {
	public:
		Image(const char *filename);
		virtual void Draw();
		virtual void GetSizeRequested(float size[2]);
		void SetModulateColor(const Color &color) { m_color = color; }
	private:
		ScopedPtr<Graphics::Drawables::TexturedUIQuad> m_quad;
		Color m_color;
		float m_width, m_height;
	};
}

#endif /* _GUIIMAGE_H */
