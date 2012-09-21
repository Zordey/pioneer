#include "Label.h"
#include "Context.h"
#include "text/TextureFont.h"

namespace UI {

Point Label::PreferredSize()
{
	vector2f textSize;
	GetContext()->GetFont(GetFontSize())->MeasureString(m_text.c_str(), textSize.x, textSize.y);
	m_preferredSize = Point(ceilf(textSize.x), ceilf(textSize.y));
	return m_preferredSize;
}

void Label::Layout()
{
	if (m_preferredSize == Point())
		PreferredSize();

	const Point &size = GetSize();
	SetActiveArea(Point(std::min(m_preferredSize.x,size.x), std::min(m_preferredSize.y,size.y)));
}

void Label::Draw()
{
	GetContext()->GetFont(GetFontSize())->RenderString(m_text.c_str(), 0.0f, 0.0f);
}

Label *Label::SetText(const std::string &text)
{
	m_text = text;
	GetContext()->RequestLayout();
	return this;
}

}
