<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef LUAWRAPPABLE_H
#define LUAWRAPPABLE_H

// all classes that can be passed through to Lua must inherit from
// LuaWrappable. this is mostly to ensure that dynamic_cast will always work
// 
// this is in a separate file so that it can be included without including all
// of LuaObject

class LuaWrappable {
public:
	virtual ~LuaWrappable() {}
};

#endif
