<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaObject.h"
#include "LuaUtils.h"
#include "CargoBody.h"

/*
 * Class: CargoBody
 *
 * Class representing an item of cargo floating in space. Inherits from
<<<<<<< HEAD
 * <Body>.
=======
 * <ModelBody>.
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
 */

/*
 * Attribute: type
 *
 * The type of cargo contained within this cargo body, as a
 * <Constants.EquipType> constant.
 *
 * Availability:
 *
 *  alpha 10
 *
 * Status:
 *
 *  experimental
 */

template <> const char *LuaObject<CargoBody>::s_type = "CargoBody";

template <> void LuaObject<CargoBody>::RegisterClass()
{
<<<<<<< HEAD
	const char *l_parent = "Body";
=======
	const char *l_parent = "ModelBody";
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	LuaObjectBase::CreateClass(s_type, l_parent, 0, 0, 0);
	LuaObjectBase::RegisterPromotion(l_parent, s_type, LuaObject<CargoBody>::DynamicCastPromotionTest);
}
