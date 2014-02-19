<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Gui.h"

namespace Gui {

Label::Label(const char *text, TextLayout::ColourMarkupMode colourMarkupMode)
{
	Init(std::string(text), colourMarkupMode);
}

Label::Label(const std::string &text, TextLayout::ColourMarkupMode colourMarkupMode)
{
	Init(text, colourMarkupMode);
}

Label::~Label()
{
	delete m_layout;
}

void Label::Init(const std::string &text, TextLayout::ColourMarkupMode colourMarkupMode)
{
	m_colourMarkupMode = colourMarkupMode;
	m_shadow = false;
	m_layout = 0;
	m_dlist = 0;
	m_font = Gui::Screen::GetFont();
<<<<<<< HEAD
	m_color = ::Color(1.0f, 1.0f, 1.0f, 1.0f);
=======
	m_color = ::Color(255);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	SetText(text);
}

void Label::UpdateLayout()
{
	if (m_layout) delete m_layout;
	m_layout = new TextLayout(m_text.c_str(), m_font, m_colourMarkupMode);
}

void Label::RecalcSize()
{
//	float size[2];
//	Screen::MeasureLayout(m_text, FLT_MAX, size);
	ResizeRequest();
}

<<<<<<< HEAD
Label *Label::Color(float r, float g, float b)
=======
Label *Label::Color(Uint8 r, Uint8 g, Uint8 b)
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
{
	m_color = ::Color(r, g, b);
	return this;
}

Label *Label::Color(const ::Color &c)
{
	m_color = c;
	return this;
}

void Label::SetText(const char *text)
{
	SetText(std::string(text));
}

void Label::SetText(const std::string &text)
{
	m_text = text;
	UpdateLayout();
	RecalcSize();
}

void Label::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	if (!m_layout) UpdateLayout();
	float size[2]; GetSize(size);
	if (m_shadow) {
<<<<<<< HEAD
		glTranslatef(1,1,0);
		m_layout->Render(size[0], Color::BLACK);
		glTranslatef(-1,-1,0);
=======
		Graphics::Renderer *r = Gui::Screen::GetRenderer();
		r->Translate(1,1,0);
		m_layout->Render(size[0], Color::BLACK);
		r->Translate(-1,-1,0);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	}
	m_layout->Render(size[0], m_color);
}

void Label::GetSizeRequested(float size[2])
{
	m_layout->MeasureSize(size[0], size);
}

}
