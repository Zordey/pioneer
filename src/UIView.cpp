<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "UIView.h"
#include "Pi.h"
#include "ui/Context.h"
#include "gameui/Panel.h"

void UIView::Update()
{
	Pi::ui->Update();
}

void UIView::Draw3D()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Pi::ui->Draw();
}

void UIView::OnSwitchTo()
{
<<<<<<< HEAD
	Pi::ui->SetInnerWidget(
=======
	Pi::ui->DropAllLayers();
	Pi::ui->GetTopLayer()->SetInnerWidget(
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		Pi::ui->VBox()
			->PackEnd(Pi::ui->CallTemplate(m_templateName))
			->PackEnd(new GameUI::Panel(Pi::ui.Get()))
	);
}

void UIView::OnSwitchFrom()
{
<<<<<<< HEAD
	Pi::ui->RemoveInnerWidget();
=======
	Pi::ui->DropAllLayers();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Pi::ui->Layout(); // UI does important things on layout, like updating keyboard shortcuts
}
