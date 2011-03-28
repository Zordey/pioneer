#ifndef _LUAUTILS_H
#define _LUAUTILS_H

extern "C" {
#include "lua/lua.h"
}

inline void pi_lua_settable(lua_State *l, const char *key, int value)
{
	lua_pushstring(l, key);
	lua_pushinteger(l, value);
	lua_settable(l, -3);
}

inline void pi_lua_settable(lua_State *l, int key, int value)
{
	lua_pushinteger(l, key);
	lua_pushinteger(l, value);
	lua_settable(l, -3);
}

inline void pi_lua_settable(lua_State *l, const char *key, double value)
{
	lua_pushstring(l, key);
	lua_pushnumber(l, value);
	lua_settable(l, -3);
}

inline void pi_lua_settable(lua_State *l, int key, double value)
{
	lua_pushinteger(l, key);
	lua_pushnumber(l, value);
	lua_settable(l, -3);
}

int pi_lua_panic(lua_State *l);
	
#ifdef DEBUG
# define LUA_DEBUG_START(luaptr) const int __luaStartStackDepth = lua_gettop(luaptr);
# define LUA_DEBUG_END(luaptr, expectedStackDiff) \
	const int __luaEndStackDepth = lua_gettop(luaptr); \
	if ( __luaEndStackDepth-expectedStackDiff != __luaStartStackDepth) { \
		fprintf(stderr, "%s:%d: lua stack difference is %d, expected %d\n", \
			__FILE__, __LINE__, __luaEndStackDepth-__luaStartStackDepth, expectedStackDiff); \
		abort(); \
	}
#else
# define LUA_DEBUG_START(luaptr)
# define LUA_DEBUG_END(luaptr, expectedStackDiff)
#endif

#endif
