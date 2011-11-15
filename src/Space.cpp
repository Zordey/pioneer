#include "libs.h"
#include "Space.h"
#include "Body.h"
#include "Frame.h"
#include "Star.h"
#include "Planet.h"
#include <algorithm>
#include <functional>
#include "Pi.h"
#include "Player.h"
#include "StarSystem.h"
#include "SpaceStation.h"
#include "Serializer.h"
#include "collider/collider.h"
#include "Missile.h"
#include "HyperspaceCloud.h"
#include "render/Render.h"
#include "WorldView.h"
#include "SectorView.h"
#include "Lang.h"
#include "SpaceManager.h"

Space::Space()
{
	m_starSystem = 0;

	rootFrame = new Frame(0, Lang::SYSTEM);
	rootFrame->SetRadius(FLT_MAX);
}

Space::Space(const SystemPath &path)
{
	m_starSystem = StarSystem::GetCached(path);

	// XXX set radius in constructor
	rootFrame = new Frame(0, Lang::SYSTEM);
	rootFrame->SetRadius(FLT_MAX);

	GenBody(m_starSystem->rootBody, rootFrame);
	rootFrame->UpdateOrbitRails();
}

Space::Space(Serializer::Reader &rd)
{
	assert(0);
}

Space::~Space()
{
	UpdateBodies(); // make sure anything waiting to be removed gets removed before we go and kill everything else
	for (std::list<Body*>::iterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
		KillBody(*i);
	UpdateBodies();

	delete rootFrame;

	if (m_starSystem)
		m_starSystem->Release();
}

void Space::AddBody(Body *b)
{
	m_bodies.push_back(b);
}

void Space::RemoveBody(Body *b)
{
	m_removeBodies.push_back(b);
}

void Space::KillBody(Body* b)
{
	if (!b->IsDead()) {
		b->MarkDead();

		// player needs to stay alive so things like the death animation
		// (which uses a camera positioned relative to the player) can
		// continue to work. it will be cleaned up with the space is torn down
		// XXX this seems like the wrong way to do it. since its still "alive"
		// it still collides, moves, etc. better to just snapshot its position
		// elsewhere
		if (b != Pi::player)
			m_killBodies.push_back(b);
	}
}

// XXX this is only called by Missile::Explode. consider moving it there
void Space::RadiusDamage(Body *attacker, Frame *f, const vector3d &pos, double radius, double kgDamage)
{
	for (std::list<Body*>::iterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		if ((*i)->GetFrame() != f) continue;
		double dist = ((*i)->GetPosition() - pos).Length();
		if (dist < radius) {
			// linear damage decay with distance
			(*i)->OnDamage(attacker, kgDamage * (radius - dist) / radius);
			if ((*i)->IsType(Object::SHIP))
				Pi::luaOnShipHit->Queue(dynamic_cast<Ship*>(*i), attacker);
		}
	}
}

void Space::DoECM(const Frame *f, const vector3d &pos, int power_val)
{
	const float ECM_RADIUS = 4000.0f;
	for (std::list<Body*>::iterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		if ((*i)->GetFrame() != f) continue;
		if (!(*i)->IsType(Object::MISSILE)) continue;

		double dist = ((*i)->GetPosition() - pos).Length();
		if (dist < ECM_RADIUS) {
			// increasing chance of destroying it with proximity
			if (Pi::rng.Double() > (dist / ECM_RADIUS)) {
				static_cast<Missile*>(*i)->ECMAttack(power_val);
			}
		}
	}
}

// random point on a sphere, distributed uniformly by area
vector3d Space::GetRandomPosition(float min_dist, float max_dist)
{
	// see http://mathworld.wolfram.com/SpherePointPicking.html
	// or a Google search for further information
	const double dist = Pi::rng.Double(min_dist, max_dist);
	const double z = Pi::rng.Double_closed(-1.0, 1.0);
	const double theta = Pi::rng.Double(2.0*M_PI);
	const double r = sqrt(1.0 - z*z) * dist;
	return vector3d(r*cos(theta), r*sin(theta), z*dist);
}

vector3d Space::GetPositionAfterHyperspace(const SystemPath *source, const SystemPath *dest)
{
	Sector source_sec(source->sectorX,source->sectorY,source->sectorZ);
	Sector dest_sec(dest->sectorX,dest->sectorY,dest->sectorZ);
	Sector::System source_sys = source_sec.m_systems[source->systemIndex];
	Sector::System dest_sys = dest_sec.m_systems[dest->systemIndex];
	const vector3d sourcePos = vector3d(source_sys.p) + vector3d(source->sectorX, source->sectorY, source->sectorZ);
	const vector3d destPos = vector3d(dest_sys.p) + vector3d(dest->sectorX, dest->sectorY, dest->sectorZ);
	return (sourcePos - destPos).Normalized() * 11.0*AU + GetRandomPosition(5.0,20.0)*1000.0; // "hyperspace zone": 11 AU from primary
}

Body *Space::FindNearestTo(const Body *b, Object::Type t)
{
	Body *nearest = 0;
	double dist = FLT_MAX;
	for (std::list<Body*>::iterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		if ((*i)->IsDead()) continue;
		if ((*i)->IsType(t)) {
			double d = (*i)->GetPositionRelTo(b).Length();
			if (d < dist) {
				dist = d;
				nearest = *i;
			}
		}
	}
	return nearest;
}

Body *Space::FindBodyForPath(const SystemPath *path)
{
	// it is a bit dumb that currentSystem is not part of Space...
	SBody *body = m_starSystem->GetBodyByPath(path);

	if (!body) return 0;

	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		if ((*i)->GetSBody() == body) return *i;
	}
	return 0;
}




/*
void Serialize(Serializer::Writer &wr)
{
	Serializer::Writer wr2;
	Frame::Serialize(wr2, rootFrame);
	wr.WrSection("Frames", wr2.GetData());

	wr.Int32(m_bodies.size());
	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		//printf("Serializing %s\n", (*i)->GetLabel().c_str());
		(*i)->Serialize(wr);
	}
	wr.Int32(storedArrivalClouds.size());
	for (std::list<HyperspaceCloud*>::iterator i = storedArrivalClouds.begin();
			i != storedArrivalClouds.end(); ++i) {
		(*i)->Serialize(wr);
	}
	if (hyperspacingTo == 0) {
		wr.Byte(0);
	} else {
		wr.Byte(1);
		hyperspacingTo->Serialize(wr);
		wr.Float(hyperspaceAnim);
		wr.Double(hyperspaceDuration);
		wr.Double(hyperspaceEndTime);
	}
}
*/

/*
void Unserialize(Serializer::Reader &rd)
{
	Serializer::IndexSystemm_bodies(Pi::spaceManager->GetSpace()->GetStarSystem());
	
	Serializer::Reader rd2 = rd.RdSection("Frames");
	rootFrame = Frame::Unserialize(rd2, 0);
	
	// XXX not needed. done in Pi::Unserialize
	Serializer::IndexFrames();
	int num_m_bodies = rd.Int32();
	//printf("%d m_bodies to read\n", num_m_bodies);
	for (int i=0; i<num_m_bodies; i++) {
		Body *b = Body::Unserialize(rd);
		if (b) m_bodies.push_back(b);
	}
	num_m_bodies = rd.Int32();
	for (int i=0; i<num_m_bodies; i++) {
		Body *b = Body::Unserialize(rd);
		if (b) storedArrivalClouds.push_back(static_cast<HyperspaceCloud*>(b));
	}

	hyperspaceAnim = 0;
	if (rd.Byte()) {
		hyperspacingTo = new SystemPath(SystemPath::Unserialize(rd));
		hyperspaceAnim = rd.Float();
		hyperspaceDuration = rd.Double();
		hyperspaceEndTime = rd.Double();
	}
	// m_bodies with references to others must fix these up
	Serializer::Indexm_bodies();
	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i) {
		(*i)->PostLoadFixup();
	}
	Frame::PostUnserializeFixup(rootFrame);
}
*/

static Frame *find_frame_with_sbody(Frame *f, const SBody *b)
{
	if (f->m_sbody == b) return f;
	else {
		for (std::list<Frame*>::iterator i = f->m_children.begin();
			i != f->m_children.end(); ++i) {
			
			Frame *found = find_frame_with_sbody(*i, b);
			if (found) return found;
		}
	}
	return 0;
}

Frame *Space::GetFrameWithSBody(const SBody *b)
{
	return find_frame_with_sbody(rootFrame, b);
}

static void SetFrameOrientationFromSBodyAxialTilt(Frame *f, const SBody *sbody)
{
	matrix4x4d rot = matrix4x4d::RotateXMatrix(sbody->axialTilt.ToDouble());
	f->SetRotationOnly(rot);
}

static Frame *MakeFrameFor(SBody *sbody, Body *b, Frame *f)
{
	Frame *orbFrame, *rotFrame;
	double frameRadius;

	if (!sbody->parent) {
		if (b) b->SetFrame(f);
		f->m_sbody = sbody;
		f->m_astroBody = b;
		return f;
	}

	if (sbody->type == SBody::TYPE_GRAVPOINT) {
		orbFrame = new Frame(f, sbody->name.c_str());
		orbFrame->m_sbody = sbody;
		orbFrame->m_astroBody = b;
		orbFrame->SetRadius(sbody->GetMaxChildOrbitalDistance()*1.1);
		return orbFrame;
	}

	SBody::BodySuperType supertype = sbody->GetSuperType();

	if ((supertype == SBody::SUPERTYPE_GAS_GIANT) ||
	    (supertype == SBody::SUPERTYPE_ROCKY_PLANET)) {
		// for planets we want an non-rotating frame for a few radii
		// and a rotating frame in the same position but with maybe 1.05*radius,
		// which actually contains the object.
		frameRadius = std::max(4.0*sbody->GetRadius(), sbody->GetMaxChildOrbitalDistance()*1.05);
		orbFrame = new Frame(f, sbody->name.c_str());
		orbFrame->m_sbody = sbody;
		orbFrame->SetRadius(frameRadius);
		//printf("\t\t\t%s has frame size %.0fkm, body radius %.0fkm\n", sbody->name.c_str(),
		//	(frameRadius ? frameRadius : 10*sbody->GetRadius())*0.001f,
		//	sbody->GetRadius()*0.001f);
	
		assert(sbody->rotationPeriod != 0);
		rotFrame = new Frame(orbFrame, sbody->name.c_str());
		// rotating frame has size of GeoSphere terrain bounding sphere
		rotFrame->SetRadius(b->GetBoundingRadius());
		rotFrame->SetAngVelocity(vector3d(0,2*M_PI/sbody->GetRotationPeriod(),0));
		rotFrame->m_astroBody = b;
		SetFrameOrientationFromSBodyAxialTilt(rotFrame, sbody);
		b->SetFrame(rotFrame);
		return orbFrame;
	}
	else if (supertype == SBody::SUPERTYPE_STAR) {
		// stars want a single small non-rotating frame
		orbFrame = new Frame(f, sbody->name.c_str());
		orbFrame->m_sbody = sbody;
		orbFrame->m_astroBody = b;
		orbFrame->SetRadius(sbody->GetMaxChildOrbitalDistance()*1.1);
		b->SetFrame(orbFrame);
		return orbFrame;
	}
	else if (sbody->type == SBody::TYPE_STARPORT_ORBITAL) {
		// space stations want non-rotating frame to some distance
		// and a much closer rotating frame
		frameRadius = 1000000.0; // XXX NFI!
		orbFrame = new Frame(f, sbody->name.c_str());
		orbFrame->m_sbody = sbody;
//		orbFrame->SetRadius(10*sbody->GetRadius());
		orbFrame->SetRadius(frameRadius);
	
		assert(sbody->rotationPeriod != 0);
		rotFrame = new Frame(orbFrame, sbody->name.c_str());
		rotFrame->SetRadius(1000.0);
//		rotFrame->SetRadius(1.1*sbody->GetRadius());		// enough for collisions?
		rotFrame->SetAngVelocity(vector3d(0.0,double(static_cast<SpaceStation*>(b)->GetDesiredAngVel()),0.0));
		rotFrame->m_astroBody = b;		// hope this doesn't break anything
		b->SetFrame(rotFrame);
		return orbFrame;
	} else if (sbody->type == SBody::TYPE_STARPORT_SURFACE) {
		// just put body into rotating frame of planet, not in its own frame
		// (because collisions only happen between objects in same frame,
		// and we want collisions on starport and on planet itself)
		Frame *frame = *f->m_children.begin();
		b->SetFrame(frame);
		assert(frame->m_astroBody->IsType(Object::PLANET));
		Planet *planet = static_cast<Planet*>(frame->m_astroBody);

		/* position on planet surface */
		double height;
		int tries;
		matrix4x4d rot;
		vector3d pos;
		// first try suggested position
		rot = sbody->orbit.rotMatrix;
		pos = rot * vector3d(0,1,0);
		if (planet->GetTerrainHeight(pos) - planet->GetSBody()->GetRadius() <= 0.0) {
			MTRand r(sbody->seed);
			// position is under water. try some random ones
			for (tries=0; tries<100; tries++) {
				// used for orientation on planet surface
				double r2 = r.Double(); 	// function parameter evaluation order is implementation-dependent
				double r1 = r.Double();		// can't put two rands in the same expression
				rot = matrix4x4d::RotateZMatrix(2*M_PI*r1)
					* matrix4x4d::RotateYMatrix(2*M_PI*r2);
				pos = rot * vector3d(0,1,0);
				height = planet->GetTerrainHeight(pos) - planet->GetSBody()->GetRadius();
				// don't want to be under water
				if (height > 0.0) break;
			}
		}
		b->SetPosition(pos * planet->GetTerrainHeight(pos));
		b->SetRotMatrix(rot);
		return frame;
	} else {
		assert(0);
	}
	return NULL;
}

void Space::GenBody(SBody *sbody, Frame *f)
{
	Body *b = 0;

	if (sbody->type != SBody::TYPE_GRAVPOINT) {
		if (sbody->GetSuperType() == SBody::SUPERTYPE_STAR) {
			Star *star = new Star(sbody);
			b = star;
		} else if ((sbody->type == SBody::TYPE_STARPORT_ORBITAL) ||
		           (sbody->type == SBody::TYPE_STARPORT_SURFACE)) {
			SpaceStation *ss = new SpaceStation(sbody);
			b = ss;
		} else {
			Planet *planet = new Planet(sbody);
			b = planet;
		}
		b->SetLabel(sbody->name.c_str());
		b->SetPosition(vector3d(0,0,0));
		AddBody(b);
	}
	f = MakeFrameFor(sbody, b, f);

	for (std::vector<SBody*>::iterator i = sbody->children.begin(); i != sbody->children.end(); ++i) {
		GenBody(*i, f);
	}
}

static bool OnCollision(Object *o1, Object *o2, CollisionContact *c, double relativeVel)
{
	Body *pb1 = static_cast<Body*>(o1);
	Body *pb2 = static_cast<Body*>(o2);
	/* Not always a Body (could be CityOnPlanet, which is a nasty exception I should eradicate) */
	if (o1->IsType(Object::BODY)) {
		if (pb1 && !pb1->OnCollision(o2, c->geomFlag, relativeVel)) return false;
	}
	if (o2->IsType(Object::BODY)) {
		if (pb2 && !pb2->OnCollision(o1, c->geomFlag, relativeVel)) return false;
	}
	return true;
}

static void hitCallback(CollisionContact *c)
{
	//printf("OUCH! %x (depth %f)\n", SDL_GetTicks(), c->depth);

	Object *po1 = static_cast<Object*>(c->userData1);
	Object *po2 = static_cast<Object*>(c->userData2);

	const bool po1_isDynBody = po1->IsType(Object::DYNAMICBODY);
	const bool po2_isDynBody = po2->IsType(Object::DYNAMICBODY);
	// collision response
	assert(po1_isDynBody || po2_isDynBody);

	if (po1_isDynBody && po2_isDynBody) {
		DynamicBody *b1 = static_cast<DynamicBody*>(po1);
		DynamicBody *b2 = static_cast<DynamicBody*>(po2);
		const vector3d linVel1 = b1->GetVelocity();
		const vector3d linVel2 = b2->GetVelocity();
		const vector3d angVel1 = b1->GetAngVelocity();
		const vector3d angVel2 = b2->GetAngVelocity();
		
		const double coeff_rest = 0.5;
		// step back
//		mover->UndoTimestep();

		const double invMass1 = 1.0 / b1->GetMass();
		const double invMass2 = 1.0 / b2->GetMass();
		const vector3d hitPos1 = c->pos - b1->GetPosition();
		const vector3d hitPos2 = c->pos - b2->GetPosition();
		const vector3d hitVel1 = linVel1 + angVel1.Cross(hitPos1);
		const vector3d hitVel2 = linVel2 + angVel2.Cross(hitPos2);
		const double relVel = (hitVel1 - hitVel2).Dot(c->normal);
		// moving away so no collision
		if (relVel > 0) return;
		if (!OnCollision(po1, po2, c, -relVel)) return;
		const double invAngInert1 = 1.0 / b1->GetAngularInertia();
		const double invAngInert2 = 1.0 / b2->GetAngularInertia();
		const double numerator = -(1.0 + coeff_rest) * relVel;
		const double term1 = invMass1;
		const double term2 = invMass2;
		const double term3 = c->normal.Dot((hitPos1.Cross(c->normal)*invAngInert1).Cross(hitPos1));
		const double term4 = c->normal.Dot((hitPos2.Cross(c->normal)*invAngInert2).Cross(hitPos2));

		const double j = numerator / (term1 + term2 + term3 + term4);
		const vector3d force = j * c->normal;
					
		b1->SetVelocity(linVel1 + force*invMass1);
		b1->SetAngVelocity(angVel1 + hitPos1.Cross(force)*invAngInert1);
		b2->SetVelocity(linVel2 - force*invMass2);
		b2->SetAngVelocity(angVel2 - hitPos2.Cross(force)*invAngInert2);
	} else {
		// one body is static
		vector3d hitNormal;
		DynamicBody *mover;

		if (po1_isDynBody) {
			mover = static_cast<DynamicBody*>(po1);
			hitNormal = c->normal;
		} else {
			mover = static_cast<DynamicBody*>(po2);
			hitNormal = -c->normal;
		}

		const double coeff_rest = 0.5;
		const vector3d linVel1 = mover->GetVelocity();
		const vector3d angVel1 = mover->GetAngVelocity();
		
		// step back
//		mover->UndoTimestep();

		const double invMass1 = 1.0 / mover->GetMass();
		const vector3d hitPos1 = c->pos - mover->GetPosition();
		const vector3d hitVel1 = linVel1 + angVel1.Cross(hitPos1);
		const double relVel = hitVel1.Dot(c->normal);
		// moving away so no collision
		if (relVel > 0 && !c->geomFlag) return;
		if (!OnCollision(po1, po2, c, -relVel)) return;
		const double invAngInert = 1.0 / mover->GetAngularInertia();
		const double numerator = -(1.0 + coeff_rest) * relVel;
		const double term1 = invMass1;
		const double term3 = c->normal.Dot((hitPos1.Cross(c->normal)*invAngInert).Cross(hitPos1));

		const double j = numerator / (term1 + term3);
		const vector3d force = j * c->normal;
					
		mover->SetVelocity(linVel1 + force*invMass1);
		mover->SetAngVelocity(angVel1 + hitPos1.Cross(force)*invAngInert);
	}
}

void Space::CollideFrame(Frame *f)
{
	if (f->m_astroBody && (f->m_astroBody->IsType(Object::TERRAINBODY))) {
		// this is pretty retarded
		for (BodyIterator i = m_bodies.begin(); i!=m_bodies.end(); ++i) {
			if ((*i)->GetFrame() != f) continue;
			if (!(*i)->IsType(Object::DYNAMICBODY)) continue;
			DynamicBody *dynBody = static_cast<DynamicBody*>(*i);

			Aabb aabb;
			dynBody->GetAabb(aabb);
			const matrix4x4d &trans = dynBody->GetGeom()->GetTransform();

			const vector3d aabbCorners[8] = {
				vector3d(aabb.min.x, aabb.min.y, aabb.min.z),
				vector3d(aabb.min.x, aabb.min.y, aabb.max.z),
				vector3d(aabb.min.x, aabb.max.y, aabb.min.z),
				vector3d(aabb.min.x, aabb.max.y, aabb.max.z),
				vector3d(aabb.max.x, aabb.min.y, aabb.min.z),
				vector3d(aabb.max.x, aabb.min.y, aabb.max.z),
				vector3d(aabb.max.x, aabb.max.y, aabb.min.z),
				vector3d(aabb.max.x, aabb.max.y, aabb.max.z)
			};

			CollisionContact c;

			for (int j=0; j<8; j++) {
				const vector3d &s = aabbCorners[j];
				vector3d pos = trans * s;
				double terrain_height = static_cast<Planet*>(f->m_astroBody)->GetTerrainHeight(pos.Normalized());
				double altitude = pos.Length();
				double hitDepth = terrain_height - altitude;
				if (altitude < terrain_height) {
					c.pos = pos;
					c.normal = pos.Normalized();
					c.depth = hitDepth;
					c.userData1 = static_cast<void*>(dynBody);
					c.userData2 = static_cast<void*>(f->m_astroBody);
					hitCallback(&c);
				}
			}
		}
	}
	f->GetCollisionSpace()->Collide(&hitCallback);
	for (std::list<Frame*>::iterator i = f->m_children.begin(); i != f->m_children.end(); ++i) {
		CollideFrame(*i);
	}
}


void Space::TimeStep(float step)
{
	// XXX does not need to be done this often
	Space::CollideFrame(rootFrame);

	// update frames of reference
	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
		(*i)->UpdateFrame();

	// AI acts here, then move all bodies and frames
	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
		(*i)->StaticUpdate(step);

	rootFrame->UpdateOrbitRails();

	for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
		(*i)->TimeStepUpdate(step);
	
	// XXX don't emit events in hyperspace. this is mostly to maintain the
	// status quo. in particular without this onEnterSystem will fire in the
	// frame immediately before the player leaves hyperspace and the system is
	// invalid when Lua goes and queries for it. we need to consider whether
	// there's anything useful that can be done with events in hyperspace
	if (m_starSystem) {
		Pi::luaOnEnterSystem->Emit();
		Pi::luaOnLeaveSystem->Emit();
		Pi::luaOnFrameChanged->Emit();
		Pi::luaOnShipHit->Emit();
		Pi::luaOnShipCollided->Emit();
		Pi::luaOnShipDestroyed->Emit();
		Pi::luaOnShipDocked->Emit();
		Pi::luaOnShipAlertChanged->Emit();
		Pi::luaOnShipUndocked->Emit();
		Pi::luaOnShipLanded->Emit();
		Pi::luaOnShipTakeOff->Emit();
		Pi::luaOnJettison->Emit();
		Pi::luaOnAICompleted->Emit();
		Pi::luaOnCreateBB->Emit();
		Pi::luaOnUpdateBB->Emit();
		Pi::luaOnShipFlavourChanged->Emit();
		Pi::luaOnShipEquipmentChanged->Emit();

		Pi::luaTimer->Tick();
	}

	UpdateBodies();
}

void Space::UpdateBodies()
{
	for (BodyIterator b = m_removeBodies.begin(); b != m_removeBodies.end(); ++b) {
		(*b)->SetFrame(0);
		for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
			(*i)->NotifyRemoved(*b);
		m_bodies.remove(*b);
	}
	m_removeBodies.clear();

	for (BodyIterator b = m_killBodies.begin(); b != m_killBodies.end(); ++b) {
		for (BodyIterator i = m_bodies.begin(); i != m_bodies.end(); ++i)
			(*i)->NotifyRemoved(*b);
		m_bodies.remove(*b);
		delete *b;
	}
    m_killBodies.clear();
}
