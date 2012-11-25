// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Frame.h"
#include "Body.h"
#include "Space.h"
#include "collider/collider.h"
#include "Sfx.h"
#include "galaxy/StarSystem.h"
#include "Pi.h"
#include "Game.h"

Frame::Frame()
{
	Init(NULL, "", 0);
}

Frame::Frame(Frame *parent, const char *label)
{
	Init(parent, label, 0);
}

Frame::Frame(Frame *parent, const char *label, unsigned int flags)
{
	Init(parent, label, flags);
}

void Frame::Serialize(Serializer::Writer &wr, Frame *f, Space *space)
{
	wr.Int32(f->m_flags);
	wr.Double(f->m_radius);
	wr.String(f->m_label);
	wr.Vector3d(f->m_pos);
	for (int i=0; i<9; i++) wr.Double(f->m_orient[i]);
	wr.Double(f->m_angSpeed);
	wr.Int32(space->GetIndexForSystemBody(f->m_sbody));
	wr.Int32(space->GetIndexForBody(f->m_astroBody));
	wr.Int32(f->m_children.size());
	for (Frame *c = f->GetFirstChild(); c; c = f->GetNextChild()) {
		Serialize(wr, c, space);
	}
	Sfx::Serialize(wr, f);
}

Frame *Frame::Unserialize(Serializer::Reader &rd, Space *space, Frame *parent)
{
	Frame *f = new Frame();
	f->m_parent = parent;
	f->m_flags = rd.Int32();
	f->m_radius = rd.Double();
	f->m_label = rd.String();
	f->m_pos = rd.Vector3d();
	for (int i=0; i<9; i++) f->m_orient[i] = rd.Double();
	f->m_angSpeed = rd.Double();
	f->m_sbody = space->GetSystemBodyByIndex(rd.Int32());
	f->m_astroBodyIndex = rd.Int32();
	f->m_vel = vector3d(0.0);
	for (int i=rd.Int32(); i>0; --i) {
		f->m_children.push_back(Unserialize(rd, space, f));
	}
	Sfx::Unserialize(rd, f);

	f->ClearMovement();
	return f;
}

void Frame::PostUnserializeFixup(Frame *f, Space *space)
{
	f->UpdateRootRelativeVars();
	f->m_astroBody = space->GetBodyByIndex(f->m_astroBodyIndex);
	for (Frame *c = f->GetFirstChild(); c; c = f->GetNextChild()) {
		PostUnserializeFixup(c, space);
	}
}

void Frame::Init(Frame *parent, const char *label, unsigned int flags)
{
	m_sfx = 0;
	m_sbody = 0;
	m_astroBody = 0;
	m_parent = parent;
	m_flags = flags;
	m_radius = 0;
	m_pos = vector3d(0.0);
	m_vel = vector3d(0.0);
	m_angSpeed = 0.0;
	m_orient = matrix3x3d::Identity();
	ClearMovement();
	m_collisionSpace = new CollisionSpace();
	if (m_parent) m_parent->AddChild(this);
	if (label) m_label = label;
}

Frame::~Frame()
{
	if (m_sfx) delete [] m_sfx;
	delete m_collisionSpace;
	if (m_parent) m_parent->RemoveChild(this);
}

void Frame::AddGeom(Geom *g) { m_collisionSpace->AddGeom(g); }
void Frame::RemoveGeom(Geom *g) { m_collisionSpace->RemoveGeom(g); }
void Frame::AddStaticGeom(Geom *g) { m_collisionSpace->AddStaticGeom(g); }
void Frame::RemoveStaticGeom(Geom *g) { m_collisionSpace->RemoveStaticGeom(g); }
void Frame::SetPlanetGeom(double radius, Body *obj)
{
	m_collisionSpace->SetSphere(vector3d(0,0,0), radius, static_cast<void*>(obj));
}

// may need one-frame exemptions to reduce camera jitter
//eg:
//	vector3d diff;
//	if (this == relTo) return vector3d(0,0,0);
//	if (relTo->GetParent() == this) return -relTo->m_pos * m_orient;	// relative to child
//	if (GetParent() == relTo) return m_pos;			// relative to parent
//	else diff = m_rootPos - relTo->m_rootPos;

// doesn't consider stasis velocity
vector3d Frame::GetVelocityRelTo(const Frame *relTo) const
{
	if (this == relTo) return vector3d(0,0,0);		// these lines are not strictly necessary
	vector3d diff = m_rootVel - relTo->m_rootVel;
	if (relTo->IsRotFrame()) return diff * relTo->m_rootOrient;
	else return diff;
}

vector3d Frame::GetPositionRelTo(const Frame *relTo) const
{
	if (this == relTo) return vector3d(0,0,0);
	if (relTo->GetParent() == this) 					// relative to child
		return -relTo->m_pos * relTo->m_orient;
	if (GetParent() == relTo) return m_pos;				// relative to parent

	vector3d diff = m_rootPos - relTo->m_rootPos;
	if (relTo->IsRotFrame()) return diff * relTo->m_rootOrient;
	else return diff;
}

vector3d Frame::GetInterpPositionRelTo(const Frame *relTo) const
{
	if (this == relTo) return vector3d(0,0,0);
	if (relTo->GetParent() == this) 							// relative to child
		return -relTo->m_interpPos * relTo->m_interpOrient;
	if (GetParent() == relTo) return m_interpPos;				// relative to parent

	vector3d diff = m_rootInterpPos - relTo->m_rootInterpPos;
	if (relTo->IsRotFrame()) return diff * relTo->m_rootOrient;
	else return diff;
}

matrix3x3d Frame::GetOrientRelTo(const Frame *relTo) const
{
	if (this == relTo) return matrix3x3d::Identity();
	return relTo->m_rootOrient.Transpose() * m_rootOrient;
}

matrix3x3d Frame::GetInterpOrientRelTo(const Frame *relTo) const
{
	if (this == relTo) return matrix3x3d::Identity();
	return relTo->m_rootInterpOrient.Transpose() * m_rootInterpOrient;
/*	if (IsRotFrame()) {
		if (relTo->IsRotFrame()) return m_interpOrient * relTo->m_interpOrient.Transpose();
		else return m_interpOrient;
	}
	if (relTo->IsRotFrame()) return relTo->m_interpOrient.Transpose();
	else return matrix3x3d::Identity();
*/
}

void Frame::UpdateInterpTransform(double alpha)
{
	m_interpPos = alpha*m_pos + (1.0-alpha)*m_oldPos;
	m_interpOrient = m_oldOrient;

	double len = m_oldAngDisplacement * double(alpha);
	if (!is_zero_general(len)) {
		vector3d axis = vector3d(0,1,0);
		matrix3x3d rot = matrix3x3d::BuildRotate(len, axis);
		m_interpOrient = rot * m_interpOrient;
	}
	if (!m_parent) ClearMovement();
	else {
		m_rootInterpPos = m_parent->m_rootInterpOrient * m_interpPos
			+ m_parent->m_rootInterpPos;
		m_rootInterpOrient = m_parent->m_rootInterpOrient * m_interpOrient;
	}

	for (Frame *c = GetFirstChild(); c; c = GetNextChild()) {
		c->UpdateInterpTransform(alpha);
	}
}

void Frame::GetFrameTransform(const Frame *fFrom, const Frame *fTo, matrix4x4d &m)
{
	matrix3x3d forient = fFrom->GetOrientRelTo(fTo);
	vector3d fpos = fFrom->GetPositionRelTo(fTo);
	m = forient; m.SetTranslate(fpos);
}

void Frame::GetFrameRenderTransform(const Frame *fFrom, const Frame *fTo, matrix4x4d &m)
{
	matrix3x3d forient = fFrom->GetInterpOrientRelTo(fTo);
	vector3d fpos = fFrom->GetInterpPositionRelTo(fTo);
	m = forient; m.SetTranslate(fpos);
}

void Frame::ClearMovement()
{
	UpdateRootRelativeVars();
	m_rootInterpPos = m_rootPos;
	m_rootInterpOrient = m_rootOrient;
	m_oldPos = m_interpPos = m_pos;
	m_oldOrient = m_interpOrient = m_orient;
	m_oldAngDisplacement = 0.0;
}

void Frame::UpdateOrbitRails(double time, double timestep)
{
	m_oldPos = m_pos;
	m_oldOrient = m_orient;
	m_oldAngDisplacement = m_angSpeed * timestep;

	// update frame position and velocity
	if (m_parent && m_sbody && !IsRotFrame()) {
		m_pos = m_sbody->orbit.OrbitalPosAtTime(time);
		vector3d pos2 = m_sbody->orbit.OrbitalPosAtTime(time+timestep);
		m_vel = (pos2 - m_pos) / timestep;
	}
	// temporary test thing
	else m_pos = m_pos + m_vel * timestep;
	
	// update frame rotation
	double ang = m_angSpeed * timestep;		// hmm. cumulative inaccuracy? worse!
	if (!is_zero_exact(m_angSpeed)) {		// calling this with very low numbers is still important
		vector3d axis = vector3d(0,1,0);
		matrix3x3d rot = matrix3x3d::BuildRotate(ang, axis);
		m_orient = m_orient * rot;		// angvel always +y
	}
	UpdateRootRelativeVars();			// update root-relative pos/vel/orient

	for (Frame *c = GetFirstChild(); c; c = GetNextChild()) {
		c->UpdateOrbitRails(time, timestep);
	}
}

void Frame::UpdateRootRelativeVars()
{
	// update pos & vel relative to parent frame
	if (!m_parent) {
		m_rootPos = m_rootVel = vector3d(0,0,0);
		m_rootOrient = matrix3x3d::Identity();
	}
	else {
		m_rootPos = m_parent->m_rootOrient * m_pos + m_parent->m_rootPos;
		m_rootVel = m_parent->m_rootOrient * m_vel + m_parent->m_rootVel;
		m_rootOrient = m_parent->m_rootOrient * m_orient;
	}
}