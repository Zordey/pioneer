#include "Context.h"
#include "FileSystem.h"
#include "text/FontDescriptor.h"

namespace UI {

Context::Context(Graphics::Renderer *renderer, int width, int height) : Single(this),
	m_renderer(renderer),
	m_width(float(width)),
	m_height(float(height)),
	m_eventDispatcher(this),
	m_skin("textures/widgets.png", renderer),
	m_font(RefCountedPtr<Text::TextureFont>(new Text::TextureFont(Text::FontDescriptor("TitilliumText22L004.otf", 14, 14, false, -1.0f), renderer)))
{
	SetSize(vector2f(m_width,m_height));
}

Context *Context::AddFloatingWidget(Widget *w, const vector2f &pos, const vector2f &size)
{
	assert(!w->IsFloating());
	assert(!w->GetContainer());

	m_floatWidgets.push_back(w);
	w->SetFloating(true);

	w->SetDimensions(pos, size);

	return this;
}

Context *Context::RemoveFloatingWidget(Widget *w)
{
	assert(w->IsFloating());
	assert(!w->GetContainer());

	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i)
		if ((*i) == w) {
			m_floatWidgets.erase(i);
			w->SetFloating(false);
			break;
		}
	
	return this;
}

// XXX this is pretty much a copy of Container::GetWidgetAtAbsolute. if
// Context could just use a FloatContainer that derives from Container we
// could probably avoid a lot of this sort of thing
Widget *Context::GetWidgetAtAbsolute(const vector2f &pos) {
	if (!ContainsAbsolute(pos)) return 0;

	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i) {
		Widget *widget = *i;
		if (widget->ContainsAbsolute(pos)) {
			if (widget->IsContainer())
				return static_cast<Container*>(widget)->GetWidgetAtAbsolute(pos);
			else
				return widget;
		}
	}

	return Single::GetWidgetAtAbsolute(pos);
}

void Context::Layout()
{
	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i)
		(*i)->Layout();

	Single::Layout();
}

void Context::Update()
{
	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i)
		(*i)->Update();

	Single::Update();
}

void Context::Draw()
{
	Single::Draw();

	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i) {
		const vector2f &pos = (*i)->GetAbsolutePosition();
		SetScissor(true, pos, (*i)->GetSize());
		m_renderer->SetTransform(matrix4x4f::Translation(pos.x,pos.y,0));
		(*i)->Draw();
	}

	SetScissor(false);
	for (std::vector<Widget*>::iterator i = m_floatWidgets.begin(); i != m_floatWidgets.end(); ++i)
	{
	}
}

void Context::SetScissor(bool enabled, const vector2f &pos, const vector2f &size)
{
	if (enabled) {
		vector2f flippedPos(pos.x, m_height-pos.y-size.y);
		m_renderer->SetScissor(true, flippedPos, size);
	}
	else
		m_renderer->SetScissor(false);

}

}
