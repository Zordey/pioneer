#include "ServicesChatForm.h"
#include "Pi.h"
#include "Player.h"
#include "SpaceStation.h"

ServicesChatForm::ServicesChatForm() : FaceChatForm()
{
	SetBgColor(0.19, 0.39, 0.19, 1.0);

	SetTitle(stringf(256, "%s services", Pi::player->GetDockedWith()->GetLabel().c_str()));

	Gui::Label *l = new Gui::Label(
		"Hello friend! Thank you for docking with this space station!\n"
		"After a recent accident involving a lemur and an onion we've had to "
		"do some extensive renovations. You'll find the smell much more "
		"pleasant since we got that stain out of the rug, but you'll notice "
		"the lights flicker and the comms system sometimes get stuck on Jazz "
		"FM. Also, there's a containment leak on deck 12, so remember to wear "
		"a hat."
	);
	Add(l, 10, 10);

	Gui::SolidButton *b = new Gui::SolidButton();
	b->SetShortcut(SDLK_1, KMOD_NONE);
	b->onClick.connect(sigc::mem_fun(this, &ServicesChatForm::RequestLaunch));
	Add(b, 30, 140);
	l = new Gui::Label("Request Launch");
	Add(l, 55, 140);

	b = new Gui::SolidButton();
	b->SetShortcut(SDLK_2, KMOD_NONE);
	b->onClick.connect(sigc::mem_fun(this, &ServicesChatForm::Shipyard));
	Add(b, 30, 200);
	l = new Gui::Label("Shipyard");
	Add(l, 55, 200);

	b = new Gui::SolidButton();
	b->SetShortcut(SDLK_3, KMOD_NONE);
	b->onClick.connect(sigc::mem_fun(this, &ServicesChatForm::CommodityMarket));
	Add(b, 30, 260);
	l = new Gui::Label("Commodity market");
	Add(l, 55, 260);

	b = new Gui::SolidButton();
	b->SetShortcut(SDLK_4, KMOD_NONE);
	b->onClick.connect(sigc::mem_fun(this, &ServicesChatForm::BulletinBoard));
	Add(b, 30, 320);
	l = new Gui::Label("Bulletin board");
	Add(l, 55, 320);

	b = new Gui::SolidButton();
	b->SetShortcut(SDLK_5, KMOD_NONE);
	b->onClick.connect(sigc::mem_fun(this, &ServicesChatForm::Police));
	Add(b, 30, 380);
	l = new Gui::Label("Contact local police");
	Add(l, 55, 380);
}

void ServicesChatForm::RequestLaunch()
{
}

void ServicesChatForm::Shipyard()
{
}

void ServicesChatForm::CommodityMarket()
{
}

void ServicesChatForm::BulletinBoard()
{
}

void ServicesChatForm::Police()
{
}
