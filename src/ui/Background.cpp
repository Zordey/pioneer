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
	const Skin::BorderedRectElement &elem(GetContext()->GetSkin().BackgroundNormal());
	const Point borderSize(elem.borderWidth*2, elem.borderHeight*2);
	if (!GetInnerWidget()) return borderSize;
	Point preferredSize = SizeAdd(GetInnerWidget()->PreferredSize(), Point(elem.paddingX*2, elem.paddingY*2));
	preferredSize.x = std::max(preferredSize.x, borderSize.x);
	preferredSize.y = std::max(preferredSize.y, borderSize.y);
	return preferredSize;
}

void Background::Layout()
{
	if (!GetInnerWidget()) return;
	const Skin::BorderedRectElement &elem(GetContext()->GetSkin().BackgroundNormal());
	SetWidgetDimensions(GetInnerWidget(), Point(elem.paddingX, elem.paddingY), GetSize()-Point(elem.paddingX*2, elem.paddingY*2));
	return GetInnerWidget()->Layout();
}

void Background::Draw()
{
	GetContext()->GetSkin().DrawBackgroundNormal(Point(), GetSize());
	Single::Draw();
}

}
