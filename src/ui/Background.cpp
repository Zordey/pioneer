#include "Background.h"
#include "Context.h"
#include "Skin.h"

namespace UI {

Point Background::PreferredSize()
{
	const Point borderSize(Skin::s_backgroundNormal.borderWidth*2);
	if (!GetInnerWidget()) return borderSize;
	return GetInnerWidget()->PreferredSize() + borderSize;
}

void Background::Layout()
{
	if (!GetInnerWidget()) return;
	SetWidgetDimensions(GetInnerWidget(), Point(Skin::s_backgroundNormal.borderWidth), GetSize()-Point(Skin::s_backgroundNormal.borderWidth*2));
	return GetInnerWidget()->Layout();
}

void Background::Draw()
{
	GetContext()->GetSkin().DrawBackgroundNormal(Point(), GetSize());
	Single::Draw();
}

}
