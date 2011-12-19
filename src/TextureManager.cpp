#include "TextureManager.h"
#include <map>

void Texture::Load()
{
	if (m_isLoaded) return;

	SDL_Surface *s = IMG_Load(m_filename.c_str());
	if (!s) {
		Error("Texture::Load: %s: %s\n", m_filename.c_str(), IMG_GetError());
		return;
	}

	if (s->format->BitsPerPixel != 24 && s->format->BitsPerPixel != 32) {
		Error("Texture::Load: %s: cannot handle image with %d bits per pixel\n", m_filename.c_str(), s->format->BitsPerPixel);
		SDL_FreeSurface(s);
		return;
	}

	m_width = s->w;
	m_height = s->h;

	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	switch (s->format->BitsPerPixel) {
		case 32:
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, s->w, s->h, GL_RGBA, GL_UNSIGNED_BYTE, s->pixels);
			break;

		case 24:
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, s->w, s->h, GL_RGB, GL_UNSIGNED_BYTE, s->pixels);
			break;

		default:
			assert(0);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	
	SDL_FreeSurface(s);

	m_isLoaded = true;
}

TextureManager::~TextureManager()
{
	for (TextureCacheMap::iterator i = m_textureCache.begin(); i != m_textureCache.end(); ++i)
		delete (*i).second;
}

Texture *TextureManager::GetTexture(const std::string &filename, bool preload)
{
	TextureCacheMap::iterator i = m_textureCache.find(filename);
	if (i != m_textureCache.end())
		return (*i).second;
	
	Texture *t = new Texture(filename, preload);
	m_textureCache.insert(std::make_pair(filename, t));

	return t;

}

