#ifndef _UI_LUA_H
#define _UI_LUA_H

#include "LuaObject.h"
#include "Context.h"

namespace UI {
	void LuaInit();
}

template <> class LuaAcquirer<UI::Align> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Background> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Box> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::HBox> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::VBox> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Button> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::CheckBox> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::ColorBackground> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Container> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Context> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::DropDown> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Grid> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Image> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Label> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::List> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Margin> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::MultiLineText> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Scroller> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Single> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Slider> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::HSlider> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::VSlider> : public LuaAcquirerRefCounted {};
template <> class LuaAcquirer<UI::Widget> : public LuaAcquirerRefCounted {};

#endif
