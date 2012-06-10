#ifndef _UI_ALIGN_H
#define _UI_ALIGN_H

#include "Single.h"

namespace UI {

class Align : public Single {
public:
	virtual vector2f PreferredSize();
	virtual void Layout();

	enum Direction {
		TOP_LEFT,
		TOP,
		TOP_RIGHT,
		LEFT,
		MIDDLE,
		RIGHT,
		BOTTOM_LEFT,
		BOTTOM,
		BOTTOM_RIGHT
	};

protected:
    friend class Context;
	Align(Context *context, Direction direction) : Single(context), m_direction(direction) {}

private:
	Direction m_direction;
};

}

#endif
