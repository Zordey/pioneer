<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef PROPERTIEDOBJECT_H
#define PROPERTIEDOBJECT_H

#include "PropertyMap.h"

class LuaManager;

class PropertiedObject {
public:
	PropertyMap &Properties() { return m_properties; }

protected:
	PropertiedObject(LuaManager *lua) : m_properties(lua) {}

private:
	PropertyMap m_properties;
};

#endif
