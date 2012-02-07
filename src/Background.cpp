#include "Background.h"
#include "perlin.h"
#include "Pi.h"
#include "StarSystem.h"
#include "Space.h"
#include "Frame.h"
#include "Player.h"
#include <vector>
#include "Game.h"
#include "render/Material.h"
#include "render/Renderer.h"
#include "render/StaticMesh.h"
#include "render/Surface.h"

namespace Background
{

Starfield::Starfield()
{
	Init();
	//starfield is not filled without a seed
}

Starfield::Starfield(unsigned long seed)
{
	Init();
	Fill(seed);
}

Starfield::~Starfield()
{
	delete m_model;
	delete m_shader;
}

void Starfield::Init()
{
	// reserve some space for positions, colours
	VertexArray *stars = new VertexArray(ATTRIB_POSITION | ATTRIB_DIFFUSE, BG_STAR_MAX);
	// one "surface"
	m_model = new StaticMesh(1, TYPE_POINTS);
	m_shader = new Render::Shader("bgstars");
	RefCountedPtr<Material> mat(new Material());
	mat->shader = m_shader;
	m_model->surfaces[0].SetMaterial(mat);
	m_model->surfaces[0].SetVertices(stars);
	m_model->numSurfaces = 1;
}

void Starfield::Fill(unsigned long seed)
{
	VertexArray *va = m_model->surfaces[0].GetVertices();
	va->Clear(); // clear if previously filled
	// Slight colour variation to stars based on seed
	MTRand rand(seed);

	//fill the array
	for (int i=0; i<BG_STAR_MAX; i++) {
		float col = float(rand.Double(0,1));

		col *= col * col * 3.0;
		col = (col > 0.725 ? 1.45-col : col);
		col = Clamp(col, 0.00f, 0.725f);

		if (i<6) {
			col = 0.9;
		} else if (i<21) {
			col = 0.85;
		} else if (i<46) {
			col = 0.8;
		}

		// this is proper random distribution on a sphere's surface
		const float theta = float(rand.Double(0.0, 2.0*M_PI));
		const float u = float(rand.Double(-1.0, 1.0));

		const double red = rand.Double(col-0.05f,col);

		va->Add(vector3f(
				1000.0f * sqrt(1.0f - u*u) * cos(theta),
				1000.0f * u,
				1000.0f * sqrt(1.0f - u*u) * sin(theta)
			), Color(
				red,
				rand.Double(col-0.1f,red),
				rand.Double(col-0.05f,col),
				1.f
			)
		);
	}
}

void Starfield::Draw(Renderer *renderer)
{
	glDisable(GL_DEPTH_TEST);

	if (Render::AreShadersEnabled()) {
		glEnable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
	} else {
		glDisable(GL_POINT_SMOOTH);
		glPointSize(1.0f);
	}

	// XXX would be nice to get rid of the Pi:: stuff here
	if (!Pi::game || Pi::player->GetFlightState() != Ship::HYPERSPACE) {
		renderer->DrawStaticMesh(m_model);
	} else {
		/* HYPERSPACING!!!!!!!!!!!!!!!!!!! */
		/* all this jizz isn't really necessary, since the player will
		 * be in the root frame when hyperspacing... */
		matrix4x4d m, rot;
		Frame::GetFrameTransform(Pi::game->GetSpace()->GetRootFrame(), Pi::player->GetFrame(), m);
		m.ClearToRotOnly();
		Pi::player->GetRotMatrix(rot);
		m = rot.InverseOf() * m;
		vector3d pz(m[2], m[6], m[10]);

		// roughly, the multiplier gets smaller as the duration gets larger.
		// the time-looking bits in this are completely arbitrary - I figured
		// it out by tweaking the numbers until it looked sort of right
		double mult = 0.0015 / (Pi::player->GetHyperspaceDuration() / (60.0*60.0*24.0*7.0));

		double hyperspaceProgress = Pi::game->GetHyperspaceProgress();

		LineVertex *vtx = new LineVertex[BG_STAR_MAX * 2];
		VertexArray *va = m_model->surfaces[0].GetVertices();
		for (int i=0; i<BG_STAR_MAX; i++) {
			
			vector3f v(va->position[i]);
			v += vector3f(pz*hyperspaceProgress*mult);

			vtx[i*2].position = va->position[i] + v;
			vtx[i*2].color = va->diffuse[i];

			vtx[i*2+1].position = v;
			vtx[i*2+1].color = va->diffuse[i];
		}
		Pi::renderer->DrawLines(BG_STAR_MAX*2, vtx);
		delete[] vtx;
	}

	glEnable(GL_DEPTH_TEST);

	if (Render::AreShadersEnabled()) {
		glDisable(GL_VERTEX_PROGRAM_POINT_SIZE_ARB);
		glDisable(GL_POINT_SMOOTH);
	}
}


MilkyWay::MilkyWay()
{
	m_model = new StaticMesh(2, TRIANGLE_STRIP);

	//build milky way model in two strips (about 256 verts)
	//The model is built as a generic vertex array first. The renderer
	//will reprocess this into buffered format as it sees fit. The old data is
	//kept around as long as StaticMesh is alive (needed if the cache is to be regenerated)

	VertexArray *bottom = new VertexArray(ATTRIB_POSITION | ATTRIB_DIFFUSE);
	VertexArray *top = new VertexArray(ATTRIB_POSITION | ATTRIB_DIFFUSE);
	m_model->surfaces[0].SetVertices(bottom);
	m_model->surfaces[1].SetVertices(top);

	const Color dark(0.f);
	const Color bright(0.05,0.05f, 0.05f, 0.05f);

	//bottom
	float theta;
	for (theta=0.0; theta < 2.0*M_PI; theta+=0.1) {
		bottom->Add(
				vector3f(100.0f*sin(theta), float(-40.0 - 30.0*noise(sin(theta),1.0,cos(theta))), 100.0f*cos(theta)),
				dark);
		bottom->Add(
			vector3f(100.0f*sin(theta), float(5.0*noise(sin(theta),0.0,cos(theta))), 100.0f*cos(theta)),
			bright);
	}
	theta = 2.0*M_PI;
	bottom->Add(
		vector3f(100.0f*sin(theta), float(-40.0 - 30.0*noise(sin(theta),1.0,cos(theta))), 100.0f*cos(theta)),
		dark);
	bottom->Add(
		vector3f(100.0f*sin(theta), float(5.0*noise(sin(theta),0.0,cos(theta))), 100.0f*cos(theta)),
		bright);
	//top
	for (theta=0.0; theta < 2.0*M_PI; theta+=0.1) {
		top->Add(
			vector3f(100.0f*sin(theta), float(5.0*noise(sin(theta),0.0,cos(theta))), 100.0f*cos(theta)),
			bright);
		top->Add(
			vector3f(100.0f*sin(theta), float(40.0 + 30.0*noise(sin(theta),-1.0,cos(theta))), 100.0f*cos(theta)),
			dark);
	}
	theta = 2.0*M_PI;
	top->Add(
		vector3f(100.0f*sin(theta), float(5.0*noise(sin(theta),0.0,cos(theta))), 100.0f*cos(theta)),
		bright);
	top->Add(
		vector3f(100.0f*sin(theta), float(40.0 + 30.0*noise(sin(theta),-1.0,cos(theta))), 100.0f*cos(theta)),
		dark);
}

MilkyWay::~MilkyWay()
{
	delete m_model;
}

void MilkyWay::Draw(Renderer *renderer)
{
	glDisable(GL_DEPTH_TEST);
	assert(m_model != 0);
	renderer->DrawStaticMesh(m_model);
	glEnable(GL_DEPTH_TEST);
}

Container::Container()
{
}

Container::Container(unsigned long seed)
{
	Refresh(seed);
};

void Container::Refresh(unsigned long seed)
{
	// redo starfield, milkyway stays normal for now
	m_starField.Fill(seed);
}

void Container::Draw(const matrix4x4d &transform) const
{
	//XXX not really const - renderer can modify the buffers
	glPushMatrix();
	Renderer *renderer = Pi::renderer;
	renderer->SetTransform(transform);
	const_cast<MilkyWay&>(m_milkyWay).Draw(renderer);
	// squeeze the starfield a bit to get more density near horizon
	matrix4x4d starTrans = transform * matrix4x4d::ScaleMatrix(1.0, 0.4, 1.0);
	renderer->SetTransform(starTrans);
	const_cast<Starfield&>(m_starField).Draw(renderer);
	glPopMatrix();
}

}; //namespace Background
