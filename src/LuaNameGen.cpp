<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "LuaNameGen.h"
#include "LuaObject.h"
#include "galaxy/StarSystem.h"
#include "Random.h"

static const std::string DEFAULT_FULL_NAME_MALE("Tom Morton");
static const std::string DEFAULT_FULL_NAME_FEMALE("Thomasina Mortonella");
static const std::string DEFAULT_SURNAME("Jameson");
static const std::string DEFAULT_BODY_NAME("Planet Rock");

static bool GetNameGenFunc(lua_State *l, const char *func)
{
	LUA_DEBUG_START(l);

<<<<<<< HEAD
	lua_getglobal(l, "NameGen");
	if (lua_isnil(l, -1)) {
		lua_pop(l, 1);
		LUA_DEBUG_END(l, 0);
		return false;
	}
=======
	if (!pi_lua_import(l, "NameGen"))
		return false;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	lua_getfield(l, -1, func);
	if (lua_isnil(l, -1)) {
		lua_pop(l, 2);
		LUA_DEBUG_END(l, 0);
		return false;
	}

	lua_remove(l, -2);

	LUA_DEBUG_END(l, 1);
	return true;
}

std::string LuaNameGen::FullName(bool isFemale, RefCountedPtr<Random> &rng)
{
	lua_State *l = m_luaManager->GetLuaState();

	if (!GetNameGenFunc(l, "FullName"))
		return isFemale ? DEFAULT_FULL_NAME_FEMALE : DEFAULT_FULL_NAME_MALE;

	lua_pushboolean(l, isFemale);
	LuaObject<Random>::PushToLua(rng.Get());
	pi_lua_protected_call(l, 2, 1);

	std::string fullname = luaL_checkstring(l, -1);
	lua_pop(l, 1);

	return fullname;
}

std::string LuaNameGen::Surname(RefCountedPtr<Random> &rng)
{
	lua_State *l = m_luaManager->GetLuaState();

	if (!GetNameGenFunc(l, "Surname"))
		return DEFAULT_SURNAME;

	LuaObject<Random>::PushToLua(rng.Get());
	pi_lua_protected_call(l, 1, 1);

	std::string surname = luaL_checkstring(l, -1);
	lua_pop(l, 1);

	return surname;
}

std::string LuaNameGen::BodyName(SystemBody *body, RefCountedPtr<Random> &rng)
{
	lua_State *l = m_luaManager->GetLuaState();

	if (!GetNameGenFunc(l, "BodyName"))
		return DEFAULT_BODY_NAME;

	LuaObject<SystemBody>::PushToLua(body);
	LuaObject<Random>::PushToLua(rng.Get());
	pi_lua_protected_call(l, 2, 1);

	std::string bodyname = luaL_checkstring(l, -1);
	lua_pop(l, 1);

	return bodyname;
}
