#ifndef _UI_SINGLE_H
#define _UI_SINGLE_H

#include "Container.h"

namespace UI {

class Single : public Container {
public:
	virtual vector2f PreferredSize();
	virtual void Layout();

	Single *SetInnerWidget(Widget *widget);
	void RemoveInnerWidget();
	Widget *GetInnerWidget() const { return m_innerWidget; }

protected:
	Single(Context *context) : Container(context), m_innerWidget(0) {}

private:
	Widget *m_innerWidget;
};

}

#endif
