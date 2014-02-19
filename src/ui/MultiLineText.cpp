<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "MultiLineText.h"
#include "Context.h"
#include "TextLayout.h"

namespace UI {

MultiLineText::MultiLineText(Context *context, const std::string &text) : Widget(context), m_text(text)
{
<<<<<<< HEAD
	m_layout.Reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));

	SetSizeControlFlags(EXPAND_WIDTH);
=======
	m_layout.reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Point MultiLineText::PreferredSize()
{
	if (m_preferredSize != Point())
		return m_preferredSize;
<<<<<<< HEAD
	return Point();
=======

	// 50-75 chars per line is ideal for general readability
	// http://baymard.com/blog/line-length-readability
	//
	// we'll compute a size for about 75 chars wide. container may choose to
	// override us, but if it gives us what we ask for this will make sure we
	// get something readable
	return m_layout->ComputeSize(Point(GetContext()->GetFont(GetFont())->GetGlyph(' ').advx * 75, 0));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void MultiLineText::Layout()
{
	const Point newSize(m_layout->ComputeSize(GetSize()));
	if (m_preferredSize != newSize) GetContext()->RequestLayout();
	m_preferredSize = newSize;
	SetActiveArea(m_preferredSize);
}

void MultiLineText::Draw()
{
	m_layout->Draw(GetSize(), GetDrawOffset(), GetContext()->GetScissor());
}

Widget *MultiLineText::SetFont(Font font) {
	Widget::SetFont(font);
<<<<<<< HEAD
	m_layout.Reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));
=======
	m_layout.reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return this;
}

MultiLineText *MultiLineText::SetText(const std::string &text)
{
	m_text = text;
<<<<<<< HEAD
	m_layout.Reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));
=======
	m_layout.reset(new TextLayout(GetContext()->GetFont(GetFont()), m_text));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	GetContext()->RequestLayout();
	return this;
}

MultiLineText *MultiLineText::AppendText(const std::string &text)
{
	return SetText(m_text + text);
}

}
