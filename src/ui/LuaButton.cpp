<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Button.h"
#include "LuaObject.h"

namespace UI {

class LuaButton {
public:

};

}

using namespace UI;

template <> const char *LuaObject<UI::Button>::s_type = "UI.Button";

template <> void LuaObject<UI::Button>::RegisterClass()
{
	static const char *l_parent = "UI.Single";

	static const luaL_Reg l_methods[] = {

		{ 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<UI::Button>::DynamicCastPromotionTest);
}
