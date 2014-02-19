<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Face.h"
#include "LuaObject.h"
#include "LuaConstants.h"

namespace GameUI {

class LuaFace {
public:

	static inline Uint32 _unpack_flags(lua_State *l) {
		LUA_DEBUG_START(l);

		Uint32 flags = 0;

		if (lua_gettop(l) > 1) {
			luaL_checktype(l, 2, LUA_TTABLE);

			lua_pushnil(l);
			while (lua_next(l, 2)) {
				flags |= static_cast<Uint32>(LuaConstants::GetConstantFromArg(l, "GameUIFaceFlags", -1));
				lua_pop(l, 1);
			}
		}

		LUA_DEBUG_END(l, 0);

		return flags;
	}

	static int l_new(lua_State *l) {
		UI::Context *c = LuaObject<UI::Context>::CheckFromLua(1);

        Uint32 flags = _unpack_flags(l);

		Uint32 seed = 0;

<<<<<<< HEAD
		if (lua_gettop(l) > 2)
=======
		if (lua_gettop(l) > 2 && !lua_isnil(l, 3))
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			seed = luaL_checkinteger(l, 3);

		LuaObject<Face>::PushToLua(new Face(c, flags, seed));
		return 1;
	}

<<<<<<< HEAD
=======
	static int l_set_height_lines(lua_State *l) {
		Face *f = LuaObject<GameUI::Face>::CheckFromLua(1);
		Uint32 lines = luaL_checkinteger(l, 2);
		f->SetHeightLines(lines);
		lua_pushvalue(l, 1);
		return 1;
	}

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

}

using namespace GameUI;

template <> const char *LuaObject<GameUI::Face>::s_type = "UI.Game.Face";

template <> void LuaObject<GameUI::Face>::RegisterClass()
{
	static const char *l_parent = "UI.Single";

	static const luaL_Reg l_methods[] = {
<<<<<<< HEAD
		{ "New", LuaFace::l_new },
=======
		{ "New",            LuaFace::l_new },
		{ "SetHeightLines", LuaFace::l_set_height_lines },
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<GameUI::Face>::DynamicCastPromotionTest);
}
