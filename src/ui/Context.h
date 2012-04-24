#ifndef _UI_CONTEXT_H
#define _UI_CONTEXT_H

#include "RefCounted.h"
#include "text/TextureFont.h"

#include "EventDispatcher.h"
#include "Skin.h"

#include "Margin.h"
#include "Background.h"
#include "Box.h"
#include "Grid.h"
#include "Image.h"
#include "Label.h"
#include "MultiLineText.h"
#include "Button.h"
#include "Slider.h"

namespace Graphics { class Renderer; }

namespace UI {

// The UI context is the top-level container, and covers the entire screen.
// Typically you will have one UI context per renderer context. Its slightly
// different to other containers internally to allow it to be a "live" widget
// without a parent container of its own.
//
// It has the simplest layout manager possible - it will only accept a single
// container widget and will override its metrics to force it to be the full
// size of the screen.
//
// The context holds resources that are shared by all widgets. Examples of
// such resources are fonts, default styles, textures and so on. New widgets
// are created from a context, and can access their context by calling their
// GetContext() method.
//
// It also holds an event dispatcher for distributing events to its widgets.

class Context : public Single {
public:
	Context(Graphics::Renderer *renderer, int width, int height);

	// event dispatch delegates
	bool Dispatch(const Event &event) { return m_eventDispatcher.Dispatch(event); }
	bool DispatchSDLEvent(const SDL_Event &event) { return m_eventDispatcher.DispatchSDLEvent(event); }

	// general purpose containers
	UI::HBox *HBox(float spacing = 0.0f) { return new UI::HBox(this, spacing); }
	UI::VBox *VBox(float spacing = 0.0f) { return new UI::VBox(this, spacing); }

	UI::Grid *Grid(const UI::CellSpec &rowSpec, const UI::CellSpec &colSpec) { return new UI::Grid(this, rowSpec, colSpec); }

	// single containers
	UI::Background *Background(const Color &color) { return new UI::Background(this, color); }
	UI::Margin *Margin(float margin) { return new UI::Margin(this, margin); };

	// visual elements
	UI::Image *Image(const std::string &filename, Image::StretchMode stretchMode = Image::STRETCH_PRESERVE) { return new UI::Image(this, filename, stretchMode); }
	UI::Label *Label(const std::string &text) { return new UI::Label(this, text); }

	UI::MultiLineText *MultiLineText(const std::string &text) { return new UI::MultiLineText(this, text); }

	UI::Button *Button() { return new UI::Button(this); }
	UI::HSlider *HSlider() { return new UI::HSlider(this); }
	UI::VSlider *VSlider() { return new UI::VSlider(this); }

	Graphics::Renderer *GetRenderer() const { return m_renderer; }
	const Skin &GetSkin() const { return m_skin; }
	RefCountedPtr<Text::TextureFont> GetFont() const { return m_font; }

private:
	virtual vector2f PreferredSize() { return 0; }

	Graphics::Renderer *m_renderer;
	float m_width;
	float m_height;

	EventDispatcher m_eventDispatcher;
	Skin m_skin;
	RefCountedPtr<Text::TextureFont> m_font;

	// used by Container::Draw to set the keep widget drawing in its bounds
	friend class Container;
	void SetScissor(bool enabled, const vector2f &pos = 0, const vector2f &size = 0);

};

}

#endif
