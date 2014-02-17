<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "LuaEvent.h"
#include "LuaManager.h"
#include "LuaObject.h"
#include "LuaUtils.h"

namespace LuaEvent {

<<<<<<< HEAD
static void _get_method_onto_stack(lua_State *l, const char *method) {
=======
static bool _get_method_onto_stack(lua_State *l, const char *method) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	LUA_DEBUG_START(l);

	int top = lua_gettop(l);

<<<<<<< HEAD
	lua_rawgeti(l, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_pushstring(l, "Event");
	lua_rawget(l, -2);
	assert(lua_istable(l, -1));

	lua_pushstring(l, method);
	lua_rawget(l, -2);
	assert(lua_isfunction(l, -1));
=======
	if (!pi_lua_import(l, "Event"))
		return false;

	lua_getfield(l, -1, method);
	if (!lua_isfunction(l, -1)) {
		lua_pop(l, 2);
		LUA_DEBUG_END(l, 0);
		return false;
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	lua_insert(l, top+1);
	lua_settop(l, top+1);

	LUA_DEBUG_END(l, 1);
<<<<<<< HEAD
=======

	return true;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Clear()
{
	lua_State *l = Lua::manager->GetLuaState();

	LUA_DEBUG_START(l);
<<<<<<< HEAD
	_get_method_onto_stack(l, "_Clear");
=======
	if (!_get_method_onto_stack(l, "_Clear")) return;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	pi_lua_protected_call(l, 0, 0);
	LUA_DEBUG_END(l, 0);
}

void Emit()
{
	lua_State *l = Lua::manager->GetLuaState();

	LUA_DEBUG_START(l);
<<<<<<< HEAD
	_get_method_onto_stack(l, "_Emit");
=======
	if (!_get_method_onto_stack(l, "_Emit")) return;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	pi_lua_protected_call(l, 0, 0);
	LUA_DEBUG_END(l, 0);
}

void Queue(const char *event, const ArgsBase &args)
{
	lua_State *l = Lua::manager->GetLuaState();

	LUA_DEBUG_START(l);
<<<<<<< HEAD
	_get_method_onto_stack(l, "Queue");
=======
	if (!_get_method_onto_stack(l, "Queue")) return;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	int top = lua_gettop(l);
    lua_pushstring(l, event);
	args.PrepareStack();
	pi_lua_protected_call(l, lua_gettop(l) - top, 0);

	LUA_DEBUG_END(l, 0);
}

}
