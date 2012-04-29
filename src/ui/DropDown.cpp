#include "DropDown.h"
#include "Context.h"
#include "ColorBackground.h"
#include "text/TextureFont.h"

namespace UI {

DropDown::DropDown(Context *context) : Widget(context), m_selected(0), m_popup(0), m_popupActive(false)
{
}

void DropDown::CalcSizePos()
{
	const float textHeight = GetContext()->GetFont()->GetHeight() + GetContext()->GetFont()->GetDescender();
	float textWidth = textHeight;
	for (std::vector<std::string>::const_iterator i = m_options.begin(); i != m_options.end(); ++i) {
		float w, h;
		GetContext()->GetFont()->MeasureString((*i).c_str(), w, h);
		if (textWidth < w) textWidth = w;
	}

	m_textPos = vector2f(Skin::s_backgroundNormal.borderWidth);
	m_textSize = vector2f(textWidth,textHeight);

	m_backgroundPos = vector2f(0);
	m_backgroundSize = m_textSize+Skin::s_backgroundNormal.borderWidth*2;

	m_buttonPos = vector2f(m_backgroundSize.x,0);
	m_buttonSize = vector2f(m_backgroundSize.y);

	m_preferredSize = vector2f(m_backgroundSize.x+m_buttonSize.x,m_backgroundSize.y);
}

vector2f DropDown::PreferredSize()
{
	CalcSizePos();
	return m_preferredSize;
}

void DropDown::Layout()
{
	if (m_preferredSize.ExactlyEqual(0))
		CalcSizePos();

	const vector2f size(GetSize());
	SetActiveArea(vector2f(std::min(m_preferredSize.x,size.x), std::min(m_preferredSize.y,size.y)));
}

void DropDown::Draw()
{
	if (IsMouseActive()) {
		GetContext()->GetSkin().DrawBackgroundActive(m_backgroundPos, m_backgroundSize);
		GetContext()->GetSkin().DrawButtonActive(m_buttonPos, m_buttonSize);
	}
	else {
		GetContext()->GetSkin().DrawBackgroundNormal(m_backgroundPos, m_backgroundSize);
		GetContext()->GetSkin().DrawButtonNormal(m_buttonPos, m_buttonSize);
	}

	if (m_selected < m_options.size())
		// XXX scissor
		GetContext()->GetFont()->RenderString(m_options[m_selected].c_str(), m_textPos.x, m_textPos.y);
}

void DropDown::BuildPopup()
{
	Context *c = GetContext();

	VBox *vbox;
	m_popup = c->Background()->SetInnerWidget(
		(vbox = c->VBox())
	);

	for (unsigned int i = 0; i < m_options.size(); i++) {
		ColorBackground *background = c->ColorBackground(Color(0,0,0,0));
		vbox->PackEnd(background->SetInnerWidget(c->Label(m_options[i])));

		background->onMouseOver.connect(sigc::bind(sigc::mem_fun(this, &DropDown::HandlePopupOptionMouseOver), background));
		background->onMouseOut.connect(sigc::bind(sigc::mem_fun(this, &DropDown::HandlePopupOptionMouseOut), background));
		background->onClick.connect(sigc::bind(sigc::mem_fun(this, &DropDown::HandlePopupOptionClick), i));

		m_backgrounds.push_back(background);
	}
}

void DropDown::HandleClick()
{
	Context *c = GetContext();

	if (m_popupActive) {
		c->RemoveFloatingWidget(m_popup);
		m_popupActive = false;
	}

	else {
		if (!m_popup)
			BuildPopup();

		const vector2f pos(GetAbsolutePosition() + vector2f(0, m_backgroundSize.y));
		c->AddFloatingWidget(m_popup, pos, m_popup->PreferredSize());

		m_popupActive = true;
	}

	Widget::HandleClick();
}

bool DropDown::HandlePopupOptionMouseOver(UI::ColorBackground *background)
{
	background->SetColor(Color(0,0,0,0.5f));
	return true;
}

bool DropDown::HandlePopupOptionMouseOut(UI::ColorBackground *background)
{
	background->SetColor(Color(0,0,0,0));
	return true;
}

bool DropDown::HandlePopupOptionClick(unsigned int selected)
{
	GetContext()->RemoveFloatingWidget(m_popup);
	m_popupActive = false;

	if (m_selected != selected) {
		m_selected = selected;
		onOptionSelected.emit(m_options[selected]);
	}

	return true;
}

DropDown *DropDown::AddOption(const std::string &text)
{
	m_options.push_back(text);
	return this;
}

}
