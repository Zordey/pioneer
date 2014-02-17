<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GRAPHICS_H
#define _GRAPHICS_H

#include "libs.h"
<<<<<<< HEAD
=======
#include "RenderTarget.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

/*
 * bunch of reused 3d drawy routines.
 * XXX most of this is to be removed
 */
namespace Graphics {

	class Renderer;
	class Material;

	// requested video settings
	struct Settings {
		bool fullscreen;
<<<<<<< HEAD
		bool shaders;
		bool useTextureCompression;
=======
		bool useTextureCompression;
		bool enableDebugMessages;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		int vsync;
		int requestedSamples;
		int height;
		int width;
<<<<<<< HEAD
=======
		const char *iconFile;
		const char *title;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};

	//for querying available modes
	struct VideoMode {
		VideoMode(int w, int h)
		: width(w), height(h) { }

		int width;
		int height;
	};

<<<<<<< HEAD
	extern bool shadersAvailable;
	extern bool shadersEnabled;
	extern Material *vtxColorMaterial;

	extern Settings settings;
=======
	extern Material *vtxColorMaterial;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	int GetScreenWidth();
	int GetScreenHeight();

	float GetFov();
	void SetFov(float);
	float GetFovFactor(); //cached 2*tan(fov/2) for LOD

	// does SDL video init, constructs appropriate Renderer
	Renderer* Init(Settings);
	void Uninit();
<<<<<<< HEAD
	bool AreShadersEnabled();
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	std::vector<VideoMode> GetAvailableVideoModes();
}

#endif /* _RENDER_H */
