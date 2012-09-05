#include "LuaRef.h"
#include <cassert>

LuaRef::LuaRef(const LuaRef & ref): m_lua(ref.m_lua), m_id(ref.m_id), m_copycount(ref.m_copycount) {
	if (m_lua && m_id)
		++(*m_copycount);
}

const LuaRef & LuaRef::operator=(const LuaRef & ref) {
	if (m_id && m_lua) {
		--(*m_copycount);
	}
	CheckCopyCount();
	m_lua = ref.m_lua;
	m_id = ref.m_id;
	if(m_lua && m_id)
		++(*m_copycount);
	return *this;
}

LuaRef::~LuaRef() {
	if (m_id == 0 || m_lua == 0)
		return;
	--(*m_copycount);
	CheckCopyCount();
}

bool LuaRef::operator==(const LuaRef & ref) const {
	if (ref.m_lua != m_lua)
		return false;
	if (ref.m_id == m_id)
		return true;

	ref.PushCopyToStack();
	PushCopyToStack();
	bool return_value = lua_compare(m_lua, -1, -2, LUA_OPEQ);
	lua_pop(m_lua, 2);
	return return_value;
}

void LuaRef::CheckCopyCount() {
	if (*m_copycount <= 0) {
		delete m_copycount;
		if (!m_lua)
			return;
		PushGlobalToStack();
		luaL_unref(m_lua, -1, m_id);
		lua_pop(m_lua, 1);
	}
}

LuaRef::LuaRef(lua_State * l, int index): m_lua(l), m_id(0) {
	assert(m_lua && index);
	index = lua_absindex(m_lua, index);

	PushGlobalToStack();
	lua_pushvalue(m_lua, index);
	m_id = luaL_ref(m_lua, -2);
	lua_pop(l, 1); // Pop global.

	m_copycount = new int(1);
}


void LuaRef::PushCopyToStack() const {
	assert(m_lua && m_id);
	PushGlobalToStack();
	lua_pushinteger(m_lua, m_id);
	lua_gettable(m_lua, -2);
	lua_remove(m_lua, -2);
}

void LuaRef::PushGlobalToStack() const {
	lua_pushstring(m_lua, "LuaRef");
	lua_gettable(m_lua, LUA_REGISTRYINDEX);
	if (lua_isnil(m_lua, -1)) {
		lua_pop(m_lua, 1);
		lua_newtable(m_lua);
		lua_pushstring(m_lua, "LuaRef");
		lua_pushvalue(m_lua, -2);
		lua_settable(m_lua, LUA_REGISTRYINDEX);
	}
}

