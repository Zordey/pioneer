<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaManager.h"
#include "FileSystem.h"
#include <cstdlib>

bool instantiated = false;

LuaManager::LuaManager() : m_lua(0) {
	if (instantiated) {
		Output("Can't instantiate more than one LuaManager");
		abort();
	}

	m_lua = luaL_newstate();
	pi_lua_open_standard_base(m_lua);
	lua_atpanic(m_lua, pi_lua_panic);

	instantiated = true;
}

LuaManager::~LuaManager() {
	lua_close(m_lua);

	instantiated = false;
}

size_t LuaManager::GetMemoryUsage() const {
	int kb = lua_gc(m_lua, LUA_GCCOUNT, 0);
	int b = lua_gc(m_lua, LUA_GCCOUNTB, 0);
	return (size_t(kb) * 1024) + b;
}

void LuaManager::CollectGarbage() {
	lua_gc(m_lua, LUA_GCCOLLECT, 0);
}
