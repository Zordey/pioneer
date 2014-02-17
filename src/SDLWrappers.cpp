<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "SDLWrappers.h"
#include "FileSystem.h"

SDLSurfacePtr LoadSurfaceFromFile(const std::string &fname, FileSystem::FileSource &source)
{
	RefCountedPtr<FileSystem::FileData> filedata = FileSystem::gameDataFiles.ReadFile(fname);
	if (!filedata) {
		fprintf(stderr, "LoadSurfaceFromFile: %s: could not read file\n", fname.c_str());
		return SDLSurfacePtr();
	}

	SDL_RWops *datastream = SDL_RWFromConstMem(filedata->GetData(), filedata->GetSize());
	SDL_Surface *surface = IMG_Load_RW(datastream, 1);
	if (!surface) {
		fprintf(stderr, "LoadSurfaceFromFile: %s: %s\n", fname.c_str(), IMG_GetError());
		return SDLSurfacePtr();
	}

	return SDLSurfacePtr::WrapNew(surface);
}

SDLSurfacePtr LoadSurfaceFromFile(const std::string &fname)
{
	return LoadSurfaceFromFile(fname, FileSystem::gameDataFiles);
}
