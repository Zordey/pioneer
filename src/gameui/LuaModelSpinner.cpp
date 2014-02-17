<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ModelSpinner.h"
#include "LuaObject.h"
#include "Pi.h"

namespace GameUI {

class LuaModelSpinner {
public:

	static int l_new(lua_State *l) {
		UI::Context *c = LuaObject<UI::Context>::CheckFromLua(1);
		const std::string name(luaL_checkstring(l, 2));
		SceneGraph::ModelSkin noskin, *skin = &noskin;
		if (lua_gettop(l) > 2)
			skin = LuaObject<SceneGraph::ModelSkin>::CheckFromLua(3);
<<<<<<< HEAD
		SceneGraph::Model *model = Pi::FindModel(name);
		LuaObject<ModelSpinner>::PushToLua(new ModelSpinner(c, model, *skin));
=======
		unsigned int pattern = 0;
		if (lua_gettop(l) > 3 && !lua_isnoneornil(l, 4))
			pattern = luaL_checkinteger(l, 4) - 1; // Lua counts from 1
		SceneGraph::Model *model = Pi::FindModel(name);
		LuaObject<ModelSpinner>::PushToLua(new ModelSpinner(c, model, *skin, pattern));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		return 1;
	}

};

}

using namespace GameUI;

template <> const char *LuaObject<GameUI::ModelSpinner>::s_type = "UI.Game.ModelSpinner";

template <> void LuaObject<GameUI::ModelSpinner>::RegisterClass()
{
	static const char *l_parent = "UI.Widget";

	static const luaL_Reg l_methods[] = {
		{ "New", LuaModelSpinner::l_new },
        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<GameUI::ModelSpinner>::DynamicCastPromotionTest);
}
