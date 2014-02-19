<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Widget.h"
#include "Container.h"
#include "Context.h"

namespace UI {

Widget::Widget(Context *context) :
	m_context(context),
	m_container(0),
	m_position(0),
	m_size(0),
	m_sizeControlFlags(0),
	m_drawOffset(0),
	m_activeOffset(0),
	m_activeArea(0),
	m_font(FONT_INHERIT),
<<<<<<< HEAD
	m_floating(false),
	m_disabled(false),
	m_mouseOver(false),
	m_mouseActive(false)
=======
	m_disabled(false),
	m_mouseOver(false),
	m_visible(false)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	assert(m_context);
}

Widget::~Widget()
{
	// a container owns its widgets. this ensures that only the container can
	// delete the widget by requiring it to clear the widgets references
	// before deletion
	assert(!m_container);

	for (std::map<std::string,sigc::connection>::iterator i = m_binds.begin(); i != m_binds.end(); ++i)
		(*i).second.disconnect();
}

Point Widget::GetAbsolutePosition() const
{
<<<<<<< HEAD
	if (IsFloating()) return m_position + m_drawOffset;
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if (!m_container) return Point() + m_drawOffset;
	return m_container->GetAbsolutePosition() + m_position + m_drawOffset;
}

<<<<<<< HEAD
void Widget::Attach(Container *container)
{
	assert(m_context == container->GetContext());
	assert(container);
	m_container = container;
=======
Point Widget::GetMousePos() const
{
	return m_context->GetMousePos() - GetAbsolutePosition();
}

void Widget::Attach(Container *container)
{
	assert(container);
	assert(m_context == container->GetContext());
	m_container = container;

	// we should never be visible while we're detached, and we should
	// always be detached before being attached to something else
	assert(!m_visible);
	NotifyVisible(container->IsVisible());
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Widget::Detach()
{
<<<<<<< HEAD
	m_container = 0;
	m_position = Point();
	m_size = Point();
	m_floating = false;
=======
	NotifyVisible(false);
	m_container = 0;
	m_position = Point();
	m_size = Point();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Widget::SetDimensions(const Point &position, const Point &size)
{
	m_position = position;
	SetSize(size);
	SetActiveArea(size);
}

<<<<<<< HEAD
=======
void Widget::NotifyVisible(bool visible)
{
	if (m_visible != visible) {
		m_visible = visible;
		if (m_visible) { HandleVisible(); } else { HandleInvisible(); }
	}
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
void Widget::SetActiveArea(const Point &activeArea, const Point &activeOffset)
{
	m_activeArea = Point(Clamp(activeArea.x, 0, GetSize().x), Clamp(activeArea.y, 0, GetSize().y));
	m_activeOffset = activeOffset;
}

Widget *Widget::SetFont(Font font)
{
	m_font = font;
	GetContext()->RequestLayout();
	return this;
}

Point Widget::CalcLayoutContribution()
{
	Point preferredSize = PreferredSize();
	const Uint32 flags = GetSizeControlFlags();

	if (flags & NO_WIDTH)
		preferredSize.x = 0;
	if (flags & NO_HEIGHT)
		preferredSize.y = 0;

	if (flags & EXPAND_WIDTH)
		preferredSize.x = SIZE_EXPAND;
	if (flags & EXPAND_HEIGHT)
		preferredSize.y = SIZE_EXPAND;

	return preferredSize;
}

Point Widget::CalcSize(const Point &avail)
{
	if (!(GetSizeControlFlags() & PRESERVE_ASPECT))
		return avail;

	const Point preferredSize = PreferredSize();

	float wantRatio = float(preferredSize.x) / float(preferredSize.y);

	// more room on X than Y, use full X, scale Y
	if (avail.x > avail.y)
		return Point(float(avail.y) * wantRatio, avail.y);

	// more room on Y than X, use full Y, scale X
	else
		return Point(avail.x, float(avail.x) / wantRatio);
}

Widget::Font Widget::GetFont() const
{
	if (m_font == FONT_INHERIT) {
		if (m_container) return m_container->GetFont();
		return FONT_NORMAL;
	}
	return m_font;
}

<<<<<<< HEAD
=======
bool Widget::IsMouseActive() const
{
	return (GetContext()->GetMouseActive() == this);
}

bool Widget::IsSelected() const
{
	return (GetContext()->GetSelected() == this);
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
void Widget::Disable()
{
	SetDisabled(true);
	GetContext()->DisableWidget(this);
}

void Widget::Enable()
{
	SetDisabled(false);
	GetContext()->EnableWidget(this);
}

bool Widget::TriggerKeyDown(const KeyboardEvent &event, bool handled)
{
	HandleKeyDown(event);
	if (emit) emit = !onKeyDown.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerKeyDown(event, emit);
=======
	if (GetContainer()) GetContainer()->TriggerKeyDown(event, emit);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return !emit;
}

bool Widget::TriggerKeyUp(const KeyboardEvent &event, bool handled)
{
	HandleKeyUp(event);
	if (emit) emit = !onKeyUp.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerKeyUp(event, emit);
	return !emit;
}

bool Widget::TriggerKeyPress(const KeyboardEvent &event, bool emit)
{
	HandleKeyPress(event);
	if (emit) emit = !onKeyPress.emit(event);
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerKeyPress(event, emit);
=======
	if (GetContainer()) GetContainer()->TriggerKeyUp(event, emit);
	return !emit;
}

bool Widget::TriggerTextInput(const TextInputEvent &event, bool handled)
{
	HandleTextInput(event);
	if (emit) emit = !onTextInput.emit(event);
	if (GetContainer()) GetContainer()->TriggerTextInput(event, emit);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return !emit;
}

bool Widget::TriggerMouseDown(const MouseButtonEvent &event, bool handled)
{
	HandleMouseDown(event);
	if (emit) emit = !onMouseDown.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) {
=======
	if (GetContainer()) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		MouseButtonEvent translatedEvent = MouseButtonEvent(event.action, event.button, event.pos+GetPosition());
		handled = GetContainer()->TriggerMouseDown(translatedEvent, handled);
	}
	return handled;
}

bool Widget::TriggerMouseUp(const MouseButtonEvent &event, bool handled)
{
	HandleMouseUp(event);
	if (emit) emit = !onMouseUp.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) {
=======
	if (GetContainer()) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		MouseButtonEvent translatedEvent = MouseButtonEvent(event.action, event.button, event.pos+GetPosition());
		handled = GetContainer()->TriggerMouseUp(translatedEvent, handled);
	}
	return handled;
}

bool Widget::TriggerMouseMove(const MouseMotionEvent &event, bool handled)
{
	HandleMouseMove(event);
	if (emit) emit = !onMouseMove.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) {
=======
	if (GetContainer()) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		MouseMotionEvent translatedEvent = MouseMotionEvent(event.pos+GetPosition(), event.rel);
		handled = GetContainer()->TriggerMouseMove(translatedEvent, handled);
	}
	return handled;
}

bool Widget::TriggerMouseWheel(const MouseWheelEvent &event, bool handled)
{
	HandleMouseWheel(event);
	if (emit) emit = !onMouseWheel.emit(event);
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) {
=======
	if (GetContainer()) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		MouseWheelEvent translatedEvent = MouseWheelEvent(event.direction, event.pos+GetPosition());
		handled = GetContainer()->TriggerMouseWheel(translatedEvent, handled);
	}
	return handled;
}

<<<<<<< HEAD
bool Widget::TriggerMouseOver(const Point &pos, bool emit, Widget *stop)
{
	// only send external events on state change
	if (!m_mouseOver && Contains(pos)) {
=======
bool Widget::TriggerJoystickButtonDown(const JoystickButtonEvent &event, bool emit)
{
	HandleJoystickButtonDown(event);
	if (!handled) handled = onJoystickButtonDown.emit(event);
	if (GetContainer()) handled = GetContainer()->TriggerJoystickButtonDown(event, handled);
	return handled;
}

bool Widget::TriggerJoystickButtonUp(const JoystickButtonEvent &event, bool handled)
{
	HandleJoystickButtonUp(event);
	if (!handled) handled = onJoystickButtonUp.emit(event);
	if (GetContainer()) handled = GetContainer()->TriggerJoystickButtonUp(event, handled);
	return handled;
}

bool Widget::TriggerJoystickAxisMove(const JoystickAxisMotionEvent &event, bool handled)
{
	HandleJoystickAxisMove(event);
	if (!handled) handled = onJoystickAxisMove.emit(event);
	if (GetContainer()) handled = GetContainer()->TriggerJoystickAxisMove(event, handled);
	return handled;
}

bool Widget::TriggerJoystickHatMove(const JoystickHatMotionEvent &event, bool handled)
{
	HandleJoystickHatMove(event);
	if (!handled) handled = onJoystickHatMove.emit(event);
	if (GetContainer()) handled = GetContainer()->TriggerJoystickHatMove(event, handled);
	return handled;
}

bool Widget::TriggerMouseOver(const Point &pos, bool handled, Widget *stop)
{
	// only send external events on state change
	if (!m_mouseOver) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		m_mouseOver = true;
		HandleMouseOver();
		if (!handled) handled = onMouseOver.emit();
	}
	if (stop == this) return !emit;
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseOver(pos+GetPosition(), emit, stop);
=======
	if (GetContainer()) GetContainer()->TriggerMouseOver(pos+GetPosition(), emit, stop);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return !emit;
}

bool Widget::TriggerMouseOut(const Point &pos, bool handled, Widget *stop)
{
	// only send external events on state change
<<<<<<< HEAD
	if (m_mouseOver && !Contains(pos)) {
=======
	if (m_mouseOver) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		HandleMouseOut();
		if (!handled) handled = onMouseOut.emit();
		m_mouseOver = false;
	}
	if (stop == this) return !emit;
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseOut(pos+GetPosition(), emit, stop);
=======
	if (GetContainer()) GetContainer()->TriggerMouseOut(pos+GetPosition(), emit, stop);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return !emit;
}

bool Widget::TriggerClick(bool handled)
{
	HandleClick();
	if (emit) emit = !onClick.emit();
<<<<<<< HEAD
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerClick(emit);
=======
	if (GetContainer()) GetContainer()->TriggerClick(emit);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return !emit;
}

void Widget::TriggerMouseActivate()
{
<<<<<<< HEAD
	m_mouseActive = true;
	HandleMouseActivate();
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseActivate();
=======
	HandleMouseActivate();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Widget::TriggerMouseDeactivate()
{
<<<<<<< HEAD
	m_mouseActive = false;
	HandleMouseDeactivate();
	if (GetContainer() && !IsFloating()) GetContainer()->TriggerMouseDeactivate();
=======
	HandleMouseDeactivate();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Widget::TriggerSelect()
{
<<<<<<< HEAD
	m_selected = true;
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	HandleSelect();
}

void Widget::TriggerDeselect()
{
<<<<<<< HEAD
	m_selected = false;
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	HandleDeselect();
}

void Widget::RegisterBindPoint(const std::string &bindName, sigc::slot<void,PropertyMap &,const std::string &> method)
{
	m_bindPoints[bindName] = method;
}

void Widget::Bind(const std::string &bindName, PropertiedObject *object, const std::string &propertyName)
{
	std::map< std::string,sigc::slot<void,PropertyMap &,const std::string &> >::const_iterator bindPointIter = m_bindPoints.find(bindName);
	if (bindPointIter == m_bindPoints.end())
		return;

	sigc::connection conn = object->Properties().Connect(propertyName, (*bindPointIter).second);

	std::map<std::string,sigc::connection>::iterator bindIter = m_binds.find(bindName);
	if (bindIter != m_binds.end()) {
		(*bindIter).second.disconnect();
		(*bindIter).second = conn;
	}
	else
		m_binds.insert(bindIter, std::make_pair(bindName, conn));

	(*bindPointIter).second(object->Properties(), propertyName);
}

}
