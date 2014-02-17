<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Gauge.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Gauge::Gauge(Context *context) : Widget(context),
	m_value(0.0f),
<<<<<<< HEAD
	m_warningLevel(2.0f),
	m_criticalLevel(2.0f),
	m_levelAscending(true),
=======
	m_warningLevel(1.0f),
	m_criticalLevel(1.0f),
	m_levelAscending(true),
	m_mult(1.0f),
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_style(NORMAL)
{
	RegisterBindPoint("value", sigc::mem_fun(this, &Gauge::BindValue));
	RegisterBindPoint("valuePercent", sigc::mem_fun(this, &Gauge::BindValuePercent));
}

Point Gauge::PreferredSize()
{
	SetSizeControlFlags(EXPAND_WIDTH);
	return GetContext()->GetSkin().GaugeBackground().size;
}

void Gauge::Layout()
{
	SetActiveArea(Point(GetSize().x, GetContext()->GetSkin().GaugeBackground().size.y));
}

<<<<<<< HEAD
Gauge *Gauge::SetWarningLevel(float v)
{
	m_warningLevel = Clamp(v, 0.0f, 1.0f);
=======
Gauge *Gauge::SetUpperValue(float v)
{
	m_mult = 1/v;
	UpdateStyle();
	return this;
}

Gauge *Gauge::SetWarningLevel(float v)
{
	m_warningLevel = Clamp(v*m_mult, 0.0f, 1.0f);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	UpdateStyle();
	return this;
}

Gauge *Gauge::SetCriticalLevel(float v)
{
<<<<<<< HEAD
	m_criticalLevel = Clamp(v, 0.0f, 1.0f);
=======
	m_criticalLevel = Clamp(v*m_mult, 0.0f, 1.0f);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	UpdateStyle();
	return this;
}

Gauge *Gauge::SetLevelAscending(bool ascending)
{
	m_levelAscending = ascending;
	UpdateStyle();
	return this;
}

void Gauge::SetValue(float v)
{
<<<<<<< HEAD
	m_value = Clamp(v, 0.0f, 1.0f);
=======
	m_value = Clamp(v*m_mult, 0.0f, 1.0f);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	UpdateStyle();
}

void Gauge::UpdateStyle()
{
	if (m_levelAscending)
		m_style =
			m_value > m_criticalLevel && m_criticalLevel <= 1.0f ? CRITICAL :
			m_value > m_warningLevel  && m_warningLevel  <= 1.0f ? WARNING  :
			                                                       NORMAL;
	else
		m_style =
			m_value < m_criticalLevel && m_criticalLevel <= 1.0f ? CRITICAL :
			m_value < m_warningLevel  && m_warningLevel  <= 1.0f ? WARNING  :
			                                                       NORMAL;
}

void Gauge::Draw()
{
	const Point activeOffset(GetActiveOffset());
	const Point activeArea(GetActiveArea());

	Context *c = GetContext();
	const Skin &s = c->GetSkin();

	s.DrawGaugeBackground(activeOffset, activeArea);

	if (m_value > 0.0f) {
		s.DrawGaugeMask(activeOffset, activeArea);

		const Point size(activeArea.x * m_value, activeArea.y);

		switch (m_style) {
			case NORMAL:
				s.DrawGaugeFillNormal(activeOffset, size);
				break;
			case WARNING:
				s.DrawGaugeFillWarning(activeOffset, size);
				break;
			case CRITICAL:
				s.DrawGaugeFillCritical(activeOffset, size);
				break;
		}
	}
}

void Gauge::BindValue(PropertyMap &p, const std::string &k)
{
<<<<<<< HEAD
	double v;
	p.Get(k, v);
	SetValue(Clamp(v, 0.0, 1.0));
=======
	double v = 0.0;
	p.Get(k, v);
	SetValue(v);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Gauge::BindValuePercent(PropertyMap &p, const std::string &k)
{
<<<<<<< HEAD
	double v;
=======
	double v = 0.0;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	p.Get(k, v);
	SetValue(Clamp(v, 0.0, 100.0)*0.01);
}

}
