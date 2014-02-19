// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include <cstdlib>
#include "SDL.h"
#include "FileSystem.h"
<<<<<<< HEAD
=======
#include "OS.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#include "graphics/Graphics.h"
#include "graphics/Renderer.h"
#include "text/FontDescriptor.h"
#include "text/TextureFont.h"

static const int WIDTH  = 1024;
static const int HEIGHT = 768;

int main(int argc, char **argv)
{
	FileSystem::Init();

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		Output("sdl init failed: %s\n", SDL_GetError());
		exit(-1);
	}

<<<<<<< HEAD
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    switch (info->vfmt->BitsPerPixel) {
        case 16:
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
            break;
        case 24:
        case 32:
            SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
            break;
        default:
            fprintf(stderr, "invalid pixel depth: %d bpp\n", info->vfmt->BitsPerPixel);
            exit(-1);
    }
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL, 1);

	SDL_Surface *surface = SDL_SetVideoMode(WIDTH, HEIGHT, info->vfmt->BitsPerPixel, SDL_OPENGL);
	if (!surface) {
		fprintf(stderr, "sdl video mode init failed: %s\n", SDL_GetError());
		SDL_Quit();
		exit(-1);
	}

	SDL_WM_SetCaption("textstress", "textstress");

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Graphics::Settings videoSettings;
	videoSettings.width = WIDTH;
	videoSettings.height = HEIGHT;
	videoSettings.fullscreen = false;
<<<<<<< HEAD
	videoSettings.shaders = false;
	videoSettings.requestedSamples = 0;
	videoSettings.vsync = false;
	videoSettings.useTextureCompression = false;
=======
	videoSettings.requestedSamples = 0;
	videoSettings.vsync = false;
	videoSettings.useTextureCompression = false;
	videoSettings.enableDebugMessages = false;
	videoSettings.iconFile = OS::GetIconFilename();
	videoSettings.title = "textstress";

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Graphics::Renderer *r = Graphics::Init(videoSettings);

	r->SetOrthographicProjection(0, WIDTH, HEIGHT, 0, -1, 1);
	r->SetTransform(matrix4x4f::Identity());
	r->SetClearColor(Color::BLACK);
	r->SetBlendMode(Graphics::BLEND_ALPHA);
	r->SetDepthTest(false);

<<<<<<< HEAD
	const Text::FontDescriptor fontDesc(Text::FontDescriptor::Load(FileSystem::gameDataFiles, "fonts/UIFont.ini", "English"));
=======
	const Text::FontDescriptor fontDesc(Text::FontDescriptor::Load(FileSystem::gameDataFiles, "fonts/UIFont.ini", "en"));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	Text::TextureFont *font = new Text::TextureFont(fontDesc, r);

	std::string str;
	for (int i = 33; i < 127; i++)
		str.push_back(i);

	while (1) {
		bool done = false;

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
				done = true;
		}
		if (done)
			break;

		font->RenderString(str.c_str(), rand()%(WIDTH*2)-WIDTH, rand()%HEIGHT, Color::WHITE);
		r->SwapBuffers();
	}

	delete font;
	delete r;

	SDL_Quit();

	exit(0);
}
