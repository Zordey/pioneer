#include "LuaObject.h"
#include "LuaEquipType.h"
#include "LuaUtils.h"
#include "EquipType.h"

static int l_equiptype_get_name(lua_State *l)
{
	const EquipType *et = LuaEquipType::GetFromLua(1);
	lua_pushstring(l, et->name);
	return 1;
}

static int l_equiptype_get_slot(lua_State *l)
{
	const EquipType *et = LuaEquipType::GetFromLua(1);
	lua_pushinteger(l, et->slot);
	return 1;
}

static int l_equiptype_get_base_price(lua_State *l)
{
	const EquipType *et = LuaEquipType::GetFromLua(1);
	lua_pushnumber(l, (double)(et->basePrice)*0.01);
	return 1;
}

static int l_equiptype_get_mass(lua_State *l)
{
	const EquipType *et = LuaEquipType::GetFromLua(1);
	lua_pushinteger(l, et->mass);
	return 1;
}

static int l_equiptype_get_equip_type(lua_State *l)
{
	Equip::Type e = static_cast<Equip::Type>(luaL_checkinteger(l, 1));
	if (e <= Equip::NONE || e >= Equip::TYPE_MAX)
		luaL_error(l, "Invalid equipment type '%d'", e);
	
	LuaEquipType::PushToLua(const_cast<EquipType*>(&(Equip::types[e])));
	return 1;
}

static int l_equiptype_get_equip_types(lua_State *l)
{
	LUA_DEBUG_START(l);

	Equip::Slot slot = static_cast<Equip::Slot>(luaL_checkinteger(l, 1));
	if (slot < 0 || slot >= Equip::SLOT_MAX)
		luaL_error(l, "Invalid equipment slot '%d'", slot);
	
	bool filter = false;
	if (lua_gettop(l) >= 2) {
		if (!lua_isfunction(l, 2))
			luaL_typerror(l, 2, lua_typename(l, LUA_TFUNCTION));
		filter = true;
	}

	lua_newtable(l);
	pi_lua_table_ro(l);
	
	for (int i = Equip::NONE; i < Equip::TYPE_MAX; i++) {
		EquipType *et = const_cast<EquipType*>(&(Equip::types[i]));
		if (Equip::types[i].slot == slot) {
			if (filter) {
				lua_pushvalue(l, 2);
				lua_pushinteger(l, i);
				LuaEquipType::PushToLua(et);
				lua_call(l, 2, 1);
				if (!lua_toboolean(l, -1)) {
					lua_pop(l, 1);
					continue;
				}
				lua_pop(l, 1);
			}

			lua_pushinteger(l, lua_objlen(l, -1)+1);
			lua_pushinteger(l, i);
			lua_rawset(l, -3);
		}
	}

	LUA_DEBUG_END(l, 1);

	return 1;
}

template <> const char *LuaObject<LuaUncopyable<EquipType> >::s_type = "EquipType";

template <> void LuaObject<LuaUncopyable<EquipType> >::RegisterClass()
{
	static const luaL_reg l_methods[] = {
		{ "GetName",      l_equiptype_get_name       },
		{ "GetSlot",      l_equiptype_get_slot       },
		{ "GetBasePrice", l_equiptype_get_base_price },
		{ "GetMass",      l_equiptype_get_mass       },

        { "GetEquipType",  l_equiptype_get_equip_type  },
		{ "GetEquipTypes", l_equiptype_get_equip_types },

		{ 0, 0 }
	};

	LuaObjectBase::CreateClass(s_type, NULL, l_methods, NULL);
}
