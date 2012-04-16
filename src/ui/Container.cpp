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
	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i)
		(*i)->Update();
}

void Container::Draw()
{
	// XXX set scissor region

	Graphics::Renderer *r = GetContext()->GetRenderer();

	for (std::list<Widget*>::iterator i = m_widgets.begin(); i != m_widgets.end(); ++i) {
		const vector2f &pos = (*i)->GetAbsolutePosition();
		r->SetTransform(matrix4x4f::Translation(pos.x,pos.y,0));
		(*i)->Draw();
	}
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

Widget *Container::GetWidgetAt(const vector2f &pos)
{
	if (!Contains(pos)) return 0;

	for (WidgetIterator i = WidgetsBegin(); i != WidgetsEnd(); ++i) {
		Widget *widget = *i;
		if (widget->Contains(pos)) {
			if (widget->IsContainer())
				return static_cast<Container*>(widget)->GetWidgetAt(pos);
			else
				return widget;
		}
	}
	
	return this;
}

}
