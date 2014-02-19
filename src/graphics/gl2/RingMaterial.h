<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GL2_RINGMATERIAL_H
#define _GL2_RINGMATERIAL_H
/*
 * Planet ring material
 */
#include "libs.h"
#include "GL2Material.h"
#include "Program.h"
namespace Graphics {

	namespace GL2 {

		class RingMaterial : public Material {
		public:
			Program *CreateProgram(const MaterialDescriptor &);
			void Apply();
			void Unapply();
		};
	}
}
#endif
