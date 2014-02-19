<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _FONTCACHE_H
#define _FONTCACHE_H

#include <map>
#include <string>
#include "RefCounted.h"
#include "text/TextureFont.h"

class FontCache {
public:
	FontCache() {}

	RefCountedPtr<Text::TextureFont> GetTextureFont(const std::string &name);

private:
	FontCache(const FontCache &);
	FontCache &operator=(const FontCache &);

	std::map< std::string,RefCountedPtr<Text::TextureFont> > m_textureFonts;
};

#endif

