#include "Container.h"
#include "Context.h"
#include "matrix4x4.h"
#include "graphics/Renderer.h"

namespace UI {

Container::~Container()
{
	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i) {
		(*i)->Detach();
		delete (*i);
	}
}

void Container::Update()
{
	if (m_needsLayout) {
		Layout();
		m_needsLayout = false;
	}

	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i)
		(*i)->Update();
}

void Container::Draw()
{
	Context *c = GetContext();
	Graphics::Renderer *r = c->GetRenderer();

	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i) {
		const vector2f &pos = (*i)->GetAbsolutePosition();
		c->SetScissor(true, pos, (*i)->GetSize());
		r->SetTransform(matrix4x4f::Translation(pos.x,pos.y,0) * (*i)->GetTransform());
		(*i)->Draw();
	}

	c->SetScissor(false);
}

void Container::RequestResize()
{
	m_needsLayout = true;
}

void Container::LayoutChildren()
{
	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i)
		(*i)->Layout();
}

void Container::AddWidget(Widget *widget)
{
	assert(!widget->GetContainer());

	std::list<Widget*>::iterator i;
	for (i = m_widgets.begin(); i != m_widgets.end(); ++i)
		if (*i == widget) break;
	assert(i == m_widgets.end());

	widget->Attach(this);
	m_widgets.push_back(widget);
}

void Container::RemoveWidget(Widget *widget)
{
	assert(widget->GetContainer() == this);

	std::list<Widget*>::iterator i;
	for (i = m_widgets.begin(); i != m_widgets.end(); ++i)
		if (*i == widget) break;
	assert(i != m_widgets.end());

	widget->Detach();
	m_widgets.erase(i);
}

void Container::SetWidgetDimensions(Widget *widget, const vector2f &position, const vector2f &size)
{
	assert(widget->GetContainer() == this);

	widget->SetDimensions(position, size);
}

Widget *Container::GetWidgetAtAbsolute(const vector2f &pos)
{
	if (!ContainsAbsolute(pos)) return 0;

	for (WidgetIterator i = WidgetsBegin(); i != WidgetsEnd(); ++i) {
		Widget *widget = *i;
		if (widget->ContainsAbsolute(pos)) {
			if (widget->IsContainer())
				return static_cast<Container*>(widget)->GetWidgetAtAbsolute(pos);
			else
				return widget;
		}
	}
	
	return this;
}

}
