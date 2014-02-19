<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "Gui.h"

static const float BUTTON_SIZE = 16.f;

namespace Gui {
Button::Button()
{
	m_isPressed = false;
	m_eventMask = EVENT_MOUSEDOWN | EVENT_MOUSEUP | EVENT_MOUSEMOTION;
	SetSize(BUTTON_SIZE, BUTTON_SIZE);
}

Button::~Button()
{
	_m_release.disconnect();
	_m_kbrelease.disconnect();
}

bool Button::OnMouseDown(MouseButtonEvent *e)
{
	if (e->button == SDL_BUTTON_LEFT) {
		m_isPressed = true;
		onPress.emit();
		// wait for mouse release, regardless of where on screen
		_m_release = RawEvents::onMouseUp.connect(sigc::mem_fun(this, &Button::OnRawMouseUp));
	}
	return false;
}

bool Button::OnMouseUp(MouseButtonEvent *e)
{
	if ((e->button == SDL_BUTTON_LEFT) && m_isPressed) {
		m_isPressed = false;
		_m_release.disconnect();
		onRelease.emit();
		onClick.emit();
	}
	return false;
}

void Button::OnActivate()
{
	// activated by keyboard shortcut
	m_isPressed = true;
	_m_kbrelease = RawEvents::onKeyUp.connect(sigc::mem_fun(this, &Button::OnRawKeyUp));
	onPress.emit();
}

void Button::OnRawKeyUp(SDL_KeyboardEvent *e)
{
	if (e->keysym.sym == m_shortcut.sym) {
		m_isPressed = false;
		_m_kbrelease.disconnect();
		onRelease.emit();
		onClick.emit();
	}
}

void Button::OnRawMouseUp(MouseButtonEvent *e)
{
	if (e->button == SDL_BUTTON_LEFT) {
		m_isPressed = false;
		_m_release.disconnect();
		onRelease.emit();
	}
}

void SolidButton::GetSizeRequested(float size[2])
{
	size[0] = size[1] = BUTTON_SIZE;
}

void TransparentButton::GetSizeRequested(float size[2])
{
	size[0] = size[1] = BUTTON_SIZE;
}

void SolidButton::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float size[2];
	GetSize(size);
	if (IsPressed()) {
		Theme::DrawIndent(size, Screen::alphaBlendState);
	} else {
		Theme::DrawOutdent(size, Screen::alphaBlendState);
	}
}
void TransparentButton::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float size[2];
	GetSize(size);
	Theme::DrawHollowRect(size, Color::WHITE, Screen::alphaBlendState);
}

LabelButton::LabelButton(Label *label): Button()
{
	m_label = label;
	m_padding = 2.0;
	onSetSize.connect(sigc::mem_fun(this, &LabelButton::OnSetSize));
}

LabelButton::~LabelButton() { delete m_label; }

void LabelButton::GetSizeRequested(float size[2])
{
	m_label->GetSizeRequested(size);
	size[0] += 2*m_padding;
	//size[1] += 2*m_padding;
}

void LabelButton::Draw()
{
<<<<<<< HEAD
=======
	PROFILE_SCOPED()
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	float size[2];
	GetSize(size);

	if (IsPressed()) {
		Theme::DrawIndent(size, Screen::alphaBlendState);
	} else {
		Theme::DrawOutdent(size, Screen::alphaBlendState);
	}
<<<<<<< HEAD
	glPushMatrix();
	glTranslatef(m_padding, m_padding*0.5, 0);
	m_label->Draw();
	glPopMatrix();
=======

	Graphics::Renderer *r = Gui::Screen::GetRenderer();
	Graphics::Renderer::MatrixTicket ticket(r, Graphics::MatrixMode::MODELVIEW);

	r->Translate(m_padding, m_padding*0.5, 0);
	m_label->Draw();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void LabelButton::OnSetSize()
{
	float size[2];
	GetSize(size);

	m_label->SetSize(size[0]-2*m_padding, size[1]);
}

}
