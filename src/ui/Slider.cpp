<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Slider.h"
#include "Context.h"

namespace UI {

Point Slider::PreferredSize()
{
	const Skin &skin = GetContext()->GetSkin();

	if (m_orient == SLIDER_HORIZONTAL) {
		SetSizeControlFlags(EXPAND_WIDTH);
		return skin.SliderHorizontalButtonNormal().size;
	}

	SetSizeControlFlags(EXPAND_HEIGHT);
	return skin.SliderVerticalButtonNormal().size;
}

void Slider::Layout()
{
	const Skin &skin = GetContext()->GetSkin();
	const Point &activeArea = GetActiveArea();

	if (m_orient == SLIDER_HORIZONTAL) {
		const Skin::EdgedRectElement &gutterRect = skin.SliderHorizontalGutter();
		m_gutterPos  = Point(0, (activeArea.y-gutterRect.size.y)/2);
		m_gutterSize = Point(activeArea.x, gutterRect.size.y);
	}
	else {
		const Skin::EdgedRectElement &gutterRect = skin.SliderVerticalGutter();
		m_gutterPos  = Point((activeArea.x-gutterRect.size.x)/2, 0);
		m_gutterSize = Point(gutterRect.size.x, activeArea.y);
	}

	UpdateButton();
	Widget::Layout();
}

void Slider::UpdateButton()
{
	const Skin &skin = GetContext()->GetSkin();

	const Point activeArea(GetActiveArea());

<<<<<<< HEAD
=======
	const float normalisedValue = (m_value - m_rangeMin) / (m_rangeMax - m_rangeMin);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if (m_orient == SLIDER_HORIZONTAL) {
		const Skin::EdgedRectElement &gutterRect = skin.SliderHorizontalGutter();
		const Skin::RectElement &buttonRect = skin.SliderHorizontalButtonNormal();

		m_buttonSize = Point(buttonRect.size.x, buttonRect.size.y);
<<<<<<< HEAD
		m_buttonPos  = Point(((activeArea.x-gutterRect.edgeWidth*2-buttonRect.size.x)*m_value)+gutterRect.edgeWidth, (activeArea.y-buttonRect.size.y)/2);
=======
		m_buttonPos  = Point(((activeArea.x-gutterRect.edgeWidth*2-buttonRect.size.x)*normalisedValue)+gutterRect.edgeWidth, (activeArea.y-buttonRect.size.y)/2);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	else {
		const Skin::EdgedRectElement &gutterRect = skin.SliderVerticalGutter();
		const Skin::RectElement &buttonRect = skin.SliderVerticalButtonNormal();

		m_buttonSize = Point(buttonRect.size.x, buttonRect.size.y);
<<<<<<< HEAD
		m_buttonPos  = Point((activeArea.x-buttonRect.size.x)/2, ((activeArea.y-gutterRect.edgeWidth*2-buttonRect.size.y)*m_value)+gutterRect.edgeWidth);
=======
		m_buttonPos  = Point((activeArea.x-buttonRect.size.x)/2, ((activeArea.y-gutterRect.edgeWidth*2-buttonRect.size.y)*normalisedValue)+gutterRect.edgeWidth);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}

	m_mouseOverButton = IsMouseOver() && PointInsideButton(m_lastMousePosition);
}

void Slider::Draw()
{
	const Skin &skin = GetContext()->GetSkin();

	if (m_orient == SLIDER_HORIZONTAL) {
		skin.DrawSliderHorizontalGutter(m_gutterPos, m_gutterSize);
		if (m_buttonDown && IsMouseActive())
			skin.DrawSliderHorizontalButtonActive(m_buttonPos, m_buttonSize);
		else if (m_mouseOverButton)
			skin.DrawSliderHorizontalButtonHover(m_buttonPos, m_buttonSize);
		else
			skin.DrawSliderHorizontalButtonNormal(m_buttonPos, m_buttonSize);
	}

	else {
		skin.DrawSliderVerticalGutter(m_gutterPos, m_gutterSize);
		if (m_buttonDown && IsMouseActive())
			skin.DrawSliderVerticalButtonActive(m_buttonPos, m_buttonSize);
		else if (m_mouseOverButton)
			skin.DrawSliderVerticalButtonHover(m_buttonPos, m_buttonSize);
		else
			skin.DrawSliderVerticalButtonNormal(m_buttonPos, m_buttonSize);
	}
}

bool Slider::PointInsideButton(const Point &p)
{
	return p.x >= m_buttonPos.x && p.y >= m_buttonPos.y && p.x < m_buttonPos.x+m_buttonSize.x && p.y <= m_buttonPos.y+m_buttonSize.y;
}

void Slider::SetValue(float v)
{
<<<<<<< HEAD
	m_value = Clamp(v, 0.0f, 1.0f);
=======
	m_value = Clamp(v, m_rangeMin, m_rangeMax);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	onValueChanged.emit(m_value);
	UpdateButton();
}

<<<<<<< HEAD
=======
Slider *Slider::SetRange(float min, float max)
{
	assert(min < max);
	if (!is_equal_exact(m_rangeMin, min) || !is_equal_exact(m_rangeMax, max)) {
		m_rangeMin = min;
		m_rangeMax = max;
		m_value = Clamp(m_value, m_rangeMin, m_rangeMax);
		onValueChanged.emit(m_value);
		UpdateButton();
	}
	return this;
}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
void Slider::HandleMouseDown(const MouseButtonEvent &event)
{
	m_buttonDown = PointInsideButton(event.pos);

    if (!m_buttonDown) {
		float change = 0.0f;

		if (m_orient == SLIDER_HORIZONTAL) {
			if (m_lastMousePosition.x < m_buttonPos.x)
				change = -0.1f;
			else
				change = 0.1f;
		}
		else {
			if (m_lastMousePosition.y < m_buttonPos.y)
				change = -0.1f;
			else
				change = 0.1f;
		}

		SetValue(GetValue()+change);
	}

	Widget::HandleMouseDown(event);
}

void Slider::HandleMouseUp(const MouseButtonEvent &event)
{
	m_buttonDown = false;
	Widget::HandleMouseUp(event);
}

void Slider::HandleMouseMove(const MouseMotionEvent &event)
{
	const Skin &skin = GetContext()->GetSkin();

	if (m_buttonDown && IsMouseActive()) {

		float travel;

		if (m_orient == SLIDER_HORIZONTAL) {
			const Skin::EdgedRectElement &gutterRect = skin.SliderHorizontalGutter();
			const Skin::RectElement &buttonRect = skin.SliderHorizontalButtonNormal();

			const int effectiveLength = GetActiveArea().x - gutterRect.edgeWidth*2 - buttonRect.size.x;
			const int pos = Clamp(event.pos.x - int(gutterRect.edgeWidth) - buttonRect.size.x/2 - GetActiveOffset().x, 0, effectiveLength);

			travel = float(pos) / effectiveLength;
		}

		else {
			const Skin::EdgedRectElement &gutterRect = skin.SliderVerticalGutter();
			const Skin::RectElement &buttonRect = skin.SliderVerticalButtonNormal();

			const int effectiveLength = GetActiveArea().y - gutterRect.edgeWidth*2 - buttonRect.size.y;
			const int pos = Clamp(event.pos.y - int(gutterRect.edgeWidth) - buttonRect.size.y/2 - GetActiveOffset().y, 0, effectiveLength);

			travel = float(pos) / effectiveLength;
		}

		SetValue(travel);
	}

	else {
		m_lastMousePosition = event.pos;
		m_mouseOverButton = PointInsideButton(event.pos);
	}

	Widget::HandleMouseMove(event);
}

void Slider::HandleMouseOut()
{
	m_mouseOverButton = false;
	Widget::HandleMouseOut();
}

}
