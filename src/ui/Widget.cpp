#include "Widget.h"
#include "Container.h"

namespace UI {

Widget::Widget(Context *context) :
	m_context(context),
	m_container(0),
	m_position(0),
	m_size(0),
	m_activeArea(0),
	m_transform(matrix4x4f::Identity()),
	m_fontSize(FONT_SIZE_NORMAL),
	m_floating(false),
	m_mouseOver(false),
	m_mouseActive(false)
{
	assert(m_context);
}

Widget::~Widget()
{
	// a container owns its widgets. this ensures that only the container can
	// delete the widget by requiring it to clear the widgets references
	// before deletion
	assert(!m_container);
}

vector2f Widget::GetAbsolutePosition() const
{
	if (IsFloating()) return m_position;
	if (!m_container) return 0;
	return m_container->GetAbsolutePosition() + m_position;
}

void Widget::Attach(Container *container)
{
	assert(m_context == container->GetContext());
	assert(container);
	m_container = container;
}

void Widget::Detach()
{
	m_container = 0;
	m_position = 0;
	m_size = 0;
}

void Widget::SetDimensions(const vector2f &position, const vector2f &size)
{
	m_position = position;
	SetSize(size);
	SetActiveArea(size);
}

void Widget::SetActiveArea(const vector2f &activeArea)
{
	m_activeArea = vector2f(Clamp(activeArea.x, 0.0f, GetSize().x), Clamp(activeArea.y, 0.0f, GetSize().y));
}

Widget *Widget::SetFontSize(FontSize fontSize)
{
    m_fontSize = fontSize;
	if (GetContainer()) GetContainer()->RequestResize();
    return this;
}

bool Widget::TriggerKeyDown(const KeyboardEvent &event, bool emit)
{
	HandleKeyDown(event);
	if (emit) emit = !onKeyDown.emit(event);
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerKeyDown(event, emit);
	return emit;
}

bool Widget::TriggerKeyUp(const KeyboardEvent &event, bool emit)
{
	HandleKeyUp(event);
	if (emit) emit = !onKeyUp.emit(event);
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerKeyUp(event, emit);
	return emit;
}

bool Widget::TriggerMouseDown(const MouseButtonEvent &event, bool emit)
{
	HandleMouseDown(event);
	if (emit) emit = !onMouseDown.emit(event);
	if (GetContainer() && !IsFloating()) {
		MouseButtonEvent translatedEvent = MouseButtonEvent(event.action, event.button, event.pos+GetPosition());
		GetContainer()->TriggerMouseDown(translatedEvent, emit);
	}
	return emit;
}

bool Widget::TriggerMouseUp(const MouseButtonEvent &event, bool emit)
{
	HandleMouseUp(event);
	if (emit) emit = !onMouseUp.emit(event);
	if (GetContainer() && !IsFloating()) {
		MouseButtonEvent translatedEvent = MouseButtonEvent(event.action, event.button, event.pos+GetPosition());
		GetContainer()->TriggerMouseUp(translatedEvent, emit);
	}
	return emit;
}

bool Widget::TriggerMouseMove(const MouseMotionEvent &event, bool emit)
{
	HandleMouseMove(event);
	if (emit) emit = !onMouseMove.emit(event);
	if (GetContainer() && !IsFloating()) {
		MouseMotionEvent translatedEvent = MouseMotionEvent(event.pos+GetPosition());
		GetContainer()->TriggerMouseMove(translatedEvent, emit);
	}
	return emit;
}

bool Widget::TriggerMouseWheel(const MouseWheelEvent &event, bool emit)
{
	HandleMouseWheel(event);
	if (emit) emit = !onMouseWheel.emit(event);
	if (GetContainer() && !IsFloating()) {
		MouseWheelEvent translatedEvent = MouseWheelEvent(event.direction, event.pos+GetPosition());
		GetContainer()->TriggerMouseWheel(translatedEvent, emit);
	}
	return emit;
}

bool Widget::TriggerMouseOver(const vector2f &pos, bool emit)
{
	// only send external events on state change
	if (!m_mouseOver && Contains(pos)) {
		m_mouseOver = true;
		HandleMouseOver();
		if (emit) emit = !onMouseOver.emit();
	}
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseOver(pos+GetPosition(), emit);
	return emit;
}

bool Widget::TriggerMouseOut(const vector2f &pos, bool emit)
{
	// only send external events on state change
	if (m_mouseOver && !Contains(pos)) {
		HandleMouseOut();
		if (emit) emit = !onMouseOut.emit();
		m_mouseOver = false;
	}
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseOut(pos+GetPosition(), emit);
	return emit;
}

bool Widget::TriggerClick(bool emit)
{
	HandleClick();
	if (emit) emit = !onClick.emit();
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerClick(emit);
	return emit;
}

void Widget::TriggerMouseActivate()
{
	m_mouseActive = true;
	HandleMouseActivate();
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseActivate();
}

void Widget::TriggerMouseDeactivate()
{
	m_mouseActive = false;
	HandleMouseDeactivate();
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseDeactivate();
}

}
