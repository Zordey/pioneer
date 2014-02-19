<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _CRC32_H
#define _CRC32_H

#include <SDL_stdinc.h>
#include <vector>

class CRC32 {
public:
	CRC32();

	void AddData(const char *data, int length);
	Uint32 GetChecksum() const { return m_checksum; }

private:
	Uint32 m_checksum;

	static const Uint32 s_polynomial;
	static bool s_lookupTableGenerated;
	static Uint32 s_lookupTable[256];
};

#endif
