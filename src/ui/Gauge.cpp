// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Gauge.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Gauge::Gauge(Context *context) : Widget(context),
	m_value(0.0f),
	m_warningLevel(2.0f),
	m_criticalLevel(2.0f),
	m_levelAscending(true),
	m_style(NORMAL)
{}

Point Gauge::PreferredSize()
{
	SetSizeControlFlags(EXPAND_WIDTH);
	return GetContext()->GetSkin().GaugeBackground().size;
}

void Gauge::Layout()
{
	SetActiveArea(Point(GetSize().x, GetContext()->GetSkin().GaugeBackground().size.y));
}

Gauge *Gauge::SetWarningLevel(float v)
{
	m_warningLevel = Clamp(v, 0.0f, 1.0f);
	UpdateStyle();
	return this;
}

Gauge *Gauge::SetCriticalLevel(float v)
{
	m_criticalLevel = Clamp(v, 0.0f, 1.0f);
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
	m_value = Clamp(v, 0.0f, 1.0f);
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
		Graphics::Renderer *r = c->GetRenderer();

		r->SetBlendMode(Graphics::BLEND_SET_ALPHA);
		s.DrawGaugeMask(activeOffset, activeArea);

		r->SetBlendMode(Graphics::BLEND_DEST_ALPHA);

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

		r->SetBlendMode(Graphics::BLEND_ALPHA); // restore default
	}
}

}
