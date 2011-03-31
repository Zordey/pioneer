#ifndef _LUASERIALIZER_H
#define _LUASERIALIZER_H

#include "LuaManager.h"
#include "LuaObject.h"
#include "DeleteEmitter.h"
#include "Serializer.h"

class LuaSerializer : public DeleteEmitter {
	friend class LuaObject<LuaSerializer>;

public:
	void RegisterSerializer();

	void Serialize(Serializer::Writer &wr);
	void Unserialize(Serializer::Reader &rd);

private:
	static int l_register(lua_State *l);

	static void pickle(lua_State *l, int idx, std::string &out, const char *key);
	static const char *unpickle(lua_State *l, const char *pos);
};

#endif
