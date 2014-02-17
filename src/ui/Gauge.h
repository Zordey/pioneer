<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_GAUGE_H
#define UI_GAUGE_H

#include "Widget.h"

namespace UI {

class Gauge: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Layout();
	virtual void Draw();

<<<<<<< HEAD
	float GetValue() const { return m_value; }
	void SetValue(float v);

=======
	float GetValue() const { return m_value/m_mult; }
	void SetValue(float v);

	Gauge *SetUpperValue(float v);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Gauge *SetWarningLevel(float v);
	Gauge *SetCriticalLevel(float v);
	Gauge *SetLevelAscending(bool ascending);

protected:
	friend class Context;
	Gauge(Context *context);

private:
	void UpdateStyle();

	void BindValue(PropertyMap &p, const std::string &k);
	void BindValuePercent(PropertyMap &p, const std::string &k);

	float m_value;

	float m_warningLevel;
	float m_criticalLevel;
	bool m_levelAscending;

<<<<<<< HEAD
=======
	float m_mult;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	enum {
		NORMAL,
		WARNING,
		CRITICAL
	} m_style;
};

}

#endif
