// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "Body.h"
#include "Frame.h"
#include "Star.h"
#include "Planet.h"
#include "CargoBody.h"
#include "SpaceStation.h"
#include "Ship.h"
#include "Player.h"
#include "Projectile.h"
#include "Missile.h"
#include "HyperspaceCloud.h"
#include "Pi.h"
#include "Space.h"
#include "Game.h"
#include "LuaEvent.h"

matrix3x3d Body::g_identityMatrix = matrix3x3d::Identity();

Body::Body()
{
	m_frame = 0;
	m_flags = 0;
//	m_hasDoubleFrame = false;
	m_dead = false;
}

Body::~Body()
{
}

void Body::Save(Serializer::Writer &wr, Space *space)
{
	wr.Int32(space->GetIndexForFrame(m_frame));
	wr.String(m_label);
	wr.Bool(m_dead);
//	wr.Bool(m_hasDoubleFrame);
}

void Body::Load(Serializer::Reader &rd, Space *space)
{
	m_frame = space->GetFrameByIndex(rd.Int32());
	m_label = rd.String();
	m_dead = rd.Bool();
//	m_hasDoubleFrame = rd.Bool();
}

void Body::Serialize(Serializer::Writer &_wr, Space *space)
{
	Serializer::Writer wr;
	wr.Int32(int(GetType()));
	switch (GetType()) {
		case Object::STAR:
		case Object::PLANET:
		case Object::SPACESTATION:
		case Object::SHIP:
		case Object::PLAYER:
		case Object::MISSILE:
		case Object::CARGOBODY:
		case Object::PROJECTILE:
		case Object::HYPERSPACECLOUD:
			Save(wr, space);
			break;
		default:
			assert(0);
	}
	wr.Vector3d(GetPosition());
	const matrix3x3d &orient = GetOrient();
	for (int i=0; i<9; i++) wr.Double(orient[i]);
	_wr.WrSection("Body", wr.GetData());
}

Body *Body::Unserialize(Serializer::Reader &_rd, Space *space)
{
	Serializer::Reader rd = _rd.RdSection("Body");
	Body *b = 0;
	Object::Type type = Object::Type(rd.Int32());
	switch (type) {
		case Object::STAR:
			b = new Star(); break;
		case Object::PLANET:
			b = new Planet();
			break;
		case Object::SPACESTATION:
			b = new SpaceStation(); break;
		case Object::SHIP:
			b = new Ship(); break;
		case Object::PLAYER:
			b = new Player(); break;
		case Object::MISSILE:
			b = new Missile(); break;
		case Object::PROJECTILE:
			b = new Projectile(); break;
		case Object::CARGOBODY:
			b = new CargoBody(); break;
		case Object::HYPERSPACECLOUD:
			b = new HyperspaceCloud(); break;
		default:
			assert(0);
	}
	b->Load(rd, space);
	// must SetFrame() correctly so ModelBodies can add geom to space
	Frame *f = b->m_frame;
	b->m_frame = 0;
	b->SetFrame(f);
	//
	b->SetPosition(rd.Vector3d());
	matrix3x3d m;
	for (int i=0; i<9; i++) m[i] = rd.Double();
	b->SetOrient(m);
	return b;
}

vector3d Body::GetPositionRelTo(const Frame *relTo) const
{
	vector3d fpos = m_frame->GetPositionRelTo(relTo);
	matrix3x3d forient = m_frame->GetOrientRelTo(relTo);
	return forient * GetPosition() + fpos;
}

vector3d Body::GetInterpPositionRelTo(const Frame *relTo) const
{
	vector3d fpos = m_frame->GetInterpPositionRelTo(relTo);
	matrix3x3d forient = m_frame->GetInterpOrientRelTo(relTo);
	return forient * GetInterpPosition() + fpos;
}

vector3d Body::GetPositionRelTo(const Body *relTo) const
{
	return GetPositionRelTo(relTo->m_frame) - relTo->GetPosition();
}

vector3d Body::GetInterpPositionRelTo(const Body *relTo) const
{
	return GetInterpPositionRelTo(relTo->m_frame) - relTo->GetInterpPosition();
}

matrix3x3d Body::GetInterpOrientRelTo(const Frame *relTo) const
{
	matrix3x3d forient = m_frame->GetInterpOrientRelTo(relTo);
	return forient * GetInterpOrient();
}

vector3d Body::GetVelocityRelTo(const Frame *relTo) const
{
	matrix3x3d forient = m_frame->GetOrientRelTo(relTo);
	vector3d vel = GetVelocity();
	if (m_frame != relTo) vel -= m_frame->GetStasisVelocity(GetPosition());
	return forient * vel + m_frame->GetVelocityRelTo(relTo);
}

vector3d Body::GetVelocityRelTo(const Body *relTo) const
{
	return GetVelocityRelTo(relTo->m_frame) - relTo->GetVelocity();
}

void Body::OrientOnSurface(double radius, double latitude, double longitude)
{
	vector3d up = vector3d(cos(latitude)*cos(longitude), sin(latitude)*cos(longitude), sin(longitude));
	SetPosition(radius * up);

	vector3d forward = vector3d(0,0,1);
	vector3d other = up.Cross(forward).Normalized();
	forward = other.Cross(up);
	SetOrient(matrix3x3d::BuildFromVectors(other, up, forward));
}

void Body::SwitchToFrame(Frame *newFrame)
{
	SetVelocity(GetVelocityRelTo(newFrame));		// do this first because it uses position
	vector3d fpos = m_frame->GetPositionRelTo(newFrame);
	matrix3x3d forient = m_frame->GetOrientRelTo(newFrame);
	SetPosition(forient * GetPosition() + fpos);
	SetOrient(forient * GetOrient());
	SetFrame(newFrame);

	LuaEvent::Queue("onFrameChanged", this);
}

void Body::UpdateFrame()
{
	if (!(m_flags & FLAG_CAN_MOVE_FRAME)) return;
	if (m_frame->IsRotFrame()) return;			// don't move from rotating frames

	// falling out of frames
	if (m_frame->GetRadius() < GetPosition().Length()) {
		Frame *newFrame = GetFrame()->GetParent();
		if (newFrame) { 						// don't fall out of root frame
			SwitchToFrame(newFrame);
			printf("%s leaves frame %s\n", GetLabel().c_str(), GetFrame()->GetLabel().c_str());
			return;
		}
	}

	// entering into frames
	std::list<Frame*> &children = m_frame->GetChildren();
	for (std::list<Frame*>::iterator j = children.begin(); j != children.end(); ++j)
	{
		if ((*j)->IsRotFrame()) continue;			// don't move into rotating frames
		vector3d pos = GetPositionRelTo(*j);
		if (pos.Length() >= (*j)->GetRadius()) continue;
		SwitchToFrame(*j);
		printf("%s enters frame %s\n", GetLabel().c_str(), (*j)->GetLabel().c_str());
		break;
	}
}

vector3d Body::GetTargetIndicatorPosition(const Frame *relTo) const
{
	return GetInterpPositionRelTo(relTo);
}
