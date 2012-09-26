#ifndef _NEWMODEL_PATTERN_H
#define _NEWMODEL_PATTERN_H
/*
 * Patterns are a color look-up trick to have customizable
 * colours on models. Patterns are grayscale textures
 * and accompanied by a tiny runtime generated gradient texture
 * with 2-3 colours
 */
#include "libs.h"
#include "SmartPtr.h"

namespace Graphics {
	class Texture;
	class Renderer;
}

namespace Newmodel {

struct Pattern {
	bool smoothColor;
	bool smoothPattern;
	RefCountedPtr<Graphics::Texture> texture;
	std::string name;

	Pattern();
	Pattern(const std::string &name, const std::string& path, Graphics::Renderer* r);
};

typedef std::vector<Pattern> PatternContainer;

}
#endif
