#include "Margin.h"
#include "LuaObject.h"

namespace UI {

class LuaMargin {
public:

};

}

static bool promotion_test(DeleteEmitter *o)
{
	return dynamic_cast<UI::Margin*>(o);
}

using namespace UI;

template <> const char *LuaObject<UI::Margin>::s_type = "UI.Margin";

template <> void LuaObject<UI::Margin>::RegisterClass()
{
	static const char *l_parent = "UI.Single";

	static const luaL_Reg l_methods[] = {

        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, promotion_test);
}
