<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef SCENEGRAPH_MODELSKIN_H
#define SCENEGRAPH_MODELSKIN_H

#include "Color.h"
#include "Serializer.h"
#include "Random.h"
#include "LuaWrappable.h"
#include <string>

namespace SceneGraph {

class Model;

class ModelSkin : public LuaWrappable {
public:
	ModelSkin();

	void Apply(Model *model) const;

<<<<<<< HEAD
	void SetPattern(unsigned int index);

	void SetColors(const std::vector<Color4ub> &colors);
	void SetPrimaryColor(const Color4ub &color);
	void SetSecondaryColor(const Color4ub &color);
	void SetTrimColor(const Color4ub &color);
=======
	void SetColors(const std::vector<Color> &colors);
	void SetPrimaryColor(const Color &color);
	void SetSecondaryColor(const Color &color);
	void SetTrimColor(const Color &color);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	void SetRandomColors(Random &rand);

	void SetDecal(const std::string &name, unsigned int index = 0);
	void ClearDecal(unsigned int index = 0);
	void ClearDecals();

	void SetLabel(const std::string &label);

	void Load(Serializer::Reader &rd);
	void Save(Serializer::Writer &wr) const;

private:
	static const unsigned int MAX_DECAL_MATERIALS = 4;

<<<<<<< HEAD
	unsigned int m_patternIndex;
	std::vector<Color4ub> m_colors;
=======
	std::vector<Color> m_colors;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	std::string m_decals[MAX_DECAL_MATERIALS];
	std::string m_label;
};

}

#endif
