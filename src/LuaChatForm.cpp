#include "Pi.h"
#include "Player.h"
#include "LuaChatForm.h"
#include "libs.h"
#include "Gui.h"
#include "SpaceStation.h"
#include "SpaceStationView.h"
#include "PoliceChatForm.h"
#include "CommodityTradeWidget.h"
#include "LuaObject.h"

/*
EXPORT_OOLUA_FUNCTIONS_10_NON_CONST(LuaChatForm,
		UpdateBaseDisplay,
		Close,
		Clear,
		GotoPolice,
		SetTitle,
		SetMessage,
		AddOption,
		AddTraderWidget,
		RemoveAdvertOnClose,
		SetStage)
EXPORT_OOLUA_FUNCTIONS_2_CONST(LuaChatForm,
		GetStage,
		GetAdRef)
*/

LuaChatForm::~LuaChatForm()
{
	if (m_adTaken) m_station->BBRemoveAdvert(m_modName, m_modRef);
}

void LuaChatForm::OnAdvertDeleted()
{
	m_advert = 0;
	Clear();
	SetMessage("Sorry, this advert has expired.");
	//AddOption("Hang up.", 0);
}

void LuaChatForm::StartChat(SpaceStation *s, const BBAdvert *a)
{
	m_adTaken = false;
	m_advert = a;
	m_station = s;
	m_modName = a->GetModule();
	m_modRef = a->GetLuaRef();
	m_stage = "";
	CallDialogHandler(0);
}

/*
void LuaChatForm::AddTraderWidget()
{
	CommodityTradeWidget *w = new CommodityTradeWidget(this);
	w->onClickBuy.connect(sigc::mem_fun(this, &LuaChatForm::OnClickBuy));
	w->onClickSell.connect(sigc::mem_fun(this, &LuaChatForm::OnClickSell));
	Gui::Fixed *f = new Gui::Fixed(400.0, 200.0);
	f->Add(w, 0, 0);
	m_msgregion->PackEnd(f);

	m_commodityTradeWidget = w;
}
*/

void LuaChatForm::AddOption(std::string text, int val)
{
	if (!hasOpts) {
		hasOpts = true;
		m_optregion->PackStart(new Gui::Label("Suggested responses:"));
	}
	Gui::Box *box = new Gui::HBox();
	Gui::Button *b = new Gui::SolidButton();
	b->onClick.connect(sigc::bind(sigc::mem_fun(this, &LuaChatForm::CallDialogHandler), val));
	box->SetSpacing(5.0f);
	box->PackEnd(b);
	box->PackEnd(new Gui::Label(text));
	m_optregion->PackEnd(box);
	ShowAll();
}

void LuaChatForm::CallDialogHandler(int optionClicked)
{
	if (m_advert == 0) {
		// advert has expired
		Close();
	} else {
		lua_State *l = LuaManager::Instance()->GetLuaState();

		lua_getfield(l, LUA_REGISTRYINDEX, "PiAdverts");
		assert(!lua_isnil(l, -1));

		lua_pushinteger(l, m_modRef);
		lua_gettable(l, -2);
		assert(!lua_isnil(l, -1));

		lua_getfield(l, -1, "onActivate");
		assert(lua_isfunction(l, -1));

		LuaObject<LuaChatForm>::PushToLua(this);
		LuaInt::PushToLua(m_modRef);
		LuaInt::PushToLua(optionClicked);
		lua_call(l, 3, 0);

		lua_pop(l, 2);
	}
}

static inline void _get_trade_function(lua_State *l, int ref, const char *name)
{
	LUA_DEBUG_START(l)

	lua_getfield(l, LUA_REGISTRYINDEX, "PiAdverts");
	assert(!lua_isnil(l, -1));

	lua_pushinteger(l, ref);
	lua_gettable(l, -2);
	assert(!lua_isnil(l, -1));

	lua_getfield(l, -1, "tradeWidgetCallbacks");
	assert(lua_istable(l, -1));

	lua_getfield(l, -1, name);
	assert(lua_isfunction(l, -1));

	lua_insert(l, -4);
	lua_pop(l, 3);

	LUA_DEBUG_END(l, 1)
}

Sint64 LuaChatForm::GetPrice(Equip::Type t) const {
    /*
	lua_State *l = PiLuaModules::GetLuaState();
	PiLuaModules::ModCall(m_modName.c_str(), "TraderGetPrice", 1, this, (int)t);
	Sint64 price = (Sint64)(100.0*lua_tonumber(l, -1));
	lua_pop(l, 1);
	return price;
    */
    return 0;
}

bool LuaChatForm::CanBuy(Equip::Type t, bool verbose) const {
	return DoesSell(t);
}
bool LuaChatForm::CanSell(Equip::Type t, bool verbose) const {
	return (GetStock(t) > 0) && DoesSell(t);
}
bool LuaChatForm::DoesSell(Equip::Type t) const {
	lua_State *l = LuaManager::Instance()->GetLuaState();

	LUA_DEBUG_START(l)

	_get_trade_function(l, m_modRef, "canTrade");

	LuaInt::PushToLua(m_modRef);
	LuaInt::PushToLua(static_cast<int>(t));
	lua_call(l, 2, 1);

	bool can_trade = lua_toboolean(l, -1) != 0;
	lua_pop(l, 1);

	LUA_DEBUG_END(l, 0);

	return can_trade;
}
int LuaChatForm::GetStock(Equip::Type t) const {
    /*
	lua_State *l = PiLuaModules::GetLuaState();
	PiLuaModules::ModCall(m_modName.c_str(), "TraderGetStock", 1, this, (int)t);
	int stock = lua_tointeger(l, -1);
	lua_pop(l, 1);
	return stock;
    */
    return 0;
}
void LuaChatForm::Bought(Equip::Type t) {
	//PiLuaModules::ModCall(m_modName.c_str(), "TraderBought", 0, this, (int)t);
}
void LuaChatForm::Sold(Equip::Type t) {
	//PiLuaModules::ModCall(m_modName.c_str(), "TraderSold", 0, this, (int)t);
}

void LuaChatForm::OnClickBuy(int equipType) {
    /*
	lua_State *l = PiLuaModules::GetLuaState();
	PiLuaModules::ModCall(m_modName.c_str(), "TraderOnClickBuy", 1, this, equipType);

	bool doBuy = lua_toboolean(l, -1) != 0;
	lua_pop(l, 1);
	if (doBuy) {
		if (SellTo(Pi::player, (Equip::Type)equipType, true)) {
			Pi::Message(stringf(512, "You have bought 1t of %s.", EquipType::types[equipType].name));
		}
		m_commodityTradeWidget->UpdateStock(equipType);
		UpdateBaseDisplay();
	}
    */
}
void LuaChatForm::OnClickSell(int equipType) {
    /*
	lua_State *l = PiLuaModules::GetLuaState();

	PiLuaModules::ModCall(m_modName.c_str(), "TraderOnClickSell", 1, this, equipType);
	bool doSell = lua_toboolean(l, -1) != 0;
	lua_pop(l, 1);
	if (doSell) {
		if (BuyFrom(Pi::player, (Equip::Type)equipType, true)) {
			Pi::Message(stringf(512, "You have sold 1t of %s.", EquipType::types[equipType].name));
		}
		m_commodityTradeWidget->UpdateStock(equipType);
		UpdateBaseDisplay();
	}
    */
}

/*
void LuaChatForm::GotoPolice() {
	Close();
	Pi::spaceStationView->JumpTo(new PoliceChatForm());
}
*/

static int l_luachatform_clear(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	dialog->Clear();
	return 0;
}

static int l_luachatform_set_title(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	std::string title = LuaString::PullFromLua();
	dialog->SetTitle(title.c_str());
	return 0;
}

static int l_luachatform_set_message(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	std::string message = LuaString::PullFromLua();
	dialog->SetMessage(message.c_str());
	return 0;
}

static int l_luachatform_add_option(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	std::string text = LuaString::PullFromLua();
	int val = LuaInt::PullFromLua();
	dialog->AddOption(text, val);
	return 0;
}

static inline void _bad_trade_function(lua_State *l, const char *name) {
	luaL_where(l, 0);
	std::string err = stringf(256, "%s bad argument '%s' to 'add_goods_trader' (function expected, got %s)", lua_tostring(l, -1), name, luaL_typename(l, -2));
	luaL_error(l, err.c_str());
}

int LuaChatForm::l_luachatform_add_goods_trader(lua_State *l)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();

	if(!lua_istable(l, 1))
		luaL_typerror(l, 2, lua_typename(l, LUA_TFUNCTION));
	
	// XXX verbose but what can you do?
	lua_getfield(l, 1, "canTrade");
	if (!lua_isfunction(l, -1))
		_bad_trade_function(l, "canTrade");

	lua_getfield(l, 1, "getStock");
	if (!lua_isfunction(l, -1))
		_bad_trade_function(l, "getStock");

	lua_getfield(l, 1, "getPrice");
	if (!lua_isfunction(l, -1))
		_bad_trade_function(l, "getPrice");

	lua_getfield(l, 1, "onClickBuy");
	if(!lua_isfunction(l, -1) && !lua_isnil(l, -1))
		_bad_trade_function(l, "onClickBuy");

	lua_getfield(l, 1, "onClickSell");
	if(!lua_isfunction(l, -1) && !lua_isnil(l, -1))
		_bad_trade_function(l, "onClickSell");

	lua_getfield(l, 1, "bought");
	if(!lua_isfunction(l, -1) && !lua_isnil(l, -1))
		_bad_trade_function(l, "bought");

	lua_getfield(l, 1, "sold");
	if(!lua_isfunction(l, -1) && !lua_isnil(l, -1))
		_bad_trade_function(l, "sold");

	lua_pop(l, 6);

	lua_getfield(l, LUA_REGISTRYINDEX, "PiAdverts");
	assert(!lua_isnil(l, -1));

	lua_pushinteger(l, dialog->m_modRef);
	lua_gettable(l, -2);
	assert(!lua_isnil(l, -1));

	lua_pushstring(l, "tradeWidgetCallbacks");
	lua_pushvalue(l, 1);
	lua_settable(l, -3);

	lua_pop(l, 2);

	CommodityTradeWidget *w = new CommodityTradeWidget(dialog);
	w->onClickBuy.connect(sigc::mem_fun(dialog, &LuaChatForm::OnClickBuy));
	w->onClickSell.connect(sigc::mem_fun(dialog, &LuaChatForm::OnClickSell));
	Gui::Fixed *f = new Gui::Fixed(400.0, 200.0);
	f->Add(w, 0, 0);
	dialog->m_msgregion->PackEnd(f);

	dialog->m_commodityTradeWidget = w;

	//onClose.connect( XXX something to clean up the callback table )

	return 0;
}

static int l_luachatform_close(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	dialog->Close();
	return 0;
}

static int l_luachatform_refresh(lua_State *s)
{
	LuaChatForm *dialog = LuaObject<LuaChatForm>::PullFromLua();
	dialog->UpdateBaseDisplay();
	return 0;
}

template <> const char *LuaObject<LuaChatForm>::s_type = "ChatForm";
template <> const char *LuaObject<LuaChatForm>::s_inherit = NULL;

template <> const luaL_reg LuaObject<LuaChatForm>::s_methods[] = {
	{ "clear",            l_luachatform_clear                         },
	{ "set_title",        l_luachatform_set_title                     },
	{ "set_message",      l_luachatform_set_message                   },
	{ "add_option",       l_luachatform_add_option                    },
	{ "add_goods_trader", LuaChatForm::l_luachatform_add_goods_trader },
	{ "close",            l_luachatform_close                         },
	{ "refresh",          l_luachatform_refresh                       },
	{ 0, 0 }
};

template <> const luaL_reg LuaObject<LuaChatForm>::s_meta[] = {
	{ 0, 0 }
};
