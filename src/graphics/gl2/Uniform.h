<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GL2_UNIFORM_H
#define _GL2_UNIFORM_H
/*
 * Shader uniform
 */
#include "libs.h"
namespace Graphics {

	class Texture;

	namespace GL2 {
		class Uniform {
		public:
			Uniform();
			void Init(const char *name, GLuint program);
			void Set(int);
			void Set(float);
			void Set(const vector3f&);
			void Set(const vector3d&);
<<<<<<< HEAD
			void Set(const Color4f&);
			void Set(const int v[3]);
			void Set(const float m[9]);
=======
			void Set(const Color&);
			void Set(const int v[3]);
			void Set(const float m[9]);
			void Set(const matrix3x3f&);
			void Set(const matrix4x4f&);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
			void Set(Texture *t, unsigned int unit);

		//private:
			GLint m_location;
		};
	}
}

#endif
