<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Graphics.h"
#include "FileSystem.h"
#include "Material.h"
#include "RendererGL2.h"
<<<<<<< HEAD
#include "RendererLegacy.h"
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#include "OS.h"

namespace Graphics {

static bool initted = false;
<<<<<<< HEAD
bool shadersAvailable = false;
bool shadersEnabled = false;
Material *vtxColorMaterial;
Settings settings;
=======
Material *vtxColorMaterial;
static int width, height;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
static float g_fov = 85.f;
static float g_fovFactor = 1.f;

int GetScreenWidth()
{
<<<<<<< HEAD
	return settings.width;
=======
	return width;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

int GetScreenHeight()
{
<<<<<<< HEAD
	return settings.height;
=======
	return height;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

float GetFov()
{
	return g_fov;
}

void SetFov(float fov)
{
	g_fov = fov;
	g_fovFactor = 2 * tan(DEG2RAD(g_fov) / 2.f);
}

float GetFovFactor()
{
	return g_fovFactor;
}

Renderer* Init(Settings vs)
{
	assert(!initted);
	if (initted) return 0;

	// no mode set, find an ok one
	if ((vs.width <= 0) || (vs.height <= 0)) {
		const std::vector<VideoMode> modes = GetAvailableVideoModes();
		assert(!modes.empty());

		vs.width = modes.front().width;
		vs.height = modes.front().height;
	}

<<<<<<< HEAD
	const SDL_VideoInfo *info = SDL_GetVideoInfo();

	//printf("SDL_GetVideoInfo says %d bpp\n", info->vfmt->BitsPerPixel);

	switch (info->vfmt->BitsPerPixel) {
		case 16:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			break;
		case 24:
		case 32:
			SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
			SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
			break;
		default:
			fprintf(stderr, "Invalid pixel depth: %d bpp\n", info->vfmt->BitsPerPixel);
	}
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, vs.requestedSamples ? 1 : 0);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, vs.requestedSamples);
	SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, vs.vsync);

	Uint32 flags = SDL_OPENGL;
	if (vs.fullscreen) flags |= SDL_FULLSCREEN;

	// attempt sequence is:
	// 1- requested mode
	SDL_Surface *scrSurface = SDL_SetVideoMode(vs.width, vs.height, info->vfmt->BitsPerPixel, flags);

	// 2- requested mode with no anti-aliasing (skipped if no AA was requested anyway)
	if (!scrSurface && vs.requestedSamples) {
		fprintf(stderr, "Failed to set video mode. (%s). Re-trying without multisampling.\n", SDL_GetError());
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);

		scrSurface = SDL_SetVideoMode(vs.width, vs.height, info->vfmt->BitsPerPixel, flags);
	}

	// 3- requested mode with 16 bit depth buffer
	if (!scrSurface) {
		fprintf(stderr, "Failed to set video mode. (%s). Re-trying with 16-bit depth buffer\n", SDL_GetError());
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, vs.requestedSamples ? 1 : 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, vs.requestedSamples);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		scrSurface = SDL_SetVideoMode(vs.width, vs.height, info->vfmt->BitsPerPixel, flags);
	}

	// 4- requested mode with 16-bit depth buffer and no anti-aliasing
	//    (skipped if no AA was requested anyway)
	if (!scrSurface && vs.requestedSamples) {
		fprintf(stderr, "Failed to set video mode. (%s). Re-trying with 16-bit depth buffer and no multisampling\n", SDL_GetError());
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 0);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 0);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

		scrSurface = SDL_SetVideoMode(vs.width, vs.height, info->vfmt->BitsPerPixel, flags);
	}

	// 5- abort!
	if (!scrSurface) {
		OS::Error("Failed to set video mode: %s", SDL_GetError());
	}

	// this valuable is not reliable if antialiasing settings are overridden by
	// nvidia/ati/whatever settings
	int actualSamples = 0;
	SDL_GL_GetAttribute(SDL_GL_MULTISAMPLESAMPLES, &actualSamples);
	if (vs.requestedSamples != actualSamples)
		fprintf(stderr, "Requested AA mode: %dx, actual: %dx\n", vs.requestedSamples, actualSamples);
=======
	WindowSDL *window = new WindowSDL(vs, "Pioneer");
	width = window->GetWidth();
	height = window->GetHeight();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	glewInit();

	if (!glewIsSupported("GL_ARB_vertex_buffer_object"))
		Error("OpenGL extension ARB_vertex_buffer_object not supported. Pioneer can not run on your graphics card.");

	Renderer *renderer = 0;

<<<<<<< HEAD
	shadersAvailable = glewIsSupported("GL_VERSION_2_0");
	shadersEnabled = vs.shaders && shadersAvailable;

	if (shadersEnabled)
		renderer = new RendererGL2(vs);
	else
		renderer = new RendererLegacy(vs);
=======
	if (!glewIsSupported("GL_VERSION_2_0") )
		Error("OpenGL Version 2.0 is not supported. Pioneer cannot run on your graphics card.");
	
	renderer = new RendererGL2(window, vs);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	Output("Initialized %s\n", renderer->GetName());

	initted = true;

	MaterialDescriptor desc;
	desc.vertexColors = true;
	vtxColorMaterial = renderer->CreateMaterial(desc);
	vtxColorMaterial->IncRefCount();

<<<<<<< HEAD
	Graphics::settings = vs;

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return renderer;
}

void Uninit()
{
	delete vtxColorMaterial;
}

<<<<<<< HEAD
bool AreShadersEnabled()
{
	return shadersEnabled;
=======
static bool operator==(const VideoMode &a, const VideoMode &b) {
	return a.width==b.width && a.height==b.height;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

std::vector<VideoMode> GetAvailableVideoModes()
{
	std::vector<VideoMode> modes;
<<<<<<< HEAD
	//querying modes using the current pixel format
	//note - this has always been sdl_fullscreen, hopefully it does not matter
	SDL_Rect **sdlmodes = SDL_ListModes(0, SDL_HWSURFACE | SDL_FULLSCREEN);

	if (sdlmodes == 0)
		OS::Error("Failed to query video modes");

	if (sdlmodes == reinterpret_cast<SDL_Rect **>(-1)) {
		// Modes restricted. Fall back to 800x600
		modes.push_back(VideoMode(800, 600));
	} else {
		for (int i=0; sdlmodes[i]; ++i) {
			modes.push_back(VideoMode(sdlmodes[i]->w, sdlmodes[i]->h));
		}
	}
=======

	const int num_displays = SDL_GetNumVideoDisplays();
	for(int display_index = 0; display_index < num_displays; display_index++)
	{
		const int num_modes = SDL_GetNumDisplayModes(display_index);

		SDL_Rect display_bounds;
		SDL_GetDisplayBounds(display_index, &display_bounds);

		for (int display_mode = 0; display_mode < num_modes; display_mode++)
		{
			SDL_DisplayMode mode;
			SDL_GetDisplayMode(display_index, display_mode, &mode);
			// insert only if unique resolution
			if( modes.end()==std::find(modes.begin(), modes.end(), VideoMode(mode.w, mode.h)) ) {
				modes.push_back(VideoMode(mode.w, mode.h));
			}
		}
	}
	if( num_displays==0 ) {
		modes.push_back(VideoMode(800, 600));
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	return modes;
}

}
