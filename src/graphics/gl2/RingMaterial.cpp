<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "RingMaterial.h"
#include "StringF.h"
#include "graphics/Graphics.h"
#include "graphics/RendererGL2.h"
#include "graphics/TextureGL.h"

namespace Graphics {
namespace GL2 {

Program *RingMaterial::CreateProgram(const MaterialDescriptor &desc)
{
	assert(desc.textures == 1);
	//pick light count and some defines
	unsigned int numLights = Clamp(desc.dirLights, 1u, 4u);
	std::string defines = stringf("#define NUM_LIGHTS %0{u}\n", numLights);
	return new Program("planetrings", defines);
}

void RingMaterial::Apply()
{
	m_program->Use();
	m_program->invLogZfarPlus1.Set(m_renderer->m_invLogZfarPlus1);
	assert(this->texture0);
	static_cast<TextureGL*>(texture0)->Bind();
	m_program->texture0.Set(0);
}

void RingMaterial::Unapply()
{
	static_cast<TextureGL*>(texture0)->Unbind();
}

}
}
