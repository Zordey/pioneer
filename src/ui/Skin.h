#ifndef _UI_SKIN_H
#define _UI_SKIN_H

#include "libs.h"
#include "SmartPtr.h"
#include "graphics/Renderer.h"
#include "graphics/Material.h"

namespace UI {

class Skin {
public:
	Skin(const std::string &filename, Graphics::Renderer *renderer);

	void DrawButtonNormal(const vector2f &pos, const vector2f &size) const {
		DrawBorderedRectElement(s_buttonNormal, pos, size);
	}
	void DrawButtonActive(const vector2f &pos, const vector2f &size) const {
		DrawBorderedRectElement(s_buttonActive, pos, size);
	}

private:
	Graphics::Renderer *m_renderer;
	RefCountedPtr<Graphics::Texture> m_texture;
	RefCountedPtr<Graphics::Material> m_material;

	struct RectElement {
		RectElement(float x, float y, float w, float h);
		const vector2f pos;
		const vector2f size;
	};

	struct BorderedRectElement : public RectElement {
		BorderedRectElement(float x, float y, float w, float h, float _borderWidth) : RectElement(x, y, w, h), borderWidth(_borderWidth) {}
		const float borderWidth;
	};

	void DrawBorderedRectElement(const BorderedRectElement &element, const vector2f &pos, const vector2f &size) const;

	static BorderedRectElement s_buttonNormal;
	static BorderedRectElement s_buttonActive;
};

}

#endif
