#ifndef _LUASHIP_H
#define _LUASHIP_H

#include "LuaObject.h"
#include "Ship.h"

class LuaShip : public LuaObject {
	LuaShip(Ship *s) : LuaObject(s) {}
};


#endif
