<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUAFILESYSTEM_H
#define _LUAFILESYSTEM_H

namespace LuaFileSystem {
	void Register();

	enum Root { // <enum scope='LuaFileSystem' name=FileSystemRoot prefix=ROOT_ public>
		ROOT_USER,
		ROOT_DATA
	};
}

#endif
