<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Single.h"

namespace UI {

Point Single::PreferredSize()
{
	if (!m_innerWidget) return Point();
	return m_innerWidget->CalcLayoutContribution();
}

void Single::Layout()
{
	if (!m_innerWidget) return;
	SetWidgetDimensions(m_innerWidget, Point(), m_innerWidget->CalcSize(GetSize()));
	m_innerWidget->Layout();
}

Single *Single::SetInnerWidget(Widget *widget)
{
	assert(widget);

	RemoveAllWidgets();

	AddWidget(widget);
	m_innerWidget = widget;

	return this;
}

void Single::RemoveInnerWidget()
{
	if (m_innerWidget) {
		Container::RemoveWidget(m_innerWidget);
		m_innerWidget = 0;
	}
}

void Single::RemoveWidget(Widget *widget)
{
	if (m_innerWidget != widget)
		return;
	RemoveInnerWidget();
}

}
