<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _TEXTUREGL_H
#define _TEXTUREGL_H

#include "Texture.h"
<<<<<<< HEAD
#include <GL/glew.h>
=======
#include "glew/glew.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace Graphics {

class TextureGL : public Texture {
public:
	virtual void Update(const void *data, const vector2f &dataSize, TextureFormat format, const unsigned int numMips);

	virtual ~TextureGL();

	void Bind();
	void Unbind();

	virtual void SetSampleMode(TextureSampleMode);
	GLuint GetTexture() const { return m_texture; }

private:
<<<<<<< HEAD
	friend class RendererLegacy;
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	friend class RendererGL2;
	TextureGL(const TextureDescriptor &descriptor, const bool useCompressed);

	GLenum m_target;
	GLuint m_texture;
};

}

#endif
