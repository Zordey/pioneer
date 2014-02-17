<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Lua.h"

namespace UI {
namespace Lua {

void Init()
{
	LuaObject<UI::Align>::RegisterClass();
	LuaObject<UI::Background>::RegisterClass();
	LuaObject<UI::Box>::RegisterClass();
	LuaObject<UI::HBox>::RegisterClass();
	LuaObject<UI::VBox>::RegisterClass();
	LuaObject<UI::Button>::RegisterClass();
	LuaObject<UI::CheckBox>::RegisterClass();
	LuaObject<UI::ColorBackground>::RegisterClass();
	LuaObject<UI::Container>::RegisterClass();
	LuaObject<UI::Context>::RegisterClass();
	LuaObject<UI::DropDown>::RegisterClass();
	LuaObject<UI::Gradient>::RegisterClass();
	LuaObject<UI::Expand>::RegisterClass();
	LuaObject<UI::Gauge>::RegisterClass();
	LuaObject<UI::Grid>::RegisterClass();
	LuaObject<UI::Icon>::RegisterClass();
	LuaObject<UI::Image>::RegisterClass();
	LuaObject<UI::Label>::RegisterClass();
<<<<<<< HEAD
=======
	LuaObject<UI::Layer>::RegisterClass();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	LuaObject<UI::List>::RegisterClass();
	LuaObject<UI::Margin>::RegisterClass();
	LuaObject<UI::MultiLineText>::RegisterClass();
	LuaObject<UI::NumberLabel>::RegisterClass();
	LuaObject<UI::Scroller>::RegisterClass();
	LuaObject<UI::Single>::RegisterClass();
	LuaObject<UI::Slider>::RegisterClass();
	LuaObject<UI::SmallButton>::RegisterClass();
	LuaObject<UI::Table>::RegisterClass();
	LuaObject<UI::TextEntry>::RegisterClass();
	LuaObject<UI::HSlider>::RegisterClass();
	LuaObject<UI::VSlider>::RegisterClass();
	LuaObject<UI::Widget>::RegisterClass();
}

UI::Widget *GetWidget(UI::Context *c, lua_State *l, int idx)
{
	UI::Widget *w = LuaObject<UI::Widget>::GetFromLua(idx);
	if (w) return w;

<<<<<<< HEAD
	if (lua_type(l, idx) == LUA_TSTRING)
		return c->Label(lua_tostring(l, idx));

	if (!lua_istable(l, idx)) return 0;

	LUA_DEBUG_START(l);

	int table = lua_absindex(l, idx);
	lua_pushlstring(l, "widget", 6);
	lua_rawget(l, table);

	if (lua_isuserdata(l, -1))
		w = LuaObject<UI::Widget>::GetFromLua(-1);

	lua_pop(l, 1);
	LUA_DEBUG_END(l, 0);

	return w;
=======
	if (lua_istable(l, idx)) {
		LUA_DEBUG_START(l);

		int table = lua_absindex(l, idx);
		lua_pushlstring(l, "widget", 6);
		lua_rawget(l, table);

		if (lua_isuserdata(l, -1))
			w = LuaObject<UI::Widget>::GetFromLua(-1);

		lua_pop(l, 1);
		LUA_DEBUG_END(l, 0);

		return w;
	}

	if (lua_isstring(l, idx))
		return c->Label(lua_tostring(l, idx));

	return 0;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

UI::Widget *CheckWidget(UI::Context *c, lua_State *l, int idx)
{
	UI::Widget *w = GetWidget(c, l, idx);
	if (w) return w;

	// will fail and produce a standard error message
	w = LuaObject<UI::Widget>::CheckFromLua(idx);

	return 0;
}

}
}
