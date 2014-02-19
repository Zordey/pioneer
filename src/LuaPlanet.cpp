<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaObject.h"
#include "LuaUtils.h"
#include "Planet.h"

/*
 * Class: Planet
 *
 * Class representing a planet. Inherits from <Body>.
 */

template <> const char *LuaObject<Planet>::s_type = "Planet";

template <> void LuaObject<Planet>::RegisterClass()
{
	const char *l_parent = "Body";

	LuaObjectBase::CreateClass(s_type, l_parent, 0, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<Planet>::DynamicCastPromotionTest);
}
