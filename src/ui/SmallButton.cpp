<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "SmallButton.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Point SmallButton::PreferredSize()
{
	return GetContext()->GetSkin().CheckboxNormal().size;
}

void SmallButton::Layout()
{
	SetActiveArea(PreferredSize());
}

void SmallButton::Draw()
{
	if (IsDisabled())
		GetContext()->GetSkin().DrawSmallButtonDisabled(GetActiveOffset(), GetActiveArea());
	else if (IsMouseActive())
		GetContext()->GetSkin().DrawSmallButtonActive(GetActiveOffset(), GetActiveArea());
	else if (IsMouseOver())
		GetContext()->GetSkin().DrawSmallButtonHover(GetActiveOffset(), GetActiveArea());
	else
		GetContext()->GetSkin().DrawSmallButtonNormal(GetActiveOffset(), GetActiveArea());
}

}
