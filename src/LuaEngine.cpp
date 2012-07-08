#include "LuaEngine.h"
#include "LuaObject.h"
#include "LuaUtils.h"
#include "LuaRand.h"
#include "Pi.h"
#include "utils.h"
#include "FileSystem.h"
#include "ui/Context.h"

/*
 * Interface: Engine
 *
 * A global table that exposes a number of non-game-specific values from the
 * game engine.
 *
 */

/*
 * Attribute: rand
 *
 * The global <Rand> object. Its stream of values will be different across
 * multiple Pioneer runs. Use this when you just need a random number and
 * don't care about the seed.
 *
 * Availability:
 *
 *  alpha 10
 *
 * Status:
 *
 *  stable
 */
static int l_engine_attr_rand(lua_State *l)
{
	LuaRand::PushToLua(&Pi::rng);
	return 1;
}

/*
 * Attribute: ui
 *
 * The global <UI.Context> object. New UI widgets are created through this
 * object.
 *
 * Availability:
 *
 *   alpha 25
 *
 * Status:
 *
 *   experimental
 */
static int l_engine_attr_ui(lua_State *l)
{
	LuaObject<UI::Context>::PushToLua(Pi::ui.Get());
	return 1;
}

/*
 * Attribute: userdir
 *
 * The Pioneer configuration directory (should be writable).
 *
 * Availability:
 *
 *   alpha 14
 *
 * Status:
 *
 *   deprecated
 */
static int l_engine_attr_userdir(lua_State *l)
{
	const std::string &userdir = FileSystem::GetUserDir();
	lua_pushlstring(l, userdir.c_str(), userdir.size());
	return 1;
}

/*
 * Attribute: version
 *
 * String describing the version of Pioneer
 *
 * Availability:
 *
 *   alpha 25
 *
 * Status:
 *
 *   experimental
 */
static int l_engine_attr_version(lua_State *l)
{
	std::string version(PIONEER_VERSION);
	if (strlen(PIONEER_EXTRAVERSION)) version += " (" PIONEER_EXTRAVERSION ")";
    lua_pushlstring(l, version.c_str(), version.size());
    return 1;
}

void LuaEngine::Register()
{
	static const luaL_Reg l_attrs[] = {
		{ "rand",    l_engine_attr_rand    },
		{ "ui",      l_engine_attr_ui      },
		{ "userdir", l_engine_attr_userdir },
        { "version", l_engine_attr_version },
		{ 0, 0 }
	};

	LuaObjectBase::CreateObject(0, l_attrs, 0);
	lua_setglobal(Pi::luaManager->GetLuaState(), "Engine");
}
