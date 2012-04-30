#ifndef _UI_SCROLLER_H
#define _UI_SCROLLER_H

#include "Container.h"

namespace UI {

class HBox;
class VSlider;

class Scroller : public Container {
public:
	virtual vector2f PreferredSize();
	virtual void Layout();

	Scroller *SetInnerWidget(Widget *widget);
	Widget *GetInnerWidget() const { return m_innerWidget; }

protected:
	friend class Context;
	Scroller(Context *context);

private:
	Widget *m_innerWidget;
	VSlider *m_slider;

	void HandleScroll(float value);
};

}

#endif
