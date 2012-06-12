#include "CheckBox.h"
#include "LuaObject.h"

namespace UI {

class LuaCheckBox {
public:

};

}

static bool promotion_test(DeleteEmitter *o)
{
	return dynamic_cast<UI::CheckBox*>(o);
}

using namespace UI;

template <> const char *LuaObject<UI::CheckBox>::s_type = "UI.CheckBox";

template <> void LuaObject<UI::CheckBox>::RegisterClass()
{
	static const char *l_parent = "UI.Widget";

	static const luaL_Reg l_methods[] = {

        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, promotion_test);
}
