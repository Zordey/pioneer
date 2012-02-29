#ifndef _DRAWABLES_H
#define _DRAWABLES_H

#include "libs.h"
#include "graphics/VertexArray.h"
#include "graphics/Renderer.h"
#include "graphics/Texture.h"
#include "Color.h"

namespace Graphics {

namespace Drawables {

// A thing that can draw itself using renderer
// (circles, disks, polylines etc)
class Drawable {
protected:
	virtual void Draw(Renderer *r) = 0;
};

class Circle {
public:
	Circle(float radius, const Color &c) : m_color(c) {
		for (float theta=0; theta < 2*M_PI; theta += 0.05*M_PI) {
			m_verts.push_back(vector3f(radius*sin(theta), radius*cos(theta), 0));
		}
	}
	virtual void Draw(Renderer *renderer) {
		renderer->DrawLines(m_verts.size(), &m_verts[0], m_color, LINE_LOOP);
	}

private:
	std::vector<vector3f> m_verts;
	Color m_color;
};

//A three dimensional line between two points
class Line3D : public Drawable {
public:
	Line3D();
	void SetStart(const vector3f &);
	void SetEnd(const vector3f &);
	void SetColor(const Color &);
	virtual void Draw(Renderer *r);
private:
	vector3f m_points[2];
	Color m_colors[2];
	float m_width;
};

// a textured quad with reversed winding for the UI
// XXX move this to Gui::Drawables
class TexturedUIQuad : public Drawable {
public:
	TexturedUIQuad(Texture *texture) : m_texture(RefCountedPtr<Texture>(texture)) {}
	virtual void Draw(Renderer *r);
	void Draw(Renderer *r, const vector2f &pos, const vector2f &size, const vector2f &texPos = 0.0f, const vector2f &texSize = 1.0f, const Color &tint = Color::WHITE);
private:
	void Draw(Renderer *r, VertexArray *va, const Color &tint);
	RefCountedPtr<Texture> m_texture;
};

}

}

#endif
