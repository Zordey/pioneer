#include "libs.h"
#include "collider/collider.h"
#include "FileSystem.h"
#include "graphics/Drawables.h"
#include "graphics/Graphics.h"
#include "graphics/Material.h"
#include "graphics/Renderer.h"
#include "graphics/VertexArray.h"
#include "gui/Gui.h"
#include "ModManager.h"
#include "newmodel/Newmodel.h"
#include "ui/Context.h"
#include "utils.h"
#include "Light.h"
#include "StringF.h"
#include <sstream>

using namespace Graphics;

static Renderer *renderer;

static SDL_Surface *g_screen;
static int g_width, g_height;
static int g_mouseMotion[2];
static char g_keyState[SDLK_LAST];
static const int MAX_MOUSE_BTN_IDX = SDL_BUTTON_WHEELDOWN + 1;
static int g_mouseButton[MAX_MOUSE_BTN_IDX];	// inc to 6 as mouseScroll is index 5
static bool g_doBenchmark = false;
static vector3f g_campos(0.0f, 0.0f, 100.0f);
static matrix4x4f g_camorient;

//some utility functions
static bool setMouseButton(const Uint8 idx, const int value)
{
	if( idx < MAX_MOUSE_BTN_IDX ) {
		g_mouseButton[idx] = value;
		return true;
	}
	return false;
}

static vector3f azElToDir(float yaw, float pitch)
{
	//0,0 points to "right" (1,0,0)
	vector3f v;
	v.x = cos(DEG2RAD(yaw)) * cos(DEG2RAD(pitch));
	v.y = sin(DEG2RAD(pitch));
	v.z = sin(DEG2RAD(yaw)) * cos(DEG2RAD(pitch));
	return v;
}
//end utility funcs

class Viewer;
static Viewer *g_viewer;

static int g_renderType = 0;
static float g_frameTime;

struct Options {
	bool attachGuns;
	bool showBoundingBoxes;
	bool showBoundingRadius;
	bool showGrid;
	float gridInterval;
	int lightPreset;

	Options()
	: attachGuns(false)
	, showBoundingBoxes(false)
	, showBoundingRadius(false)
	, showGrid(false)
	, gridInterval(0.f)
	, lightPreset(0)
	{ }
};

class Viewer: public Gui::Fixed {
private: //data members
	bool m_playing;
	bool m_screenshotQueued;
	CollisionSpace *m_space;
	CollMesh *m_cmesh;
	double m_currentTime;
	Geom *m_geom;
	Gui::Label *m_trisReadout;
	Model *m_model;
	ModelParams m_modelParams;
	Options m_options;
	RefCountedPtr<Newmodel::ModelNode> m_gunModelNode;
	ScopedPtr<Model> m_gunModel;
	std::list<std::string> m_logLines;
	std::string m_logString;
	std::string m_modelName;
	UI::Context *m_ui;
	UI::DropDown *m_animSelector;
	UI::DropDown *m_patternSelector;
	UI::Slider *m_sliders[3*3]; //color sliders 3*rgb

private: //methods
	void SetupUI();
	bool OnAnimPlay(UI::Widget *w, bool reverse);
	bool OnAnimStop(UI::Widget *w);
	bool OnReloadModel(UI::Widget *w);
	bool OnToggleBoundingRadius(UI::Widget *w);
	bool OnToggleGrid(UI::Widget *w);
	bool OnToggleGuns(UI::CheckBox *w);
	void OnLightPresetChanged(unsigned int index, const std::string &);
	void OnModelColorsChanged(float v=0.f);
	void OnPatternChanged(unsigned int index, const std::string &);
	void AddLog(const std::string &message);
	void ClearModel();
	void DrawLog();
	void Screenshot();
	void UpdateAnimList();
	void UpdateLights();
	void UpdatePatternList();
	void UpdateTime();

public:
	void ResetCamera();
	void SetModel(Model *, const std::string &modelname);
	void PickModel(const std::string &initial_name, const std::string &initial_errormsg);
	void PickModel() {
		PickModel("", "");
	}
	bool PickAnotherModel() {
		PickModel();
		return true;
	}

	Viewer(): Gui::Fixed(float(g_width), float(g_height)),
		m_playing(false),
		m_screenshotQueued(false),
		m_cmesh(0),
		m_currentTime(0.001 * SDL_GetTicks()),
		m_geom(0),
		m_model(0),
		m_logString(""),
		m_modelName("")
	{
		SetupUI();

		//load gun model for attachment test
		{
			Newmodel::Loader loader(renderer);
			try {
				Newmodel::NModel *m = loader.LoadModel("test_gun");
				m_gunModel.Reset(m);
				m_gunModelNode.Reset(new Newmodel::ModelNode(m_gunModel.Get()));
			} catch (Newmodel::LoadingError &) {
				AddLog("Could not load test_gun model");
			}
		}

		m_space = new CollisionSpace();
		Gui::Screen::AddBaseWidget(this, 0, 0);
		SetTransparency(true);

		m_trisReadout = new Gui::Label("");
		Add(m_trisReadout, 500, 0);
		{
			Gui::Button *b = new Gui::SolidButton();
			//b->SetShortcut(SDLK_c, KMOD_NONE);
			//b->onClick.connect(sigc::mem_fun(*this, &Viewer::OnClickChangeView));
			Add(b, 10, 10);
			Add(new Gui::Label("[c] Change view (normal, collision mesh"), 30, 10);
		}
		{
			Gui::Button *b = new Gui::SolidButton();
			//b->SetShortcut(SDLK_p, KMOD_NONE);
			//b->onClick.connect(sigc::mem_fun(*this, &Viewer::OnClickToggleBenchmark));
			Add(b, 10, 70);
			Add(new Gui::Label("[p] Toggle performance test (renders models 1000 times per frame)"), 30, 70);
		}
		{
			Gui::Button *b = new Gui::SolidButton();
			//b->SetShortcut(SDLK_b, KMOD_LSHIFT);
			//b->onClick.connect(sigc::mem_fun(*this, &Viewer::OnToggleBoundingRadius));
			Add(b, 10, 90);
			Add(new Gui::Label("[shift-b] Visualize bounding radius"), 30, 90);
		}
		{
			Gui::Button *b = new Gui::SolidButton();
			//b->SetShortcut(SDLK_g, KMOD_LSHIFT);
			//b->onClick.connect(sigc::mem_fun(*this, &Viewer::OnToggleGrid));
			Add(b, 10, 110);
			Add(new Gui::Label("[shift-g] Toggle grid"), 30, 110);
		}

		ShowAll();
		Show();
	}

	~Viewer() {
		ClearModel();
		delete m_space;
		delete m_ui;
	}

	void OnAnimChange(Gui::Adjustment *a, Gui::TextEntry *e) {
		char buf[128];
		snprintf(buf, sizeof(buf), "%.2f", a->GetValue());
		e->SetText(buf);
	}

	void OnClickToggleBenchmark() {
		g_doBenchmark = !g_doBenchmark;
	}

	void OnClickChangeView() {
		g_renderType++;
		// XXX raytraced view disabled
		if (g_renderType > 1) g_renderType = 0;
	}

	void MainLoop() __attribute((noreturn));

private:
	void DrawGrid(matrix4x4f& trans, double radius);
	void PollEvents();
	void TryModel(const SDL_keysym *sym, Gui::TextEntry *entry, Gui::Label *errormsg);
	void VisualizeBoundingRadius(matrix4x4f& trans, double radius);
};

#if 0
static UI::Button *AddButton(UI::Context *c, UI::Box *box, const std::string &label)
{
	UI::Button *button = 0;
	const UI::Box::ChildAttrs attrs(false, false);
	box->PackEnd(((button = c->Button())->SetInnerWidget(c->Label(label))), attrs);
	return button;
}

static UI::CheckBox *AddCheckbox(UI::Context *c, UI::Box *box, const std::string &label)
{
	UI::CheckBox *button = 0;
	const UI::Box::ChildAttrs attrs(false, false);
	box->PackEnd(
		c->HBox()->PackEnd(
			(button = c->CheckBox()), attrs
		)->PackEnd(c->Label(label), attrs)
		, attrs
	);
	return button;
}
#endif

//widget-label pair
static void AddPair(UI::Context *c, UI::Box *parent, UI::Widget *widget, const std::string &label)
{
	const Uint32 flags = 0;
	parent->PackEnd(
		c->HBox(5.f)->PackEnd(widget, flags)->PackEnd(c->Label(label), flags)
	);
}

void Viewer::SetupUI()
{
	/* Components
	Reload model
	Cycle grid mode
	Toggle bounding radius
	Draw collision mesh

	Toggle guns

	Select pattern
	3x3 colour sliders

	Light presets (dropdown)

	Message area

	Stats:
	fps + ms/frame
	triangles
	*/
	m_ui = new UI::Context(renderer, g_width, g_height);
	UI::Context *c = m_ui;
	UI::Box *box;
	UI::Box *buttBox;
	UI::Box *animBox;
	UI::Button *b1, *gridBtn, *reloadBtn;
	UI::Button *playBtn, *stopBtn, *revBtn;
	UI::CheckBox *radiusCheck, *gunsCheck;
	
	c->SetInnerWidget((box = c->VBox(5.f)));

	//buttons
	/*c1 = AddCheckbox(c, buttonBox, "Toggle bounding radius");
	b1 = AddButton(c, buttonBox, "Cycle grid mode");

	c1->onClick.connect(sigc::mem_fun(*this, &Viewer::OnToggleBoundingRadius));
	b1->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnToggleGrid), b1));*/
	Uint32 battrs = 0;

	box->PackEnd((buttBox = c->VBox(5.f)), battrs);
	AddPair(c, buttBox, (b1 = c->Button()), "Pick another model");
	AddPair(c, buttBox, (reloadBtn = c->Button()), "Reload model");
	AddPair(c, buttBox, (gridBtn = c->Button()), "Grid mode");
	AddPair(c, buttBox, (radiusCheck = c->CheckBox()), "Show bounding radius");
	AddPair(c, buttBox, (gunsCheck = c->CheckBox()), "Attach guns");
	AddPair(c, buttBox, (c->CheckBox()), "Draw collision mesh");

	box->PackEnd(animBox = c->VBox(5.f), battrs);
	animBox->PackEnd(c->Label("Animation:"));
	animBox->PackEnd(m_animSelector = c->DropDown()->AddOption("None"));
	AddPair(c, animBox, playBtn = c->Button(), "Play/Pause");
	AddPair(c, animBox, revBtn = c->Button(), "Play reverse");
	AddPair(c, animBox, stopBtn = c->Button(), "Stop");

	b1->onClick.connect(sigc::mem_fun(*this, &Viewer::PickAnotherModel));
	reloadBtn->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnReloadModel), reloadBtn));
	gridBtn->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnToggleGrid), gridBtn));
	radiusCheck->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnToggleBoundingRadius), radiusCheck));
	gunsCheck->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnToggleGuns), gunsCheck));

	playBtn->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnAnimPlay), playBtn, false));
	revBtn->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnAnimPlay), revBtn, true));
	stopBtn->onClick.connect(sigc::bind(sigc::mem_fun(*this, &Viewer::OnAnimStop), stopBtn));

	UI::DropDown *ddown;
	buttBox->PackEnd(c->Label("Pattern:"));
	buttBox->PackEnd((m_patternSelector = c->DropDown()->AddOption("Default")));
	buttBox->PackEnd(c->Label("Lights:"));
	buttBox->PackEnd((ddown = c->DropDown()
		->AddOption("1  Front white")
		->AddOption("2  Two-point")
		->AddOption("3  Backlight")
		)
	);

	m_patternSelector->onOptionSelected.connect(sigc::mem_fun(*this, &Viewer::OnPatternChanged));
	ddown->onOptionSelected.connect(sigc::mem_fun(*this, &Viewer::OnLightPresetChanged));

	//3x3 colour sliders
	const Uint32 all = UI::Box::BOX_FILL | UI::Box::BOX_EXPAND;
	const Uint32 expand = UI::Box::BOX_EXPAND;
	const float spacing = 5.f;
	c->AddFloatingWidget(
		c->HBox()->PackEnd( //three columns
			c->VBox()->PackEnd(UI::WidgetSet( //three rows
				c->HBox(spacing)->PackEnd(c->Label("R"))->PackEnd(m_sliders[0] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("G"))->PackEnd(m_sliders[1] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("B"))->PackEnd(m_sliders[2] = c->HSlider(), expand)
				)), all
		)->PackEnd(
			c->VBox()->PackEnd(UI::WidgetSet( //three rows
				c->HBox(spacing)->PackEnd(c->Label("R"))->PackEnd(m_sliders[3] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("G"))->PackEnd(m_sliders[4] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("B"))->PackEnd(m_sliders[5] = c->HSlider(), expand)
				)), all
		)->PackEnd(
			c->VBox()->PackEnd(UI::WidgetSet( //three rows
				c->HBox(spacing)->PackEnd(c->Label("R"))->PackEnd(m_sliders[6] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("G"))->PackEnd(m_sliders[7] = c->HSlider(), expand),
				c->HBox(spacing)->PackEnd(c->Label("B"))->PackEnd(m_sliders[8] = c->HSlider(), expand)
				)), all
		)
	, vector2f(0.f, g_height-200.f), vector2f(500.f, 300.f));

	//connect slider signals, set initial values
	const float values[] = {
		1.f, 0.f, 0.f,
		0.f, 1.f, 0.f,
		0.f, 0.f, 1.f
	};
	for(unsigned int i=0; i<3*3; i++) {
		m_sliders[i]->SetValue(values[i]);
		m_sliders[i]->onValueChanged.connect(sigc::mem_fun(*this, &Viewer::OnModelColorsChanged));
	}

	c->Layout();
}

bool Viewer::OnAnimPlay(UI::Widget *w, bool reverse)
{
	Newmodel::Animation::Direction dir = reverse ? Newmodel::Animation::REVERSE : Newmodel::Animation::FORWARD;
	const std::string animname = m_animSelector->GetSelectedOption();
	m_playing = !m_playing;
	if (m_playing) {
		int success = static_cast<Newmodel::NModel*>(m_model)->PlayAnimation(animname, dir);
		if (success)
			AddLog(stringf("Playing animation \"%0\"", animname));
		else {
			AddLog(stringf("Model does not have animation \"%0\"", animname));
			m_playing = false;
		}
	} else {
		AddLog("Animation paused");
	}
	return m_playing;
}

bool Viewer::OnAnimStop(UI::Widget *w)
{
	if (m_playing) AddLog("Animation stopped");
	m_playing = false;
	static_cast<Newmodel::NModel*>(m_model)->StopAnimations();
	return false;
}

bool Viewer::OnReloadModel(UI::Widget *w)
{
	try {
		AddLog("Reloading model...");
		Newmodel::Loader loader(renderer);
		Model *mo = loader.LoadModel(m_modelName);
		SetModel(mo, m_modelName);
		AddLog("Model loaded");
	} catch (Newmodel::LoadingError &) {
		PickModel(m_modelName, std::string("Could not find model: ") + m_modelName);
	}
	return true;
}

void Viewer::AddLog(const std::string &line)
{
	m_logLines.push_back(line);
	if (m_logLines.size() > 8) m_logLines.pop_front();

	std::stringstream ss;
	for(std::list<std::string>::const_iterator it = m_logLines.begin();
		it != m_logLines.end();
		++it)
	{
		ss << *it << std::endl;
	}
	m_logString = ss.str();
}

void Viewer::ClearModel()
{
	// clear old geometry
	if (m_model) {
		delete m_model;
		m_model = 0;
	}
	if (m_cmesh) {
		delete m_cmesh;
		m_cmesh = 0;
	}
	if (m_geom) {
		m_space->RemoveGeom(m_geom);
		delete m_geom;
		m_geom = 0;
	}
}

void Viewer::DrawLog()
{
	Gui::Screen::EnterOrtho();
	Gui::Screen::PushFont("ConsoleFont");
	Gui::Screen::RenderString(m_logString, 10, 400);
	Gui::Screen::PopFont();
	Gui::Screen::LeaveOrtho();
}

void Viewer::Screenshot()
{
	char buf[256];
	const time_t t = time(0);
	struct tm *_tm = localtime(&t);
	strftime(buf, sizeof(buf), "modelviewer-%Y%m%d-%H%M%S.png", _tm);
	Screendump(buf, g_width, g_height);
	AddLog("Screenshot saved");
}

void Viewer::UpdateAnimList()
{
	m_animSelector->Clear();
	Newmodel::NModel *model = dynamic_cast<Newmodel::NModel*>(m_model);
	if (model) {
		const std::vector<Newmodel::Animation*> &anims = model->GetAnimations();
		for(unsigned int i=0; i<anims.size(); i++) {
			m_animSelector->AddOption(anims[i]->GetName());
		}
	}
	m_animSelector->Layout();
}

void Viewer::UpdateLights()
{
	Light lights[2];

	switch(m_options.lightPreset) {
	case 0:
		//Front white
		lights[0] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(90,0), Color(1.0f, 1.0f, 1.0f), Color(0.f), Color(1.f));
		lights[1] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(0,-90), Color(0.05, 0.05f, 0.1f), Color(0.f), Color(1.f));
		break;
	case 1:
		//Two-point
		lights[0] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(120,0), Color(0.9f, 0.8f, 0.8f), Color(0.f), Color(1.f));
		lights[1] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(-30,-90), Color(0.7f, 0.5f, 0.0f), Color(0.f), Color(1.f));
		break;
	case 2:
		//Backlight
		lights[0] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(-75,20), Color(1.f), Color(0.f), Color(1.f));
		lights[1] = Light(Light::LIGHT_DIRECTIONAL, azElToDir(0,-90), Color(0.05, 0.05f, 0.1f), Color(0.f), Color(1.f));
		break;
	};

	renderer->SetLights(2, &lights[0]);
}

void Viewer::UpdatePatternList()
{
	m_patternSelector->Clear();
	Newmodel::NModel *model = dynamic_cast<Newmodel::NModel*>(m_model);
	if (model) {
		const Newmodel::PatternContainer &pats = model->GetPatterns();
		for(unsigned int i=0; i<pats.size(); i++) {
			m_patternSelector->AddOption(pats[i].name);
		}
		m_ui->Layout();
	}
}

void Viewer::UpdateTime()
{
	static double lastTime = 0;
	const double newtime = 0.001 * SDL_GetTicks();
	if (m_playing) {
		m_currentTime += newtime - lastTime;
	}
	lastTime = newtime;
}

void Viewer::OnLightPresetChanged(unsigned int index, const std::string &)
{
	m_options.lightPreset = std::min<unsigned int>(index, 2);
}

static Color4ub GetColor(UI::Slider *r, UI::Slider *g, UI::Slider *b)
{
	return Color4ub(r->GetValue() * 255.f, g->GetValue() * 255.f, b->GetValue() * 255.f);
}

void Viewer::OnModelColorsChanged(float)
{
	Newmodel::NModel *model = dynamic_cast<Newmodel::NModel*>(m_model);
	if (model) {
		std::vector<Color4ub> colors;
		colors.push_back(GetColor(m_sliders[0], m_sliders[1], m_sliders[2]));
		colors.push_back(GetColor(m_sliders[3], m_sliders[4], m_sliders[5]));
		colors.push_back(GetColor(m_sliders[6], m_sliders[7], m_sliders[8]));
		model->SetColors(renderer, colors);
	}
}

void Viewer::OnPatternChanged(unsigned int index, const std::string &)
{
	Newmodel::NModel *model = dynamic_cast<Newmodel::NModel*>(m_model);
	if (model) {
		assert(index < model->GetPatterns().size());
		model->SetPattern(index);
	}
}

bool Viewer::OnToggleGrid(UI::Widget *w)
{
	if (!m_options.showGrid) {
		m_options.showGrid = true;
		m_options.gridInterval = 1.0f;
	}
	else {
		m_options.gridInterval = powf(10, ceilf(log10f(m_options.gridInterval))+1);
		if (m_options.gridInterval >= 10000.0f) {
			m_options.showGrid = false;
			m_options.gridInterval = 0.0f;
		}
	}
	AddLog(m_options.showGrid
		? stringf("Grid: %0{d}", int(m_options.gridInterval))
		: "Grid: off");
	return m_options.showGrid;
}

bool Viewer::OnToggleGuns(UI::CheckBox *w)
{
	if (!m_gunModel.Valid() || !m_gunModelNode.Valid()) {
		AddLog("test_gun.model not available");
		return false;
	}
	Newmodel::NModel *model = dynamic_cast<Newmodel::NModel*>(m_model);
	if (!model) return false;
	m_options.attachGuns = !m_options.attachGuns;
	Newmodel::Group *tagL = model->FindTagByName("tag_gun_left");
	Newmodel::Group *tagR = model->FindTagByName("tag_gun_right");
	if (!tagL || !tagR) {
		AddLog("Missing tags gun_left and gun_right in model");
		return false;
	}
	if (m_options.attachGuns) {
		tagL->AddChild(m_gunModelNode.Get());
		tagR->AddChild(m_gunModelNode.Get());
	} else { //detach
		//we know there's nothing else
		tagL->RemoveChildAt(0);
		tagR->RemoveChildAt(0);
	}
	return true;
}

bool Viewer::OnToggleBoundingRadius(UI::Widget *w)
{
	m_options.showBoundingRadius = !m_options.showBoundingRadius;
	return m_options.showBoundingRadius;
}

void Viewer::ResetCamera()
{
	g_campos = vector3f(0.0f, 0.0f, m_model->GetDrawClipRadius());
	g_camorient = matrix4x4f::Identity();
	//matrix4x4f modelRot = matrix4x4f::Identity();
}

void Viewer::SetModel(Model *model, const std::string &name)
{
	ClearModel();

	m_modelName = name;
	m_model = model;
	m_cmesh = m_model->CreateCollisionMesh(0);
	m_geom = new Geom(m_cmesh->GetGeomTree());
	m_space->AddGeom(m_geom);
	ResetCamera();

	UpdateAnimList();
	UpdatePatternList();
	OnModelColorsChanged();
}

void Viewer::TryModel(const SDL_keysym *sym, Gui::TextEntry *entry, Gui::Label *errormsg)
{
	if (sym->sym == SDLK_RETURN) {
		const std::string &name = entry->GetText();
		Newmodel::Loader load(renderer);
		try {
			Model *mo = load.LoadModel(name);
			SetModel(mo, name);
		} catch (Newmodel::LoadingError &) {
			errormsg->SetText("Could not find model: " + name);
		}	
	}
}

void Viewer::PickModel(const std::string &initial_name, const std::string &initial_errormsg)
{
	//delete old
	ClearModel();

	Gui::Fixed *f = new Gui::Fixed();
	f->SetSizeRequest(Gui::Screen::GetWidth()*0.5f, Gui::Screen::GetHeight()*0.5);
	Gui::Screen::AddBaseWidget(f, Gui::Screen::GetWidth()*0.25f, Gui::Screen::GetHeight()*0.25f);

	f->Add(new Gui::Label("Enter the name of the model you want to view (esc to quit app):"), 0, 0);

	Gui::Label *errormsg = new Gui::Label(initial_errormsg);
	f->Add(errormsg, 0, 64);

	Gui::TextEntry *entry = new Gui::TextEntry();
	entry->SetText(initial_name);
	entry->onKeyPress.connect(sigc::bind(sigc::mem_fun(this, &Viewer::TryModel), entry, errormsg));
	entry->Show();
	f->Add(entry, 0, 32);

	while (!m_model) {
		this->Hide();
		f->ShowAll();
		PollEvents();
		renderer->ClearScreen();
		Gui::Draw();
		renderer->SwapBuffers();
	}
	Gui::Screen::RemoveBaseWidget(f);
	delete f;
	this->Show();
}

#if 0
static void render_coll_mesh(const LmrCollMesh *m)
{
	Material mat;
	mat.unlit = true;
	mat.diffuse = Color(1.f, 0.f, 1.f);
	glDepthRange(0.0,0.9f);
	VertexArray va(ATTRIB_POSITION, m->ni * 3);
	for (int i=0; i<m->ni; i+=3) {
		va.Add(static_cast<vector3f>(&m->pVertex[3*m->pIndex[i]]));
		va.Add(static_cast<vector3f>(&m->pVertex[3*m->pIndex[i+1]]));
		va.Add(static_cast<vector3f>(&m->pVertex[3*m->pIndex[i+2]]));
	}
	renderer->DrawTriangles(&va, &mat);

	mat.diffuse = Color(1.f);
	glPolygonOffset(-1.f, -1.f);
	renderer->SetWireFrameMode(true);
	renderer->DrawTriangles(&va, &mat);
	renderer->SetWireFrameMode(false);
	glPolygonOffset(0.f, 0.f);
}
#endif

void Viewer::MainLoop()
{
	Uint32 lastTurd = SDL_GetTicks();

	Uint32 t = SDL_GetTicks();
	int numFrames = 0, fps = 0, numTris = 0;
	Uint32 lastFpsReadout = SDL_GetTicks();
	//g_campos = vector3f(0.0f, 0.0f, m_cmesh->GetBoundingRadius());
	g_camorient = matrix4x4f::Identity();
	matrix4x4f modelRot = matrix4x4f::Identity();
	m_modelParams.scrWidth = g_width;

	for (;;) {
		PollEvents();
		UpdateTime();

		if (g_keyState[SDLK_LSHIFT] || g_keyState[SDLK_RSHIFT]) {
			if (g_keyState[SDLK_UP]) g_camorient = g_camorient * matrix4x4f::RotateXMatrix(g_frameTime);
			if (g_keyState[SDLK_DOWN]) g_camorient = g_camorient * matrix4x4f::RotateXMatrix(-g_frameTime);
			if (g_keyState[SDLK_LEFT]) g_camorient = g_camorient * matrix4x4f::RotateYMatrix(-g_frameTime);
			if (g_keyState[SDLK_RIGHT]) g_camorient = g_camorient * matrix4x4f::RotateYMatrix(g_frameTime);
			if (g_mouseButton[3]) {
				float rx = 0.01f*g_mouseMotion[1];
				float ry = 0.01f*g_mouseMotion[0];
				g_camorient = g_camorient * matrix4x4f::RotateXMatrix(rx);
				g_camorient = g_camorient * matrix4x4f::RotateYMatrix(ry);
				if (g_mouseButton[1]) {
					g_campos = g_campos - g_camorient * vector3f(0.0f,0.0f,1.0f) * 0.01 *
						m_model->GetDrawClipRadius();
				}
			}
		} else {
			if (g_keyState[SDLK_UP]) modelRot = modelRot * matrix4x4f::RotateXMatrix(g_frameTime);
			if (g_keyState[SDLK_DOWN]) modelRot = modelRot * matrix4x4f::RotateXMatrix(-g_frameTime);
			if (g_keyState[SDLK_LEFT]) modelRot = modelRot * matrix4x4f::RotateYMatrix(-g_frameTime);
			if (g_keyState[SDLK_RIGHT]) modelRot = modelRot * matrix4x4f::RotateYMatrix(g_frameTime);
			if (g_mouseButton[3]) {
				float rx = 0.01f*g_mouseMotion[1];
				float ry = 0.01f*g_mouseMotion[0];
				modelRot = modelRot * matrix4x4f::RotateXMatrix(rx);
				modelRot = modelRot * matrix4x4f::RotateYMatrix(ry);
			}
		}
		float rate = 5.f * g_frameTime;
		if (g_keyState[SDLK_LSHIFT]) rate = 20.f * g_frameTime;
		if (g_keyState[SDLK_EQUALS] || g_keyState[SDLK_KP_PLUS]) g_campos = g_campos - g_camorient * vector3f(0.0f,0.0f,1.f) * rate;
		if (g_keyState[SDLK_MINUS] || g_keyState[SDLK_KP_MINUS]) g_campos = g_campos + g_camorient * vector3f(0.0f,0.0f,1.f) * rate;
		if (g_keyState[SDLK_PAGEUP]) g_campos = g_campos - g_camorient * vector3f(0.0f,0.0f,0.5f);
		if (g_keyState[SDLK_PAGEDOWN]) g_campos = g_campos + g_camorient * vector3f(0.0f,0.0f,0.5f);

		float znear;
		float zfar;
		renderer->GetNearFarRange(znear, zfar);
		renderer->SetPerspectiveProjection(85, g_width/float(g_height), znear, zfar);
		renderer->SetTransform(matrix4x4f::Identity());
		renderer->ClearScreen();
		renderer->SetDepthTest(true);
		UpdateLights();
		static_cast<Newmodel::NModel*>(m_model)->UpdateAnimations(m_currentTime);
#if 0
		int beforeDrawTriStats = LmrModelGetStatsTris();
#endif
		if (g_renderType == 0) {
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			matrix4x4f m = g_camorient.InverseOf() * matrix4x4f::Translation(-g_campos) * modelRot.InverseOf();
			if (g_doBenchmark) {
				for (int i=0; i<1000; i++) m_model->Render(renderer, m, &m_modelParams);
			} else {
				m_model->Render(renderer, m, &m_modelParams);
			}
			glPopAttrib();
		} else if (g_renderType == 1) {
			glPushMatrix();
			matrix4x4f m = g_camorient.InverseOf() * matrix4x4f::Translation(-g_campos) * modelRot.InverseOf();
			glMultMatrixf(&m[0]);
#if 0
			render_coll_mesh(m_cmesh);
#endif
			glPopMatrix();
		}

		if (m_options.showBoundingRadius) {
			matrix4x4f mo = g_camorient.InverseOf() * matrix4x4f::Translation(-g_campos);// * modelRot.InverseOf();
			VisualizeBoundingRadius(mo, m_model->GetDrawClipRadius());
		}

		if (m_options.showGrid) {
			matrix4x4f m = g_camorient.InverseOf() * matrix4x4f::Translation(-g_campos) * modelRot.InverseOf();
			const float rad = m_model->GetDrawClipRadius();
			DrawGrid(m, rad);
			const int numAxVerts = 6;
			const vector3f vts[numAxVerts] = {
				//X
				vector3f(0.f, 0.f, 0.f),
				vector3f(rad, 0.f, 0.f),

				//Y
				vector3f(0.f, 0.f, 0.f),
				vector3f(0.f, rad, 0.f),

				//Z
				vector3f(0.f, 0.f, 0.f),
				vector3f(0.f, 0.f, rad),
			};
			const Color col[numAxVerts] = {
				Color(1.f, 0.f, 0.f),
				Color(1.f, 0.f, 0.f),

				Color(0.f, 0.f, 1.f),
				Color(0.f, 0.f, 1.f),

				Color(0.f, 1.f, 0.f),
				Color(0.f, 1.f, 0.f)
			};
			renderer->SetDepthTest(false);
			renderer->DrawLines(numAxVerts, &vts[0], &col[0]);
			renderer->SetDepthTest(true);
		}

		{
#if 0
			char buf[256];
			Aabb aabb = m_cmesh->GetAabb();
			snprintf(buf, sizeof(buf), "%d triangles, %d fps, %.3fm tris/sec\ncollision mesh size: %.1fx%.1fx%.1f (radius %.1f)\nClipping radius %.1f\nGrid interval: %d metres",
					(g_renderType == 0 ? 
						LmrModelGetStatsTris() - beforeDrawTriStats :
						m_cmesh->m_numTris),
					fps,
					numTris/1000000.0f,
					aabb.max.x-aabb.min.x,
					aabb.max.y-aabb.min.y,
					aabb.max.z-aabb.min.z,
					aabb.GetBoundingRadius(),
					m_model->GetDrawClipRadius(),
					int(gridInterval));
			m_trisReadout->SetText(buf);
#endif
		}
		
		//Gui::Draw();
		m_ui->Update();
		if (!m_screenshotQueued) {
			renderer->SetDepthTest(false);
			renderer->SetOrthographicProjection(0, g_width, g_height, 0, -1, 1);
			renderer->SetTransform(matrix4x4f::Identity());
			renderer->SetClearColor(Color::BLACK);
			renderer->SetDepthTest(false);
			m_ui->Draw();
			DrawLog();
		}
		renderer->SwapBuffers();
		if (m_screenshotQueued) {
			m_screenshotQueued = false;
			Screenshot();
		}
		numFrames++;
		g_frameTime = (SDL_GetTicks() - lastTurd) * 0.001f;
		lastTurd = SDL_GetTicks();
#if 0
		if (SDL_GetTicks() - lastFpsReadout > 1000) {
			numTris = LmrModelGetStatsTris();
			fps = numFrames;
			numFrames = 0;
			lastFpsReadout = SDL_GetTicks();
			LmrModelClearStatsTris();
		}
#endif
	}
}

void Viewer::PollEvents()
{
	SDL_Event event;

	g_mouseMotion[0] = g_mouseMotion[1] = 0;
	while (SDL_PollEvent(&event)) {
		Gui::HandleSDLEvent(&event);
		m_ui->DispatchSDLEvent(event);
		switch (event.type) {
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
                    if (g_viewer->m_model) {
                        g_viewer->PickModel();
                    } else {
                        SDL_Quit();
                        exit(0);
                    }
				}
				if (event.key.keysym.sym == SDLK_F11) SDL_WM_ToggleFullScreen(g_screen);
				if (event.key.keysym.sym == SDLK_PRINT) m_screenshotQueued = true;
				g_keyState[event.key.keysym.sym] = 1;
				break;
			case SDL_KEYUP:
				g_keyState[event.key.keysym.sym] = 0;
				break;
			case SDL_MOUSEBUTTONDOWN:
				setMouseButton(event.button.button, 1);
				break;
			case SDL_MOUSEBUTTONUP:
				setMouseButton(event.button.button, 0);
				break;
			case SDL_MOUSEMOTION:
				g_mouseMotion[0] += event.motion.xrel;
				g_mouseMotion[1] += event.motion.yrel;
				break;
			case SDL_QUIT:
				SDL_Quit();
				exit(0);
				break;
		}
	}
}

void Viewer::VisualizeBoundingRadius(matrix4x4f& trans, double radius)
{
	renderer->SetTransform(trans);
	Drawables::Circle circ(radius, Color(0.f, 0.f, 1.f, 1.f));
	circ.Draw(renderer);
}

void Viewer::DrawGrid(matrix4x4f& trans, double radius)
{
	const float dist = abs(g_campos.z);

	const float max = std::min(powf(10, ceilf(log10f(dist))), ceilf(radius/m_options.gridInterval)*m_options.gridInterval);

	std::vector<vector3f> points;

	for (float x = -max; x <= max; x += m_options.gridInterval) {
		points.push_back(vector3f(x,0,-max));
		points.push_back(vector3f(x,0,max));
		points.push_back(vector3f(0,x,-max));
		points.push_back(vector3f(0,x,max));

		points.push_back(vector3f(x,-max,0));
		points.push_back(vector3f(x,max,0));
		points.push_back(vector3f(0,-max,x));
		points.push_back(vector3f(0,max,x));

		points.push_back(vector3f(-max,x,0));
		points.push_back(vector3f(max,x,0));
		points.push_back(vector3f(-max,0,x));
		points.push_back(vector3f(max,0,x));
	}

	renderer->SetTransform(trans);
	renderer->DrawLines(points.size(), &points[0], Color(0.0f,0.2f,0.0f,1.0f));
}


int main(int argc, char **argv)
{
	if ((argc<=1) || (0==strcmp(argv[1],"--help"))) {
		printf("Usage:\nluamodelviewer <width> <height> <model name>\n");
	}
	if (argc >= 3) {
		g_width = atoi(argv[1]);
		g_height = atoi(argv[2]);
	} else {
		g_width = 800;
		g_height = 600;
	}

	FileSystem::Init();
	FileSystem::rawFileSystem.MakeDirectory(FileSystem::GetUserDir());
	ModManager::Init();

	const SDL_VideoInfo *info = NULL;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
		exit(-1);
	}

	info = SDL_GetVideoInfo();

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_OPENGL;

	if ((g_screen = SDL_SetVideoMode(g_width, g_height, info->vfmt->BitsPerPixel, flags)) == 0) {
		// fall back on 16-bit depth buffer...
		SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 6);
		SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
		SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
		fprintf(stderr, "Failed to set video mode. (%s). Re-trying with 16-bit depth buffer.\n", SDL_GetError());
		if ((g_screen = SDL_SetVideoMode(g_width, g_height, info->vfmt->BitsPerPixel, flags)) == 0) {
			fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
		}
	}
	glewInit();

	renderer = Graphics::Init(g_width, g_height, true);
	Gui::Init(renderer, g_width, g_height, g_width, g_height);

	g_viewer = new Viewer();
	if (argc >= 4) {
		try {
			const std::string &name(argv[3]);
			Newmodel::Loader loader(renderer);
			Model *mo = loader.LoadModel(name);
			g_viewer->SetModel(mo, name);
			//attach some guns
			if(0)
			{
				Newmodel::NModel *parent = static_cast<Newmodel::NModel*>(mo);
				Newmodel::NModel *gun = loader.LoadModel("test_gun");
				Newmodel::Group *tag = parent->FindTagByName("tag_gun_left");
				if (tag && gun)
					tag->AddChild(new Newmodel::ModelNode(gun));
				tag = parent->FindTagByName("tag_gun_right");
				if (tag && gun) {
					tag->AddChild(new Newmodel::ModelNode(gun));
				}
			}
		} catch (Newmodel::LoadingError &) {
			g_viewer->PickModel(argv[3], std::string("Could not find model: ") + argv[3]);
		}
	} else {
		g_viewer->PickModel();
	}

	g_viewer->MainLoop();
	FileSystem::Uninit();
	delete renderer;
	return 0;
}
