<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUASERIALIZER_H
#define _LUASERIALIZER_H

#include "LuaManager.h"
#include "LuaObject.h"
#include "DeleteEmitter.h"
#include "Serializer.h"

class LuaSerializer : public DeleteEmitter {
	friend class LuaObject<LuaSerializer>;

public:
	void Serialize(Serializer::Writer &wr);
	void Unserialize(Serializer::Reader &rd);

private:
	static int l_register(lua_State *l);
<<<<<<< HEAD
=======
	static int l_register_class(lua_State *l);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	static void pickle(lua_State *l, int idx, std::string &out, const char *key);
	static const char *unpickle(lua_State *l, const char *pos);
};

#endif
