#ifndef _UI_EVENT_H
#define _UI_EVENT_H

#include "libs.h"

namespace UI {

class Widget;

class NoEvent;
class KeyboardEvent;
class MouseButtonEvent;
class MouseMotionEvent;
class MouseWheelEvent;

// base event. can't be instantiated directly
class Event {
public:
	enum Type {
		NONE,
		KEYBOARD,
		MOUSE_BUTTON,
		MOUSE_MOTION,
		MOUSE_WHEEL
	};
	const Type type;

protected:
	Event(Type _type) : type(_type) {}
};

// data for various events
class KeyboardEvent : public Event {
public:
	enum Action {
		KEY_DOWN,
		KEY_UP
	};
	KeyboardEvent(Action _action, SDL_keysym _keysym) : Event(Event::KEYBOARD), action(_action), keysym(_keysym) {}
	const Action action;
	const SDL_keysym keysym;
};

class MouseEvent : public Event {
public:
	const vector2f pos; // relative to widget
protected:
	MouseEvent(Event::Type _type, const vector2f &_pos) : Event(_type), pos(_pos) {}
};

class MouseButtonEvent : public MouseEvent {
public:
	enum Action {
		BUTTON_DOWN,
		BUTTON_UP
	};
	enum ButtonType {
		BUTTON_LEFT,
		BUTTON_MIDDLE,
		BUTTON_RIGHT
	};
	MouseButtonEvent(Action _action, ButtonType _button, const vector2f &_pos) : MouseEvent(Event::MOUSE_BUTTON, _pos), action(_action), button(_button) {}
	const Action action;
	const ButtonType button;
};

class MouseMotionEvent : public MouseEvent {
public:
	MouseMotionEvent(const vector2f &_pos) : MouseEvent(Event::MOUSE_MOTION, _pos) {}
};

class MouseWheelEvent : public MouseEvent {
public:
	enum WheelDirection {
		WHEEL_UP,
		WHEEL_DOWN
	};
	MouseWheelEvent(WheelDirection _direction, const vector2f &_pos) : MouseEvent(Event::MOUSE_WHEEL, _pos), direction(_direction) {}
	WheelDirection direction;
};

}

#endif
