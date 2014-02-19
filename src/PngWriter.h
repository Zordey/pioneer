<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef PNGWRITER_H
#define PNGWRITER_H

#include <SDL_stdinc.h>
#include <string>

namespace FileSystem {
	class FileSourceFS;
}

// stride is in bytes (bytes per row)
void write_png(FileSystem::FileSourceFS &fs, const std::string &path, const Uint8 *bytes, int width, int height, int stride, int bytes_per_pixel);

#endif
