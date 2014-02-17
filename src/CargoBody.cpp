<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "CargoBody.h"
#include "Game.h"
#include "Pi.h"
#include "Serializer.h"
#include "Sfx.h"
#include "Space.h"
#include "EnumStrings.h"
#include "collider/collider.h"
#include "scenegraph/SceneGraph.h"

void CargoBody::Save(Serializer::Writer &wr, Space *space)
{
	DynamicBody::Save(wr, space);
	wr.Int32(static_cast<int>(m_type));
	wr.Float(m_hitpoints);
}

void CargoBody::Load(Serializer::Reader &rd, Space *space)
{
	DynamicBody::Load(rd, space);
	m_type = static_cast<Equip::Type>(rd.Int32());
	Init();
	m_hitpoints = rd.Float();
}

void CargoBody::Init()
{
	m_hitpoints = 1.0f;
	SetLabel(Equip::types[m_type].name);
	SetMassDistributionFromModel();

<<<<<<< HEAD
	std::vector<Color4ub> colors;
	//metallic blue-orangeish color scheme
	colors.push_back(Color4ub(255, 198, 64));
	colors.push_back(Color4ub(0, 222, 255));
	colors.push_back(Color4ub(255, 255, 255));
=======
	std::vector<Color> colors;
	//metallic blue-orangeish color scheme
	colors.push_back(Color(255, 198, 64));
	colors.push_back(Color(0, 222, 255));
	colors.push_back(Color(255, 255, 255));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	GetModel()->SetColors(colors);

	Properties().Set("type", EnumStrings::GetString("EquipType", m_type));
}

CargoBody::CargoBody(Equip::Type t)
{
	m_type = t;
	SetModel("cargo");
	Init();
	SetMass(1.0);
}

bool CargoBody::OnDamage(Object *attacker, float kgDamage, const CollisionContact& contactData)
{
	m_hitpoints -= kgDamage*0.001f;
	if (m_hitpoints < 0) {
		Pi::game->GetSpace()->KillBody(this);
		Sfx::Add(this, Sfx::TYPE_EXPLOSION);
	}
	return true;
}

bool CargoBody::OnCollision(Object *b, Uint32 flags, double relVel)
{
	// ignore collision if its about to be scooped
	// XXX this is wrong. should only ignore if its actually going to be scooped. see Ship::OnCollision
	if (b->IsType(Object::SHIP)) {
		return true;
	}

	return DynamicBody::OnCollision(b, flags, relVel);
}

void CargoBody::Render(Graphics::Renderer *r, const Camera *camera, const vector3d &viewCoords, const matrix4x4d &viewTransform)
{
	GetModel()->SetLabel(Equip::types[m_type].name);
	RenderModel(r, camera, viewCoords, viewTransform);
}
