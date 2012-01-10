#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "libs.h"
#include "RefCounted.h"

class Texture : public RefCounted {
public:

	struct Format {
		Format(GLint internalFormat_, GLenum dataFormat_, GLenum dataType_) :
			internalFormat(internalFormat_),
			dataFormat(dataFormat_),
			dataType(dataType_)
		{}
		GLint internalFormat; // GL_RGB8, GL_RGB8_ALPHA8 etc.
		GLenum dataFormat;    // GL_RGB, GL_RGBA...
		GLenum dataType;      // GL_UNSIGNED_BYTE etc.
	};

	enum WrapMode {
		REPEAT,
		CLAMP
	};

	enum FilterMode {
		NEAREST, //sharp
		LINEAR   //smooth (Texture will pick bilinear/trilinear, maybe anisotropic according to graphics settings)
	};

	virtual ~Texture();

	virtual void Bind();
	virtual void Unbind();
	//perhaps also Bind(int) so you can switch active texture unit

	bool IsCreated() const { return m_glTexture != 0; }
	
	GLenum GetTarget() const { return m_target; }
	
	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

	float GetTextureWidth() const { return m_texWidth; }
	float GetTextureHeight() const { return m_texHeight; }

	const Format &GetFormat() const { return m_format; }

	void DrawQuad(float x, float y, float w, float h, float tx, float ty, float tw, float th);

	inline void DrawQuad(float x, float y, float w, float h) {
		DrawQuad(x, y, w, h, 0, 0, GetTextureWidth(), GetTextureHeight());
	}

	inline void DrawQuad(float w, float h) {
		DrawQuad(0, 0, w, h, 0, 0, GetTextureWidth(), GetTextureHeight());
	}

protected:
	Texture(const Texture &) : m_format(0,0,0) {}

	Texture(GLenum target, const Format &format, WrapMode wrapMode, FilterMode filterMode, bool hasMipmaps, bool wantPow2Resize) :
		m_target(target),
		m_format(format),
		m_wrapMode(wrapMode),
		m_filterMode(filterMode),
		m_hasMipmaps(hasMipmaps),
		m_wantPow2Resize(wantPow2Resize),
		m_width(0),
		m_height(0),
		m_texWidth(0.0f),
		m_texHeight(0.0f),
		m_glTexture(0)
	{}

	void CreateFromArray(const void *data, unsigned int width, unsigned int height);
	bool CreateFromSurface(SDL_Surface *s);
	bool CreateFromFile(const std::string &filename);

    GLuint GetGLTexture() const { return m_glTexture; }

private:
	GLenum m_target; // GL_TEXTURE2D etc.
	
	Format m_format;
	WrapMode m_wrapMode;
	FilterMode m_filterMode;
	bool m_hasMipmaps;
	bool m_wantPow2Resize;

	unsigned int m_width;
	unsigned int m_height;

	float m_texWidth;
	float m_texHeight;

	GLuint m_glTexture;
};


class ModelTexture : public Texture {
public:
	ModelTexture(const std::string &filename, bool preload = false);

	virtual void Bind() {
		if (!IsCreated())
			Load();
		Texture::Bind();
	}

	const std::string &GetFilename() const { return m_filename; }

private:
	void Load();

	std::string m_filename;
};


class UITexture : public Texture {
public:
	UITexture(SDL_Surface *s);
	UITexture(const std::string &filename);
};

#endif
