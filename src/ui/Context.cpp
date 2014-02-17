<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "Context.h"
#include "FileSystem.h"
#include "text/FontDescriptor.h"
#include "Lua.h"
#include "FileSystem.h"
#include <typeinfo>

namespace UI {

// minimum screen height for scaling. if the screen has fewer vertical pixels
// than this, certain draw elements will be scaled down
static const int SCALE_CUTOFF_HEIGHT = 768;

static const float FONT_SCALE[] = {
	0.7f,  // XSMALL
	0.85f, // SMALL
	1.0f,  // NORMAL
	1.4f,  // LARGE
	1.8f,  // XLARGE

	0.7f,  // HEADING_XSMALL
	0.85f, // HEADING_SMALL
	1.0f,  // HEADING_NORMAL
	1.4f,  // HEADING_LARGE
	1.8f   // HEADING_XLARGE
};

<<<<<<< HEAD
Context::Context(LuaManager *lua, Graphics::Renderer *renderer, int width, int height, const std::string &lang) : Single(this),
=======
Context::Context(LuaManager *lua, Graphics::Renderer *renderer, int width, int height, const std::string &lang) : Container(this),
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_renderer(renderer),
	m_width(width),
	m_height(height),
	m_scale(std::min(float(m_height)/SCALE_CUTOFF_HEIGHT, 1.0f)),
	m_needsLayout(false),
<<<<<<< HEAD
	m_float(new FloatContainer(this)),
=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	m_eventDispatcher(this),
	m_skin("ui/Skin.ini", renderer, GetScale()),
	m_lua(lua)
{
	lua_State *l = m_lua->GetLuaState();
	lua_newtable(l);
	m_templateStore = LuaRef(l, -1);

	SetSize(Point(m_width,m_height));
<<<<<<< HEAD

	m_float->SetSize(Point(m_width,m_height));
	m_float->Attach(this);
=======
	m_visible = true;

	NewLayer();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	// XXX should do point sizes, but we need display DPI first
	// XXX TextureFont could load multiple sizes into the same object/atlas
	{
		const Text::FontDescriptor baseFontDesc(Text::FontDescriptor::Load(FileSystem::gameDataFiles, "fonts/UIFont.ini", lang));
		for (int i = FONT_SMALLEST; i <= FONT_LARGEST; i++) {
			const Text::FontDescriptor fontDesc(baseFontDesc.filename, baseFontDesc.pixelWidth*FONT_SCALE[i]*GetScale(), baseFontDesc.pixelHeight*FONT_SCALE[i]*GetScale(), baseFontDesc.outline, baseFontDesc.advanceXAdjustment);

			m_font[i] = RefCountedPtr<Text::TextureFont>(new Text::TextureFont(fontDesc, renderer));
		}
	}
	{
		const Text::FontDescriptor baseFontDesc(Text::FontDescriptor::Load(FileSystem::gameDataFiles, "fonts/UIHeadingFont.ini", lang));
		for (int i = FONT_HEADING_SMALLEST; i <= FONT_HEADING_LARGEST; i++) {
			const Text::FontDescriptor fontDesc(baseFontDesc.filename, baseFontDesc.pixelWidth*FONT_SCALE[i]*GetScale(), baseFontDesc.pixelHeight*FONT_SCALE[i]*GetScale(), baseFontDesc.outline, baseFontDesc.advanceXAdjustment);

			m_font[i] = RefCountedPtr<Text::TextureFont>(new Text::TextureFont(fontDesc, renderer));
		}
	}

	m_scissorStack.push(std::make_pair(Point(0,0), Point(m_width,m_height)));
}

<<<<<<< HEAD
Context::~Context() {
	m_float->Detach();
=======
Layer *Context::NewLayer()
{
	Layer *layer = new Layer(this);
	AddWidget(layer);
	SetWidgetDimensions(layer, Point(0), Point(m_width, m_height));
	m_layers.push_back(layer);
	m_needsLayout = true;
	return layer;
}

void Context::DropLayer()
{
	// dropping the last layer would be bad
	assert(m_layers.size() > 1);
	RemoveWidget(m_layers.back());
	m_layers.pop_back();
	m_needsLayout = true;
}

void Context::DropAllLayers()
{
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i != m_layers.end(); ++i)
		RemoveWidget(*i);
	m_layers.clear();
	NewLayer();
	m_needsLayout = true;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Widget *Context::GetWidgetAt(const Point &pos)
{
<<<<<<< HEAD
	Widget *w = m_float->GetWidgetAt(pos);
	if (!w || w == m_float.Get())
		w = Single::GetWidgetAt(pos);
	return w;
=======
	return GetTopLayer()->GetWidgetAt(pos);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Context::Layout()
{
<<<<<<< HEAD
	m_needsLayout = false;

	m_float->Layout();
	Single::Layout();

	if (m_needsLayout) {
		m_float->Layout();
		Single::Layout();
	}
=======
	// some widgets (eg MultiLineText) can require two layout passes because we
	// don't know their preferred size until after their first layout run. so
	// then we have to do layout again to make sure everyone else gets it right
	m_needsLayout = false;

	LayoutChildren();
	if (m_needsLayout)
		LayoutChildren();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	m_needsLayout = false;

	m_eventDispatcher.LayoutUpdated();
}

void Context::Update()
{
<<<<<<< HEAD
	m_eventDispatcher.Update();

	if (m_needsLayout)
		Layout();

	m_float->Update();
	Single::Update();
=======
	if (m_needsLayout)
		Layout();

	Container::Update();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void Context::Draw()
{
	Graphics::Renderer *r = GetRenderer();

<<<<<<< HEAD
	r->SetOrthographicProjection(0, m_width, m_height, 0, -1, 1);
	r->SetTransform(matrix4x4f::Identity());
	r->SetClearColor(Color::BLACK);
	r->SetBlendMode(Graphics::BLEND_ALPHA);
	r->SetDepthTest(false);

	Single::Draw();
	m_float->Draw();

	r->SetScissor(false);
=======
	// reset renderer for each layer
	for (std::vector<Layer*>::iterator i = m_layers.begin(); i != m_layers.end(); ++i) {
		r->SetOrthographicProjection(0, m_width, m_height, 0, -1, 1);
		r->SetTransform(matrix4x4f::Identity());
		r->SetClearColor(Color::BLACK);
		r->SetBlendMode(Graphics::BLEND_ALPHA);
		r->SetDepthTest(false);

		(*i)->Draw();

		r->SetScissor(false);
	}
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

Widget *Context::CallTemplate(const char *name, const LuaTable &args)
{
	lua_State *l = m_lua->GetLuaState();

	m_templateStore.PushCopyToStack();
	const LuaTable t(l, -1);
	if (!t.Get<bool,const char *>(name))
		return 0;

	t.PushValueToStack<const char*>(name);
	lua_pushvalue(l, args.GetIndex());
	pi_lua_protected_call(m_lua->GetLuaState(), 1, 1);

	return LuaObject<UI::Widget>::CheckFromLua(-1);
}

Widget *Context::CallTemplate(const char *name)
{
	return CallTemplate(name, LuaTable(m_lua->GetLuaState()));
}

void Context::DrawWidget(Widget *w)
{
	const Point &pos = w->GetPosition();
	const Point &drawOffset = w->GetDrawOffset();
	const Point &size = w->GetSize();

	m_drawWidgetPosition += pos;

	const std::pair<Point,Point> &currentScissor(m_scissorStack.top());
	const Point &currentScissorPos(currentScissor.first);
	const Point &currentScissorSize(currentScissor.second);

	const Point newScissorPos(std::max(m_drawWidgetPosition.x, currentScissorPos.x), std::max(m_drawWidgetPosition.y, currentScissorPos.y));

	const Point newScissorSize(
		Clamp(std::min(newScissorPos.x + size.x, currentScissorPos.x + currentScissorSize.x) - newScissorPos.x, 0, m_width),
		Clamp(std::min(newScissorPos.y + size.y, currentScissorPos.y + currentScissorSize.y) - newScissorPos.y, 0, m_height));

	m_scissorStack.push(std::make_pair(newScissorPos, newScissorSize));

	m_renderer->SetScissor(true, vector2f(newScissorPos.x, m_height - newScissorPos.y - newScissorSize.y), vector2f(newScissorSize.x, newScissorSize.y));

	m_drawWidgetPosition += drawOffset;

	m_renderer->SetTransform(matrix4x4f::Translation(m_drawWidgetPosition.x, m_drawWidgetPosition.y, 0));

	w->Draw();

	m_scissorStack.pop();

	m_drawWidgetPosition -= pos + drawOffset;
}

}
