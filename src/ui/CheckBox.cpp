<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "CheckBox.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Point CheckBox::PreferredSize()
{
	return GetContext()->GetSkin().CheckboxNormal().size;
}

void CheckBox::Layout()
{
	SetActiveArea(PreferredSize());
}

void CheckBox::Draw()
{
	if (m_checked) {
		if (IsDisabled())
			GetContext()->GetSkin().DrawCheckBoxCheckedDisabled(GetActiveOffset(), GetActiveArea());
		else if (IsMouseOver())
			GetContext()->GetSkin().DrawCheckBoxCheckedHover(GetActiveOffset(), GetActiveArea());
		else
			GetContext()->GetSkin().DrawCheckBoxCheckedNormal(GetActiveOffset(), GetActiveArea());
	} else {
		if (IsDisabled())
			GetContext()->GetSkin().DrawCheckBoxDisabled(GetActiveOffset(), GetActiveArea());
		else if (IsMouseOver())
			GetContext()->GetSkin().DrawCheckBoxHover(GetActiveOffset(), GetActiveArea());
		else
			GetContext()->GetSkin().DrawCheckBoxNormal(GetActiveOffset(), GetActiveArea());
	}
}

<<<<<<< HEAD
void CheckBox::HandleClick()
{
	m_checked = !m_checked;
=======
void CheckBox::Toggle()
{
	m_checked = !m_checked;
	onValueChanged.emit(m_checked);
}

bool CheckBox::IsChecked() const
{
	return m_checked;
}

void CheckBox::SetState(bool state)
{
	if (m_checked != state) {
		Toggle();
	}
}

void CheckBox::HandleClick()
{
	Toggle();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

}
