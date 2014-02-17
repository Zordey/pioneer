<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "ModManager.h"
#include "FileSystem.h"
#include "FileSourceZip.h"
#include "utils.h"

void ModManager::Init() {
	FileSystem::userFiles.MakeDirectory("mods");

	for (FileSystem::FileEnumerator files(FileSystem::userFiles, "mods", 0); !files.Finished(); files.Next()) {
		const FileSystem::FileInfo &info = files.Current();
		const std::string &zipPath = info.GetPath();
<<<<<<< HEAD
		if (ends_with(zipPath, ".zip")) {
=======
		if (ends_with_ci(zipPath, ".zip")) {
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			printf("adding mod: %s\n", zipPath.c_str());
			FileSystem::gameDataFiles.PrependSource(new FileSystem::FileSourceZip(FileSystem::userFiles, zipPath));
		}
	}
}
