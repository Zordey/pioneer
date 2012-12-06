// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "DropDown.h"
#include "Context.h"
#include "ColorBackground.h"
#include "text/TextureFont.h"

namespace UI {

DropDown::DropDown(Context *context) : Container(context), m_popupActive(false)
{
	Context *c = GetContext();

	m_popup.Reset(c->List());
	m_popup->onOptionSelected.connect(sigc::mem_fun(onOptionSelected, &sigc::signal<void,unsigned int,const std::string &>::emit));
	m_popup->onClick.connect(sigc::mem_fun(this, &DropDown::HandlePopupClick));

	m_container = c->Background();
	m_label = c->Label("");
	m_icon = c->Icon("ArrowDown");
	m_container->SetInnerWidget(
		c->HBox(5)->PackEnd(
			WidgetSet(c->Expand(UI::Expand::HORIZONTAL)->SetInnerWidget(m_label), m_icon)
		)
	);

	AddWidget(m_container);
}

Point DropDown::PreferredSize()
{
	return m_container->PreferredSize();
}

void DropDown::Layout()
{
	SetWidgetDimensions(m_container, Point(), GetSize());
	m_container->Layout();
}

void DropDown::HandleClick()
{
	TogglePopup();
	Widget::HandleClick();
}

bool DropDown::HandlePopupClick()
{
	TogglePopup();
	return true;
}

void DropDown::TogglePopup()
{
	Context *c = GetContext();

	if (m_popupActive) {
		m_label->SetText(m_popup->GetSelectedOption());
		c->RemoveFloatingWidget(m_popup.Get());
		m_popupActive = false;
	}

	else {
		const Point pos(GetAbsolutePosition() + Point(0, GetSize().y));
		c->AddFloatingWidget(m_popup.Get(), pos, m_popup->PreferredSize());
		m_popupActive = true;
	}

}

DropDown *DropDown::AddOption(const std::string &text)
{
	float w, h;
	GetContext()->GetFont(GetFont())->MeasureString(text.c_str(), w, h);

	m_popup->AddOption(text);

	m_label->SetText(m_popup->GetSelectedOption());

	return this;
}

const std::string &DropDown::GetSelectedOption() const
{
	return m_popup->GetSelectedOption();
}

void DropDown::Clear()
{
	m_popup->Clear();
	if (m_popupActive) TogglePopup();
}

}
