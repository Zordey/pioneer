#include "EventDispatcher.h"
#include "Widget.h"
#include "Container.h"

namespace UI {

static inline MouseButtonEvent::ButtonType MouseButtonFromSDLButton(Uint8 sdlButton) {
	return
		sdlButton == SDL_BUTTON_LEFT   ? MouseButtonEvent::BUTTON_LEFT   :
		sdlButton == SDL_BUTTON_MIDDLE ? MouseButtonEvent::BUTTON_MIDDLE :
		                                 MouseButtonEvent::BUTTON_RIGHT;
}

bool EventDispatcher::DispatchSDLEvent(const SDL_Event &event)
{
	switch (event.type) {
		case SDL_KEYDOWN:
			return Dispatch(KeyboardEvent(KeyboardEvent::KEY_DOWN, event.key.keysym));

		case SDL_KEYUP:
			return Dispatch(KeyboardEvent(KeyboardEvent::KEY_UP, event.key.keysym));

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_WHEELUP || event.button.button == SDL_BUTTON_WHEELDOWN)
				return Dispatch(MouseWheelEvent(event.button.button == SDL_BUTTON_WHEELUP ? MouseWheelEvent::WHEEL_UP : MouseWheelEvent::WHEEL_DOWN, vector2f(event.button.x,event.button.y)));
			return Dispatch(MouseButtonEvent(MouseButtonEvent::BUTTON_DOWN, MouseButtonFromSDLButton(event.button.button), vector2f(event.button.x,event.button.y)));

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_WHEELUP || event.button.button == SDL_BUTTON_WHEELDOWN)
				return false;
			return Dispatch(MouseButtonEvent(MouseButtonEvent::BUTTON_UP, MouseButtonFromSDLButton(event.button.button), vector2f(event.button.x,event.button.y)));

		case SDL_MOUSEMOTION:
			return Dispatch(MouseMotionEvent(vector2f(event.motion.x,event.motion.y)));
	}

	return false;
}

bool EventDispatcher::Dispatch(const Event &event)
{
	switch (event.type) {
		case Event::KEYBOARD: {
			const KeyboardEvent keyEvent = static_cast<const KeyboardEvent&>(event);
			switch (keyEvent.action) {
				case KeyboardEvent::KEY_DOWN: return m_baseContainer->TriggerKeyDown(keyEvent);
				case KeyboardEvent::KEY_UP:   return m_baseContainer->TriggerKeyUp(keyEvent);
			}
			return false;
		}

		case Event::MOUSE_BUTTON: {
			const MouseButtonEvent mouseButtonEvent = static_cast<const MouseButtonEvent&>(event);
			Widget *target = m_baseContainer->GetWidgetAtAbsolute(mouseButtonEvent.pos);

			switch (mouseButtonEvent.action) {

				case MouseButtonEvent::BUTTON_DOWN: {
					// activate widget and remember it
					assert(!m_mouseActiveReceiver);
					m_mouseActiveReceiver = target;
					target->TriggerMouseActivate();

					MouseButtonEvent translatedEvent = MouseButtonEvent(mouseButtonEvent.action, mouseButtonEvent.button, mouseButtonEvent.pos-target->GetAbsolutePosition());
					return target->TriggerMouseDown(translatedEvent);
				}

				case MouseButtonEvent::BUTTON_UP: {

					// if there's an active widget, deactivate it
					if (m_mouseActiveReceiver) {
						m_mouseActiveReceiver->TriggerMouseDeactivate();

						// if we released over the active widget, then we clicked it
						if (m_mouseActiveReceiver == target)
							m_mouseActiveReceiver->TriggerClick();

						m_mouseActiveReceiver = 0;

						// send the straight up event too
						MouseButtonEvent translatedEvent = MouseButtonEvent(mouseButtonEvent.action, mouseButtonEvent.button, mouseButtonEvent.pos-target->GetAbsolutePosition());
						bool ret = target->TriggerMouseUp(translatedEvent);

						DispatchMouseOverOut(target, mouseButtonEvent.pos);

						return ret;
					}

					MouseButtonEvent translatedEvent = MouseButtonEvent(mouseButtonEvent.action, mouseButtonEvent.button, mouseButtonEvent.pos-target->GetAbsolutePosition());
					return target->TriggerMouseUp(translatedEvent);
				}

				default:
					return false;
			}
		}

		case Event::MOUSE_MOTION: {
			const MouseMotionEvent mouseMotionEvent = static_cast<const MouseMotionEvent&>(event);

			// if there's a mouse-active widget, just send motion events directly into it
			if (m_mouseActiveReceiver) {
				MouseMotionEvent translatedEvent = MouseMotionEvent(mouseMotionEvent.pos-m_mouseActiveReceiver->GetAbsolutePosition());
				return m_mouseActiveReceiver->TriggerMouseMove(translatedEvent);
			}

			// widget directly under the mouse
			Widget *target = m_baseContainer->GetWidgetAtAbsolute(mouseMotionEvent.pos);

			DispatchMouseOverOut(target, mouseMotionEvent.pos);

			MouseMotionEvent translatedEvent = MouseMotionEvent(mouseMotionEvent.pos-target->GetAbsolutePosition());
			return target->TriggerMouseMove(translatedEvent);
		}

		case Event::MOUSE_WHEEL: {
			const MouseWheelEvent mouseWheelEvent = static_cast<const MouseWheelEvent&>(event);
			Widget *target = m_baseContainer->GetWidgetAtAbsolute(mouseWheelEvent.pos);
			return target->TriggerMouseWheel(mouseWheelEvent);
		}

		default:
			return false;
	}

	return false;
}

void EventDispatcher::DispatchMouseOverOut(Widget *target, const vector2f &mousePos)
{
	// do over/out handling for wherever the mouse is right now
	if (target != m_lastMouseOverTarget) {

		if (m_lastMouseOverTarget) {

			// if we're switching from float to non-float then we need to force the out event, even if the mouse is still over the last target.

			// only the base widget of a floating stack is marked floating, so walk up to find it
			// XXX this is doing too much work. should we flag this on the widget somewhere?
			Widget *targetBase = target;
			while (!targetBase->IsFloating() && targetBase->GetContainer()) targetBase = targetBase->GetContainer();
			Widget *lastTargetBase = m_lastMouseOverTarget;
			while (!lastTargetBase->IsFloating() && lastTargetBase->GetContainer()) lastTargetBase = lastTargetBase->GetContainer();

			// if we're moving from float->non-float or non-float->float,
			// force the out event on the last target by reporting a position
			// that is by definition outside itself
			const vector2f outPos = targetBase->IsFloating() != lastTargetBase->IsFloating() ? vector2f(-FLT_MAX) : mousePos-m_lastMouseOverTarget->GetAbsolutePosition();
			m_lastMouseOverTarget->TriggerMouseOut(outPos);
		}

		m_lastMouseOverTarget = target;
		m_lastMouseOverTarget->TriggerMouseOver(mousePos-m_lastMouseOverTarget->GetAbsolutePosition());
	}
}

}
