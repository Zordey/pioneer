#include "Pattern.h"
#include "FileSystem.h"
#include "graphics/Texture.h"
#include "graphics/TextureBuilder.h"

namespace Newmodel {

Pattern::Pattern()
: smoothColor(false)
, smoothPattern(false)
, name("")
{
}

Pattern::Pattern(const std::string &name_, const std::string& path, Graphics::Renderer* r)
: smoothColor(false)
, smoothPattern(true)
, name(name_)
{
	//load as a pattern, allowed:
	//patternNN.png
	//patternNN_f.png
	//patternNN_f_f.png
	//s = smooth (default for pattern)
	//n = nearest (default for color)
	if (name.length() >= 11 && name.compare(10,1, "n") == 0) smoothPattern = false;
	if (name.length() >= 13 && name.compare(12,1, "s") == 0) smoothColor = true;

	const std::string patternPath = FileSystem::JoinPathBelow(path, name);

	Graphics::TextureSampleMode sampleMode = smoothPattern ? Graphics::LINEAR_CLAMP : Graphics::NEAREST_CLAMP;
	texture.Reset(Graphics::TextureBuilder(patternPath, sampleMode, true, true, false).CreateTexture(r));
}

}
