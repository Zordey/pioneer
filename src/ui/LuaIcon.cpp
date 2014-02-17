<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Icon.h"
#include "LuaObject.h"

namespace UI {

class LuaIcon {
public:

	static int l_set_color(lua_State *l) {
		UI::Icon *icon = LuaObject<UI::Icon>::CheckFromLua(1);
		Color c = Color::FromLuaTable(l, 2);
		icon->SetColor(c);
		lua_pushvalue(l, 1);
		return 1;
	}

};

}

using namespace UI;

template <> const char *LuaObject<UI::Icon>::s_type = "UI.Icon";

template <> void LuaObject<UI::Icon>::RegisterClass()
{
	static const char *l_parent = "UI.Widget";

	static const luaL_Reg l_methods[] = {
		{ "SetColor", LuaIcon::l_set_color },
		{ 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<UI::Icon>::DynamicCastPromotionTest);
}
