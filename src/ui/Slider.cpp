#include "Slider.h"
#include "Context.h"

namespace UI {

static const float MIN_SLIDER_INNER_SIZE = 16.0f;

vector2f Slider::PreferredSize()
{
	// XXX use slider gutter size
	if (m_orient == SLIDER_HORIZONTAL)
		return vector2f(MIN_SLIDER_INNER_SIZE+Skin::s_buttonNormal.borderWidth);
	else
		return vector2f(MIN_SLIDER_INNER_SIZE+Skin::s_buttonNormal.borderWidth);
}

void Slider::Layout()
{
	UpdateButton();
	Widget::Layout();
}

void Slider::UpdateButton()
{
	const float buttonBorderWidth = Skin::s_buttonNormal.borderWidth;
	const vector2f activeArea(GetActiveArea());
	if (m_orient == SLIDER_HORIZONTAL) {
		m_buttonSize = vector2f(std::min(activeArea.x-buttonBorderWidth*2, MIN_SLIDER_INNER_SIZE), activeArea.y-buttonBorderWidth*2);
		m_buttonPos = vector2f((activeArea.x-buttonBorderWidth*2-m_buttonSize.x)*m_value+buttonBorderWidth, buttonBorderWidth);
	}
	else {
		m_buttonSize = vector2f(activeArea.x-buttonBorderWidth*2, std::min(activeArea.y-buttonBorderWidth*2, MIN_SLIDER_INNER_SIZE));
		m_buttonPos = vector2f(buttonBorderWidth, (activeArea.y-buttonBorderWidth*2-m_buttonSize.y)*m_value+buttonBorderWidth);
	}
}

void Slider::Draw()
{
	GetContext()->GetSkin().DrawButtonActive(0, GetActiveArea());        // XXX gutter
	if (m_buttonDown && IsMouseActive())
		GetContext()->GetSkin().DrawButtonActive(m_buttonPos, m_buttonSize); // XXX button
	else
		GetContext()->GetSkin().DrawButtonNormal(m_buttonPos, m_buttonSize); // XXX button
}

void Slider::SetValue(float v)
{
	m_value = Clamp(v, 0.0f, 1.0f);
	UpdateButton();
}

bool Slider::HandleMouseDown(const MouseButtonEvent &event, bool emit)
{
	m_buttonDown = event.pos.x >= m_buttonPos.x && event.pos.y >= m_buttonPos.y && event.pos.x < m_buttonPos.x+m_buttonSize.x && event.pos.y < m_buttonPos.y+m_buttonSize.y;
	return Widget::HandleMouseDown(event, emit);
}

bool Slider::HandleMouseUp(const MouseButtonEvent &event, bool emit)
{
	m_buttonDown = false;
	return Widget::HandleMouseUp(event, emit);
}

bool Slider::HandleMouseMove(const MouseMotionEvent &event, bool emit)
{
	if (m_buttonDown && IsMouseActive())
		SetValue(m_orient == SLIDER_HORIZONTAL ? Clamp(event.pos.x, 0.0f, GetActiveArea().x) / GetActiveArea().x : Clamp(event.pos.y, 0.0f, GetActiveArea().y) / GetActiveArea().y);
	return Widget::HandleMouseMove(event, emit);
}

}
