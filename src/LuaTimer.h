<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUATIMER_H
#define _LUATIMER_H

#include "LuaManager.h"
#include "DeleteEmitter.h"

class LuaTimer : public DeleteEmitter {
public:
	void Tick();
	void RemoveAll();
};

#endif
