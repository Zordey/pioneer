#ifndef _TEXTURE_H
#define _TEXTURE_H

#include "libs.h"

class Texture {
public:
	Texture(const std::string &filename, bool preload = false) :
		m_filename(filename),
		m_isLoaded(false),
		m_width(-1),
		m_height(-1),
		m_tex(0)
	{
		if (preload)
			Load();
	}
	~Texture() {
		if (m_tex)
			glDeleteTextures(1, &m_tex);
	}

	void BindTexture() {
		if (!IsLoaded())
			Load();
		glBindTexture(GL_TEXTURE_2D, m_tex);
	}

	const std::string &GetFilename() const { return m_filename; }
	bool IsLoaded() const { return m_isLoaded; }

	int GetWidth() const { return m_width; }
	int GetHeight() const { return m_height; }

private:
	void Load();

	std::string m_filename;
	bool m_isLoaded;
	int m_width, m_height;
	GLuint m_tex;
};

#endif
