<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "CellSpec.h"
#include "LuaObject.h"

namespace UI {

CellSpec CellSpec::FromLuaTable(lua_State *l, int idx) {
	const int table = lua_absindex(l, idx);
	assert(lua_istable(l, table));

	const int len = lua_rawlen(l, table);
	std::vector<float> cellPercent(len);
	for (int i = 0; i < len; i++) {
		lua_rawgeti(l, table, i+1);
		cellPercent[i] = luaL_checknumber(l, -1);
		lua_pop(l, 1);
	}

	return CellSpec(cellPercent);
}

}
