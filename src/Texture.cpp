#include "Texture.h"

Texture::~Texture()
{
	if (m_glTexture)
		glDeleteTextures(1, &m_glTexture);
}

void Texture::Bind()
{
	assert(m_glTexture);
	glBindTexture(m_target, m_glTexture);
}

void Texture::Unbind()
{
	glBindTexture(m_target, 0);
}

void Texture::CreateFromArray(const void *data, unsigned int width, unsigned int height)
{
	if (m_glTexture) {
		glDeleteTextures(1, &m_glTexture);
		m_glTexture = 0;
	}

	glEnable(m_target);

	glGenTextures(1, &m_glTexture);
	glBindTexture(m_target, m_glTexture);

	if (m_wrapMode == CLAMP) {
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else {
		glTexParameteri(m_target, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(m_target, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}

	if (m_filterMode == NEAREST) {
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_wantMipmaps ? GL_NEAREST_MIPMAP_NEAREST : GL_NEAREST);
	}
	else {
		glTexParameteri(m_target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(m_target, GL_TEXTURE_MIN_FILTER, m_wantMipmaps ? GL_LINEAR_MIPMAP_LINEAR : GL_LINEAR);
	}

	// XXX feels a bit icky
	switch (m_target) {
		case GL_TEXTURE_1D:
			assert(!m_wantMipmaps);
			glTexImage1D(GL_TEXTURE_1D, 0, m_format.internalFormat, width, 0, m_format.dataFormat, m_format.dataType, data);
			break;

		case GL_TEXTURE_2D:
		case GL_TEXTURE_RECTANGLE:
			if (m_wantMipmaps)
				gluBuild2DMipmaps(m_target, m_format.internalFormat, width, height, m_format.dataFormat, m_format.dataType, data);
			else
				glTexImage2D(m_target, 0, m_format.internalFormat, width, height, 0, m_format.dataFormat, m_format.dataType, data);
			break;

		default:
			assert(0);
	}

	glBindTexture(m_target, 0);
	glDisable(m_target);

	m_width = width;
	m_height = height;
}

// RGBA pixel format for converting textures
// XXX little-endian. if we ever have a port to a big-endian arch, invert shift and mask
static SDL_PixelFormat rgba_pixfmt = {
	0,                                  // palette
	32,                                 // bits per pixel
	4,                                  // bytes per pixel
	0, 0, 0, 0,                         // RGBA loss
	24, 16, 8, 0,                       // RGBA shift
	0xff, 0xff00, 0xff0000, 0xff000000, // RGBA mask
	0,                                  // colour key
	0                                   // alpha
};

bool Texture::CreateFromSurface(SDL_Surface *s)
{
	bool freeSurface = false;

	SDL_PixelFormat *pixfmt = s->format;
	if (pixfmt->BytesPerPixel != rgba_pixfmt.BytesPerPixel || pixfmt->Rmask != rgba_pixfmt.Rmask || pixfmt->Gmask != rgba_pixfmt.Gmask || pixfmt->Bmask != rgba_pixfmt.Bmask) {
		s = SDL_ConvertSurface(s, &rgba_pixfmt, SDL_SWSURFACE);
		freeSurface = true;
	}

	unsigned int width = s->w;
	unsigned int height = s->h;

	// extend to power-of-two if necessary
	int width2 = ceil_pow2(s->w);
	int height2 = ceil_pow2(s->h);
	if (s->w != width2 || s->h != height2) {
		SDL_Surface *s2 = SDL_CreateRGBSurface(SDL_SWSURFACE, width2, height2, rgba_pixfmt.BitsPerPixel, rgba_pixfmt.Rmask, rgba_pixfmt.Gmask, rgba_pixfmt.Bmask, rgba_pixfmt.Amask);

		SDL_SetAlpha(s, 0, 0);
		SDL_SetAlpha(s2, 0, 0);
		SDL_BlitSurface(s, 0, s2, 0);

		if (freeSurface)
			SDL_FreeSurface(s);

		s = s2;
		freeSurface = true;

		m_texWidth = float(width) / float(width2);
		m_texHeight = float(height) / float(height2);
	}
	else
		m_texWidth = m_texHeight = 1.0f;

	SDL_LockSurface(s);
	CreateFromArray(s->pixels, s->w, s->h);
	SDL_UnlockSurface(s);

	m_width = width;
	m_height = height;

	if (freeSurface)
		SDL_FreeSurface(s);

	return true;
}

bool Texture::CreateFromFile(const std::string &filename)
{
	SDL_Surface *s = IMG_Load(filename.c_str());
	if (!s) {
		fprintf(stderr, "Texture::CreateFromFile: %s: %s\n", filename.c_str(), IMG_GetError());
		return false;
	}

	if (!CreateFromSurface(s)) {
		fprintf(stderr, "Texture::CreateFromFile: %s: creating texture from surface failed\n", filename.c_str());
		SDL_FreeSurface(s);
		return false;
	}

	SDL_FreeSurface(s);

	return true;
}

void Texture::DrawQuad(float x, float y, float w, float h, float tx, float ty, float tw, float th)
{
	GLfloat array[4*4] = {
		x,   y+h, tx,    ty+th,
		x,   y,   tx,    ty,
		x+w, y,   tx+tw, ty,
		x+w, y+h, tx+tw, ty+th
	};

	DrawQuadArray(array);
}

void Texture::DrawUIQuad(float x, float y, float w, float h, float tx, float ty, float tw, float th)
{
	GLfloat array[4*4] = {
		x,   y+h, tx,    ty+th,
		x+w, y+h, tx+tw, ty+th,
		x+w, y,   tx+tw, ty,
		x,   y,   tx,    ty
	};

	DrawQuadArray(array);
}

void Texture::DrawQuadArray(const GLfloat *array)
{
	glEnable(GetTarget());
	Bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(GLfloat)*4, &array[0]);
	glTexCoordPointer(2, GL_FLOAT, sizeof(GLfloat)*4, &array[2]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	Unbind();
	glDisable(GetTarget());
}


ModelTexture::ModelTexture(const std::string &filename, bool preload) :
	Texture(GL_TEXTURE_2D, Format(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE), REPEAT, LINEAR, true),
	m_filename(filename)
{
	if (preload)
		Load();
}

void ModelTexture::Load()
{
	assert(!IsCreated());
	CreateFromFile(m_filename);
}


UITexture::UITexture(SDL_Surface *s) :
    Texture(GL_TEXTURE_2D, Format(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE), CLAMP, LINEAR, false)
{
	CreateFromSurface(s);
}

UITexture::UITexture(const std::string &filename) :
    Texture(GL_TEXTURE_2D, Format(GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE), CLAMP, LINEAR, false)
{
	CreateFromFile(filename);
}
