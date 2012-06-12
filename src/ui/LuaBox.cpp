#include "Box.h"
#include "LuaObject.h"

namespace UI {

class LuaBox {
public:

};

}

static bool promotion_test(DeleteEmitter *o)
{
	return dynamic_cast<UI::Box*>(o);
}

using namespace UI;

template <> const char *LuaObject<UI::Box>::s_type = "UI.Box";

template <> void LuaObject<UI::Box>::RegisterClass()
{
	static const char *l_parent = "UI.Container";

	static const luaL_Reg l_methods[] = {

        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, promotion_test);
}
