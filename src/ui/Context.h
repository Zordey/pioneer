#ifndef _UI_CONTEXT_H
#define _UI_CONTEXT_H

#include "RefCounted.h"
#include "text/TextureFont.h"

#include "EventDispatcher.h"
#include "Skin.h"

#include "Widget.h"
#include "FloatContainer.h"

#include "Margin.h"
#include "Align.h"
#include "Background.h"
#include "ColorBackground.h"
#include "Box.h"
#include "Grid.h"
#include "Scroller.h"
#include "Image.h"
#include "Label.h"
#include "MultiLineText.h"
#include "Button.h"
#include "CheckBox.h"
#include "Slider.h"
#include "List.h"
#include "DropDown.h"

#include "Lua.h"

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
//
// The context also manages floating widgets. Floating widgets are drawn last
// over the top of everything else. Events given to a floating widget or its
// children will not propogate to a non-floating widget.

class Context : public Single {
public:
	Context(Graphics::Renderer *renderer, int width, int height);
	virtual ~Context();

	// general purpose containers
	UI::HBox *HBox(float spacing = 0.0f) { return new UI::HBox(this, spacing); }
	UI::VBox *VBox(float spacing = 0.0f) { return new UI::VBox(this, spacing); }

	UI::Grid *Grid(const UI::CellSpec &rowSpec, const UI::CellSpec &colSpec) { return new UI::Grid(this, rowSpec, colSpec); }

	// single containers
	UI::Background *Background() { return new UI::Background(this); }
	UI::ColorBackground *ColorBackground(const Color &color) { return new UI::ColorBackground(this, color); }
	UI::Margin *Margin(float margin) { return new UI::Margin(this, margin); };
	UI::Align *Align(UI::Align::Direction direction) { return new UI::Align(this, direction); }
	UI::Scroller *Scroller() { return new UI::Scroller(this); }

	// visual elements
	UI::Image *Image(const std::string &filename, Image::StretchMode stretchMode = Image::STRETCH_PRESERVE) { return new UI::Image(this, filename, stretchMode); }
	UI::Label *Label(const std::string &text) { return new UI::Label(this, text); }

	UI::MultiLineText *MultiLineText(const std::string &text) { return new UI::MultiLineText(this, text); }

	UI::Button *Button() { return new UI::Button(this); }
	UI::CheckBox *CheckBox() { return new UI::CheckBox(this); }

	UI::HSlider *HSlider() { return new UI::HSlider(this); }
	UI::VSlider *VSlider() { return new UI::VSlider(this); }

	UI::List *List() { return new UI::List(this); }
	UI::DropDown *DropDown() { return new UI::DropDown(this); }

	// add a floating widget
	Context *AddFloatingWidget(Widget *w, const vector2f &pos, const vector2f &size) { m_float->AddWidget(w, pos, size); return this; }
	Context *RemoveFloatingWidget(Widget *w) { m_float->RemoveWidget(w); return this; }

	// considers floating widgets also
	virtual Widget *GetWidgetAtAbsolute(const vector2f &pos);

	// event dispatch delegates
	bool Dispatch(const Event &event) { return m_eventDispatcher.Dispatch(event); }
	bool DispatchSDLEvent(const SDL_Event &event) { return m_eventDispatcher.DispatchSDLEvent(event); }

	void AddShortcut(const KeySym &keysym, Widget *target) { m_eventDispatcher.AddShortcut(keysym, target); }
	void RemoveShortcut(const KeySym &keysym) { m_eventDispatcher.RemoveShortcut(keysym); }
	void ClearShortcuts() { m_eventDispatcher.ClearShortcuts(); }

	void RequestLayout() { m_needsLayout = true; }

	virtual void Layout();
	virtual void Update();
	virtual void Draw();

	// catalog, stores widgets by name
	void AddToCatalog(const std::string &name, Widget *widget);
	void RemoveFromCatalog(const std::string &name);
	Widget *GetFromCatalog(const std::string &name);

	Graphics::Renderer *GetRenderer() const { return m_renderer; }
	const Skin &GetSkin() const { return m_skin; }

	RefCountedPtr<Text::TextureFont> GetFont() const { return GetFont(Widget::FONT_SIZE_NORMAL); }
	RefCountedPtr<Text::TextureFont> GetFont(Widget::FontSize fontSize) const { return m_font[fontSize]; }

private:
	virtual vector2f PreferredSize() { return 0; }

	Graphics::Renderer *m_renderer;
	float m_width;
	float m_height;

	bool m_needsLayout;

	RefCountedPtr<FloatContainer> m_float;

	EventDispatcher m_eventDispatcher;
	Skin m_skin;

	RefCountedPtr<Text::TextureFont> m_font[FONT_SIZE_MAX];

	typedef std::map< std::string,RefCountedPtr<Widget> > CatalogMap;
	CatalogMap m_catalog;

	// used by Container::Draw to set the keep widget drawing in its bounds
	friend class Container;
	void EnableScissor(const vector2f &pos = 0, const vector2f &size = 0);
	void DisableScissor();
};

}

#endif
