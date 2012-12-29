// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Sfx.h"
#include "Frame.h"
#include "galaxy/StarSystem.h"
#include "libs.h"
#include "Pi.h"
#include "Pi.h"
#include "Space.h"
#include "graphics/Drawables.h"
#include "graphics/Graphics.h"
#include "graphics/Material.h"
#include "graphics/Renderer.h"
#include "graphics/TextureBuilder.h"

using namespace Graphics;

#define MAX_SFX_PER_FRAME 1024
Graphics::Drawables::Sphere3D *Sfx::shieldEffect = 0;
Graphics::Drawables::Sphere3D *Sfx::explosionEffect = 0;
Graphics::Material *Sfx::damageParticle = 0;
Graphics::Material *Sfx::ecmParticle = 0;

Sfx::Sfx()
{
	m_type = TYPE_NONE;
}

void Sfx::Save(Serializer::Writer &wr)
{
	wr.Vector3d(m_pos);
	wr.Vector3d(m_vel);
	wr.Float(m_age);
	wr.Int32(m_type);
}

void Sfx::Load(Serializer::Reader &rd)
{
	m_pos = rd.Vector3d();
	m_vel = rd.Vector3d();
	m_age = rd.Float();
	m_type = static_cast<Sfx::TYPE>(rd.Int32());
}

void Sfx::Serialize(Serializer::Writer &wr, const Frame *f)
{
	// how many sfx turds are active in frame?
	int numActive = 0;
	if (f->m_sfx) {
		for (int i=0; i<MAX_SFX_PER_FRAME; i++) {
			if (f->m_sfx[i].m_type != TYPE_NONE) numActive++;
		}
	}
	wr.Int32(numActive);

	if (numActive) for (int i=0; i<MAX_SFX_PER_FRAME; i++) {
		if (f->m_sfx[i].m_type != TYPE_NONE) {
			f->m_sfx[i].Save(wr);
		}
	}
}

void Sfx::Unserialize(Serializer::Reader &rd, Frame *f)
{
	int numActive = rd.Int32();
	if (numActive) {
		f->m_sfx = new Sfx[MAX_SFX_PER_FRAME];
		for (int i=0; i<numActive; i++) {
			f->m_sfx[i].Load(rd);
		}
	}
}

void Sfx::SetPosition(const vector3d &p)
{
	m_pos = p;
}

void Sfx::TimeStepUpdate(const float timeStep)
{
	m_age += timeStep;
	m_pos += m_vel * double(timeStep);

	switch (m_type) {
		case TYPE_EXPLOSION:
			if (m_age > 0.5) m_type = TYPE_NONE;
			break;
		case TYPE_DAMAGE:
			if (m_age > 2.0) m_type = TYPE_NONE;
			break;
		case TYPE_NONE: break;
	}
}

void Sfx::Render(Renderer *renderer, const matrix4x4d &ftransform)
{
	vector3d fpos = ftransform * GetPosition();

	switch (m_type) {
		case TYPE_NONE: break;
		case TYPE_EXPLOSION: {
			//Explosion effect: A quick flash of three concentric coloured spheres. A bit retro.
			glPushMatrix();
			matrix4x4f trans = trans.Identity();
			trans.Translate(fpos.x, fpos.y, fpos.z);
			RefCountedPtr<Material> exmat = Sfx::explosionEffect->GetMaterial();
			exmat->diffuse = Color(1.f, 1.f, 0.5f, 1.f);
			renderer->SetTransform(trans * matrix4x4f::ScaleMatrix(500*m_age));
			Sfx::explosionEffect->Draw(renderer);
			renderer->SetBlendMode(BLEND_ALPHA);
			exmat->diffuse = Color(1.f, 0.5f, 0.f, 0.66f);
			renderer->SetTransform(trans * matrix4x4f::ScaleMatrix(750*m_age));
			Sfx::explosionEffect->Draw(renderer);
			exmat->diffuse = Color(1.f, 0.f, 0.f, 0.33f);
			renderer->SetTransform(trans * matrix4x4f::ScaleMatrix(1000*m_age));
			Sfx::explosionEffect->Draw(renderer);
			glPopMatrix();
			break;
		}
		case TYPE_DAMAGE:
			vector3f pos(&fpos.x);
			damageParticle->diffuse = Color(1.f, 1.f, 0.f, 1.0f-(m_age/2.0f));
			renderer->SetBlendMode(BLEND_ALPHA_ONE);
			renderer->DrawPointSprites(1, &pos, damageParticle, 20.f);
			break;
	}
}

Sfx *Sfx::AllocSfxInFrame(Frame *f)
{
	if (!f->m_sfx) {
		f->m_sfx = new Sfx[MAX_SFX_PER_FRAME];
	}

	for (int i=0; i<MAX_SFX_PER_FRAME; i++) {
		if (f->m_sfx[i].m_type == TYPE_NONE) {
			return &f->m_sfx[i];
		}
	}
	return 0;
}

void Sfx::Add(const Body *b, TYPE t)
{
	Sfx *sfx = AllocSfxInFrame(b->GetFrame());
	if (!sfx) return;

	sfx->m_type = t;
	sfx->m_age = 0;
	sfx->SetPosition(b->GetPosition());
	sfx->m_vel = b->GetVelocity() + 200.0*vector3d(
			Pi::rng.Double()-0.5,
			Pi::rng.Double()-0.5,
			Pi::rng.Double()-0.5);
}

void Sfx::TimeStepAll(const float timeStep, Frame *f)
{
	if (f->m_sfx) {
		for (int i=0; i<MAX_SFX_PER_FRAME; i++) {
			if (f->m_sfx[i].m_type != TYPE_NONE) {
				f->m_sfx[i].TimeStepUpdate(timeStep);
			}
		}
	}

	for (Frame *c = f->GetFirstChild(); c; c = f->GetNextChild()) {
		TimeStepAll(timeStep, c);
	}
}

void Sfx::RenderAll(Renderer *renderer, Frame *f, const Frame *camFrame)
{
	if (f->m_sfx) {
		matrix4x4d ftran;
		Frame::GetFrameTransform(f, camFrame, ftran);

		for (int i=0; i<MAX_SFX_PER_FRAME; i++) {
			if (f->m_sfx[i].m_type != TYPE_NONE) {
				f->m_sfx[i].Render(renderer, ftran);
			}
		}
	}

	for (Frame *c = f->GetFirstChild(); c; c = f->GetNextChild()) {
		RenderAll(renderer, c, camFrame);
	}
}

void Sfx::Init(Graphics::Renderer *r)
{
	Graphics::MaterialDescriptor desc;
	RefCountedPtr<Graphics::Material> shieldMat(r->CreateMaterial(desc));
	RefCountedPtr<Graphics::Material> explosionMat(r->CreateMaterial(desc));
	shieldEffect = new Graphics::Drawables::Sphere3D(shieldMat, 2);
	explosionEffect = new Graphics::Drawables::Sphere3D(explosionMat, 2);

	desc.textures = 1;
	damageParticle = r->CreateMaterial(desc);
	damageParticle->texture0 = Graphics::TextureBuilder::Billboard("textures/smoke.png").GetOrCreateTexture(r, "billboard");
	ecmParticle = r->CreateMaterial(desc);
	ecmParticle->texture0 = Graphics::TextureBuilder::Billboard("textures/ecm.png").GetOrCreateTexture(r, "billboard");
}

void Sfx::Uninit()
{
	delete shieldEffect; shieldEffect = 0;
	delete explosionEffect; explosionEffect = 0;
	delete damageParticle; damageParticle = 0;
	delete ecmParticle; ecmParticle = 0;
}
