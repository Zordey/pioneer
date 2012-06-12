#include "Label.h"
#include "LuaObject.h"

namespace UI {

class LuaLabel {
public:

};

}

static bool promotion_test(DeleteEmitter *o)
{
	return dynamic_cast<UI::Label*>(o);
}

using namespace UI;

template <> const char *LuaObject<UI::Label>::s_type = "UI.Label";

template <> void LuaObject<UI::Label>::RegisterClass()
{
	static const char *l_parent = "UI.Widget";

	static const luaL_Reg l_methods[] = {

        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, promotion_test);
}
