<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_EVENTDISPATCHER_H
#define UI_EVENTDISPATCHER_H

#include "Event.h"
#include <map>

namespace UI {

class Widget;
class Container;

class EventDispatcher {
public:
	EventDispatcher(Container *baseContainer) :
		m_baseContainer(baseContainer),
		m_mouseActiveReceiver(0),
<<<<<<< HEAD
		m_lastMouseOverTarget(0),
		m_keyRepeatSym(SDLK_UNKNOWN),
		m_keyRepeatActive(false)
=======
		m_lastMouseOverTarget(0)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		{}

	bool Dispatch(const Event &event);
	bool DispatchSDLEvent(const SDL_Event &event);

<<<<<<< HEAD
	void Update();

	void LayoutUpdated();

=======
	void LayoutUpdated();

	Widget *GetSelected() const { return m_selected.Get(); }
	Widget *GetMouseActive() const { return m_mouseActiveReceiver.Get(); }

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void SelectWidget(Widget *target);
	void DeselectWidget(Widget *target);

	void DisableWidget(Widget *target);
	void EnableWidget(Widget *target);

<<<<<<< HEAD
=======
	Point GetMousePos() const { return m_lastMousePosition; }

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
private:
	void DispatchMouseOverOut(Widget *target, const Point &mousePos);
	void DispatchSelect(Widget *target);

	Container *m_baseContainer;

	RefCountedPtr<Widget> m_mouseActiveReceiver;
	MouseButtonEvent::ButtonType m_mouseActiveTrigger;

	RefCountedPtr<Widget> m_lastMouseOverTarget;
	Point m_lastMousePosition;

	RefCountedPtr<Widget> m_selected;

<<<<<<< HEAD
	KeySym m_keyRepeatSym;
	bool m_keyRepeatActive;
	Uint32 m_nextKeyRepeat;

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	std::map<KeySym,Widget*> m_shortcuts;
};

}

#endif
