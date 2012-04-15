#ifndef _UI_CONTAINER_H
#define _UI_CONTAINER_H

#include "Widget.h"
#include <list>

// Container is the base class for all UI containers. Containers must
// provide a Layout() method that implements its layout strategy. Layout()
// will typically call GetMetrics() on its children to request their sizings,
// then call SetSize() on its children to set their size appropriately.
// Containers should then call LayoutChildren() to make its children do their
// layout.
//
// Containers don't have provide Update() or Draw(). If they do they should
// make sure that they call the baseclass methods so that child widgets will
// also receive these methods.

namespace UI {

class Container: public Widget {

protected:
	// can't instantiate a base container directly
	Container(Context *context) : Widget(context) {}

public:
	virtual ~Container();

	virtual void Layout() = 0;
	virtual void Update();
	virtual void Draw();

	virtual bool IsContainer() const { return true; }

	virtual Widget *GetWidgetAt(const vector2f &pos);

	typedef std::list<Widget*>::const_iterator WidgetIterator;
	const WidgetIterator WidgetsBegin() const { return m_widgets.begin(); }
	const WidgetIterator WidgetsEnd() const { return m_widgets.end(); }

protected:
	void LayoutChildren();

	void AddWidget(Widget *);
	void RemoveWidget(Widget *);
	void SetWidgetDimensions(Widget *widget, const vector2f &position, const vector2f &size);

	// EventDispatcher needs to give us events
	friend class EventDispatcher;

	// event handlers. these fire the event handler signal for this widget
	virtual bool HandleKeyDown(const KeyboardEvent &event);
	virtual bool HandleKeyUp(const KeyboardEvent &event);
	virtual bool HandleMouseDown(const MouseButtonEvent &event);
	virtual bool HandleMouseUp(const MouseButtonEvent &event);
	virtual bool HandleMouseMove(const MouseMotionEvent &event);
	virtual bool HandleMouseWheel(const MouseWheelEvent &event);

private:
	std::list<Widget*> m_widgets;
};

}

#endif
