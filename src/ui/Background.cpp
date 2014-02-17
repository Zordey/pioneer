<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Background.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Point Background::PreferredSize()
{
	const Point borderSize(GetContext()->GetSkin().BackgroundNormal().borderWidth*2);
	if (!GetInnerWidget()) return borderSize;
	return SizeAdd(GetInnerWidget()->PreferredSize(), borderSize);
}

void Background::Layout()
{
	if (!GetInnerWidget()) return;
	SetWidgetDimensions(GetInnerWidget(), Point(GetContext()->GetSkin().BackgroundNormal().borderWidth), GetSize()-Point(GetContext()->GetSkin().BackgroundNormal().borderWidth*2));
	return GetInnerWidget()->Layout();
}

void Background::Draw()
{
	GetContext()->GetSkin().DrawBackgroundNormal(Point(), GetSize());
	Single::Draw();
}

}
