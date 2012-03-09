#include "Renderer.h"
#include "Texture.h"

namespace Graphics {

Renderer::Renderer(int w, int h) :
	m_width(w), m_height(h)
{

}

Renderer::~Renderer()
{
	RemoveAllCachedTextures();
}

Texture *Renderer::GetCachedTexture(const std::string &type, const std::string &name)
{
	//printf(">>> GetCachedTexture: %s/%s... ", type.c_str(), name.c_str());
	TextureCacheMap::iterator i = m_textures.find(TextureCacheKey(type,name));
	if (i == m_textures.end()) { /*printf("miss\n");*/ return 0; }
	//printf("hit [%p]\n", (*i).second->Get());
	return (*i).second->Get();
}

void Renderer::AddCachedTexture(const std::string &type, const std::string &name, Texture *texture)
{
	//printf(">>> AddCachedTexture: %s/%s [%p]\n", type.c_str(), name.c_str(), texture);
	RemoveCachedTexture(type,name);
	m_textures.insert(std::make_pair(TextureCacheKey(type,name),new RefCountedPtr<Texture>(texture)));
}

void Renderer::RemoveCachedTexture(const std::string &type, const std::string &name)
{
	TextureCacheMap::iterator i = m_textures.find(TextureCacheKey(type,name));
	if (i == m_textures.end()) return;
	delete (*i).second;
	m_textures.erase(i);
}

void Renderer::RemoveAllCachedTextures()
{
	for (TextureCacheMap::iterator i = m_textures.begin(); i != m_textures.end(); ++i)
		delete (*i).second;
	m_textures.clear();
}

}
