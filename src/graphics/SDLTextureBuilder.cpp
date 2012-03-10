#include "SDLTextureBuilder.h"
#include <SDL/SDL_image.h>

namespace Graphics {

SDLTextureBuilder::SDLTextureBuilder(SDL_Surface *surface, TextureSampleMode sampleMode, bool generateMipmaps, bool potExtend, bool forceRGBA) :
    m_surface(surface), m_sampleMode(sampleMode), m_generateMipmaps(generateMipmaps), m_potExtend(potExtend), m_forceRGBA(forceRGBA), m_prepared(false)
{
}

SDLTextureBuilder::SDLTextureBuilder(const std::string &filename, TextureSampleMode sampleMode, bool generateMipmaps, bool potExtend, bool forceRGBA) :
    m_surface(0), m_filename(filename), m_sampleMode(sampleMode), m_generateMipmaps(generateMipmaps), m_potExtend(potExtend), m_forceRGBA(forceRGBA), m_prepared(false)
{
}

SDLTextureBuilder::~SDLTextureBuilder()
{
	if (m_surface)
		SDL_FreeSurface(m_surface);
}

// RGBA and RGBpixel format for converting textures
// XXX little-endian. if we ever have a port to a big-endian arch, invert shift and mask
static SDL_PixelFormat pixelFormatRGBA = {
	0,                                  // palette
	32,                                 // bits per pixel
	4,                                  // bytes per pixel
	0, 0, 0, 0,                         // RGBA loss
	24, 16, 8, 0,                       // RGBA shift
	0xff, 0xff00, 0xff0000, 0xff000000, // RGBA mask
	0,                                  // colour key
	0                                   // alpha
};

static SDL_PixelFormat pixelFormatRGB = {
	0,                                  // palette
	24,                                 // bits per pixel
	3,                                  // bytes per pixel
	0, 0, 0, 0,                         // RGBA loss
	16, 8, 0, 0,                        // RGBA shift
	0xff, 0xff00, 0xff0000, 0,          // RGBA mask
	0,                                  // colour key
	0                                   // alpha
};

static inline bool GetTargetFormat(const SDL_PixelFormat *sourcePixelFormat, TextureFormat *targetTextureFormat, SDL_PixelFormat **targetPixelFormat, bool forceRGBA)
{
	if (!forceRGBA && sourcePixelFormat->BytesPerPixel == pixelFormatRGB.BytesPerPixel &&
			sourcePixelFormat->Rmask == pixelFormatRGB.Rmask && sourcePixelFormat->Bmask == pixelFormatRGB.Bmask && sourcePixelFormat->Gmask == pixelFormatRGB.Gmask) {
		*targetTextureFormat = TEXTURE_RGB;
		*targetPixelFormat = &pixelFormatRGB;
		return true;
	}

	if (sourcePixelFormat->BytesPerPixel == pixelFormatRGBA.BytesPerPixel &&
			sourcePixelFormat->Rmask == pixelFormatRGBA.Rmask && sourcePixelFormat->Bmask == pixelFormatRGBA.Bmask && sourcePixelFormat->Gmask == pixelFormatRGBA.Gmask) {
		*targetTextureFormat = TEXTURE_RGBA;
		*targetPixelFormat = &pixelFormatRGBA;
		return true;
	}
	
	if (!forceRGBA && sourcePixelFormat->BytesPerPixel == 3) {
		*targetTextureFormat = TEXTURE_RGB;
		*targetPixelFormat = &pixelFormatRGB;
		return false;
	}

	*targetTextureFormat = TEXTURE_RGBA;
	*targetPixelFormat = &pixelFormatRGBA;
	return false;
}

static inline Uint32 ceil_pow2(Uint32 v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}

void SDLTextureBuilder::PrepareSurface()
{
	if (m_prepared) return;

	if (!m_surface && m_filename.length() > 0)
		LoadSurface();

	TextureFormat targetTextureFormat;
	SDL_PixelFormat *targetPixelFormat;
	bool needConvert = !GetTargetFormat(m_surface->format, &targetTextureFormat, &targetPixelFormat, m_forceRGBA);

	if (needConvert) {
		SDL_Surface *s = SDL_ConvertSurface(m_surface, targetPixelFormat, SDL_SWSURFACE);
		SDL_FreeSurface(m_surface);
		m_surface = s;
	}

	unsigned int virtualWidth, actualWidth, virtualHeight, actualHeight;
	virtualWidth = actualWidth = m_surface->w;
	virtualHeight = actualHeight = m_surface->h;

	if (m_potExtend) {
		// extend to power-of-two if necessary
		actualWidth = ceil_pow2(m_surface->w);
		actualHeight = ceil_pow2(m_surface->h);
		if (actualWidth != virtualWidth || actualHeight != virtualHeight) {
			SDL_Surface *s = SDL_CreateRGBSurface(SDL_SWSURFACE, actualWidth, actualHeight, targetPixelFormat->BitsPerPixel,
				targetPixelFormat->Rmask, targetPixelFormat->Gmask, targetPixelFormat->Bmask, targetPixelFormat->Amask);

			SDL_SetAlpha(m_surface, 0, 0);
			SDL_SetAlpha(s, 0, 0);
			SDL_BlitSurface(m_surface, 0, s, 0);

			SDL_FreeSurface(m_surface);
			m_surface = s;
		}
	}

	else if (m_filename.length() > 0) {
		// power-of-to check
		unsigned long width = ceil_pow2(m_surface->w);
		unsigned long height = ceil_pow2(m_surface->h);

		if (width != virtualWidth || height != virtualHeight)
			fprintf(stderr, "WARNING: texture '%s' is not power-of-two and may not display correctly\n", m_filename.c_str());
	}

	m_descriptor = TextureDescriptor(
		targetTextureFormat,
		vector2f(actualWidth,actualHeight),
		vector2f(float(virtualWidth)/float(actualWidth),float(virtualHeight)/float(actualHeight)),
		m_sampleMode, m_generateMipmaps);
	
	m_prepared = true;
}

void SDLTextureBuilder::LoadSurface()
{
	assert(!m_surface);

	m_surface = IMG_Load(m_filename.c_str());
	if (!m_surface) {
		fprintf(stderr, "SDLTextureBuilder: couldn't load image '%s': %s\n", m_filename.c_str(), IMG_GetError());

		// XXX prepare "empty" surface

		return;
	}
}

void SDLTextureBuilder::UpdateTexture(Texture *texture)
{
	texture->Update(m_surface->pixels, vector2f(m_surface->w,m_surface->h), m_descriptor.format == TEXTURE_RGBA ? IMAGE_RGBA : IMAGE_RGB, IMAGE_UNSIGNED_BYTE);
}

}
