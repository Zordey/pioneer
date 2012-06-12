#include "Image.h"
#include "LuaObject.h"

namespace UI {

class LuaImage {
public:

};

}

static bool promotion_test(DeleteEmitter *o)
{
	return dynamic_cast<UI::Image*>(o);
}

using namespace UI;

template <> const char *LuaObject<UI::Image>::s_type = "UI.Image";

template <> void LuaObject<UI::Image>::RegisterClass()
{
	static const char *l_parent = "UI.Widget";

	static const luaL_Reg l_methods[] = {

        { 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, l_parent, l_methods, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, promotion_test);
}
