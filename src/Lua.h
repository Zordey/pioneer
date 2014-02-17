<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUA_H
#define _LUA_H

#include "LuaManager.h"

// home for the global Lua context. here so its shareable between pioneer and
// modelviewer. probably sucks in the long term
namespace Lua {

extern LuaManager *manager;

void Init();
void Uninit();

}

#endif
