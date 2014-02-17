<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "GameConfig.h"
#include "KeyBindings.h"
#include "FileSystem.h"

GameConfig::GameConfig()
{
	// set defaults
	std::map<std::string, std::string> &map = m_map[""];
<<<<<<< HEAD
	map["Lang"] = "English";
	map["DisableShaders"] = "0";
=======
	map["Lang"] = "en";
	map["DisableEclipse"] = "0";
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	map["DisableSound"] = "0";
	map["StartFullscreen"] = "0";
	map["ScrWidth"] = "800";
	map["ScrHeight"] = "600";
	map["DetailCities"] = "1";
	map["DetailPlanets"] = "1";
	map["SfxVolume"] = "0.8";
	map["EnableJoystick"] = "1";
	map["InvertMouseY"] = "0";
	map["FOVVertical"] = "65";
	map["DisplayNavTunnel"] = "0";
	map["MasterVolume"] = "0.8";
	map["MusicVolume"] = "0.8";
	map["MasterMuted"] = "0";
	map["SfxMuted"] = "0";
	map["MusicMuted"] = "0";
	map["SectorViewXRotation"] = "-10.0";
	map["SectorViewZRotation"] = "0";
	map["SectorViewZoom"] = "2.0";
	map["MaxPhysicsCyclesPerRender"] = "4";
	map["AntiAliasingMode"] = "2";
	map["JoystickDeadzone"] = "0.1";
	map["DefaultLowThrustPower"] = "0.25";
	map["VSync"] = "0";
	map["UseTextureCompression"] = "0";
<<<<<<< HEAD
	map["CockpitCamera"] = "1";
	map["WorkerThreads"] = "0";
=======
	map["WorkerThreads"] = "0";
	map["SpeedLines"] = "0";
	map["EnableCockpit"] = "0";
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

#ifdef _WIN32
	map["RedirectStdio"] = "1";
#else
	map["RedirectStdio"] = "0";
#endif
<<<<<<< HEAD
=======
	map["EnableGLDebug"] = "0";
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	Load();
}

void GameConfig::Load()
{
	Read(FileSystem::userFiles, "config.ini");
}

bool GameConfig::Save()
{
	return Write(FileSystem::userFiles, "config.ini");
}
