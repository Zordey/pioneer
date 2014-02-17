<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _WIN32_WIN32SETUP_H
#define _WIN32_WIN32SETUP_H

// MinGW targets NT4 by default. We need to set some higher versions to ensure
// that functions we need are available. Specifically, SHCreateDirectoryExA
// and GetFileSizeEx requires Windows 2000 and IE5. We include w32api.h to get
// the symbolic constants for these things.
#ifdef __MINGW32__
#	include <w32api.h>
#	ifdef WINVER
#		undef WINVER
#	endif
#	define WINVER Windows2000
#	define _WIN32_IE IE5
#endif

#endif
