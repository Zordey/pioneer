#include "Context.h"
#include "FileSystem.h"
#include "text/FontDescriptor.h"
#include "LuaObject.h"

namespace UI {

Context::Context(Graphics::Renderer *renderer, int width, int height) : Single(this),
	m_renderer(renderer),
	m_width(float(width)),
	m_height(float(height)),
	m_needsLayout(false),
	m_float(new FloatContainer(this)),
	m_eventDispatcher(this),
	m_skin("textures/widgets.png", renderer)
{
	SetSize(vector2f(m_width,m_height));

	m_float->SetSize(vector2f(m_width,m_height));
	m_float->Attach(this);

	// XXX should do point sizes, but we need display DPI first
	// XXX TextureFont could load multiple sizes into the same object/atlas
	for (int i = FONT_SIZE_XSMALL; i < FONT_SIZE_MAX; i++) {
		int pixelSize = i*3 + 14;
		m_font[i] = RefCountedPtr<Text::TextureFont>(new Text::TextureFont(Text::FontDescriptor("TitilliumText22L004.otf", pixelSize, pixelSize, false, -1.0f), renderer));
	}
}

Context::~Context() {
    m_float->Detach();
}

Widget *Context::GetWidgetAtAbsolute(const vector2f &pos) {
	Widget *w = m_float->GetWidgetAtAbsolute(pos);
	if (!w || w == m_float.Get())
		w = Single::GetWidgetAtAbsolute(pos);
	return w;
}

void Context::Layout()
{
	m_float->Layout();
	Single::Layout();
	m_eventDispatcher.LayoutUpdated();
	m_needsLayout = false;
}

void Context::Update()
{
	if (m_needsLayout)
		Layout();

	m_float->Update();
	Single::Update();
}

void Context::Draw()
{
	Graphics::Renderer *r = GetRenderer();

	r->SetOrthographicProjection(0, m_width, m_height, 0, -1, 1);
	r->SetTransform(matrix4x4f::Identity());
	r->SetClearColor(Color::BLACK);
	r->SetDepthTest(false);

	// XXX GL renderer enables lighting by default. if all draws use materials
	// that's ok, but for filled regions (ie ColorBackground) its not right. a
	// scissored version of Renderer::ClearScreen would be the most efficient,
	// but I'm not quite ready to do it yet.
	glDisable(GL_LIGHTING);

	Single::Draw();
    m_float->Draw();

	DisableScissor();
}

void Context::EnableScissor(const vector2f &pos, const vector2f &size)
{
	vector2f flippedPos(pos.x, m_height-pos.y-floorf(size.y));
	m_renderer->SetScissor(true, flippedPos, size);
}

void Context::DisableScissor()
{
	m_renderer->SetScissor(false);
}

void Context::LuaInit()
{
	LuaObject<UI::Align>::RegisterClass();
	LuaObject<UI::Background>::RegisterClass();
	LuaObject<UI::Box>::RegisterClass();
	LuaObject<UI::HBox>::RegisterClass();
	LuaObject<UI::VBox>::RegisterClass();
	LuaObject<UI::Button>::RegisterClass();
	LuaObject<UI::CheckBox>::RegisterClass();
	LuaObject<UI::ColorBackground>::RegisterClass();
	LuaObject<UI::Container>::RegisterClass();
	LuaObject<UI::Context>::RegisterClass();
	LuaObject<UI::DropDown>::RegisterClass();
	LuaObject<UI::Grid>::RegisterClass();
	LuaObject<UI::Image>::RegisterClass();
	LuaObject<UI::Label>::RegisterClass();
	LuaObject<UI::List>::RegisterClass();
	LuaObject<UI::Margin>::RegisterClass();
	LuaObject<UI::MultiLineText>::RegisterClass();
	LuaObject<UI::Scroller>::RegisterClass();
	LuaObject<UI::Single>::RegisterClass();
	LuaObject<UI::Slider>::RegisterClass();
	LuaObject<UI::HSlider>::RegisterClass();
	LuaObject<UI::VSlider>::RegisterClass();
	LuaObject<UI::Widget>::RegisterClass();
}

}
