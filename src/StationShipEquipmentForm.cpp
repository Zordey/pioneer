#include "StationShipEquipmentForm.h"
#include "Pi.h"
#include "Player.h"
#include "SpaceStation.h"
#include "SpaceStationView.h"
#include "StationShipViewForm.h"
#include "ShipCpanel.h"

#define REMOVAL_VALUE_PERCENT 90

StationShipEquipmentForm::StationShipEquipmentForm(FormController *controller) : FaceForm(controller)
{
	m_station = Pi::player->GetDockedWith();

	SetTitle(stringf(256, "%s ship equipment", m_station->GetLabel().c_str()));

	Gui::VScrollBar *scroll = new Gui::VScrollBar();
	Gui::VScrollPortal *portal = new Gui::VScrollPortal(450);
	scroll->SetAdjustment(&portal->vscrollAdjust);

	int NUM_ITEMS = 0;
	const float YSEP = floor(Gui::Screen::GetFontHeight() * 1.5f);
	for (int i=Equip::FIRST_SHIPEQUIP; i<=Equip::LAST_SHIPEQUIP; i++) {
		if (m_station->GetStock(static_cast<Equip::Type>(i)))
			NUM_ITEMS++;
	}

	Gui::VBox *outerbox = new Gui::VBox();

	Gui::Fixed *innerbox = new Gui::Fixed(450, NUM_ITEMS*YSEP);
	innerbox->SetTransparency(true);

	for (int i=Equip::FIRST_SHIPEQUIP, num=0; i<=Equip::LAST_SHIPEQUIP; i++) {
		Equip::Type type = static_cast<Equip::Type>(i);
		int stock = m_station->GetStock(type);
		if (!stock) continue;
		Gui::Label *l = new Gui::Label(EquipType::types[i].name);
		if (EquipType::types[i].description) {
			l->SetToolTip(EquipType::types[i].description);
		}
		innerbox->Add(l,0,num*YSEP);
		
		innerbox->Add(new Gui::Label(format_money(m_station->GetPrice(type))), 200, num*YSEP);

		innerbox->Add(new Gui::Label(format_money(REMOVAL_VALUE_PERCENT * m_station->GetPrice(type) / 100)),
				275, num*YSEP);
		
		innerbox->Add(new Gui::Label(stringf(64, "%dt", EquipType::types[i].mass)), 360, num*YSEP);

		ButtonPair pair;
		pair.type = type;
		
		pair.add = new Gui::SolidButton();
		pair.add->onClick.connect(sigc::bind(sigc::mem_fun(this, &StationShipEquipmentForm::FitItem), type));
		innerbox->Add(pair.add, 400, num*YSEP);

		pair.remove = new Gui::SolidButton();
		pair.remove->onClick.connect(sigc::bind(sigc::mem_fun(this, &StationShipEquipmentForm::RemoveItem), type));
		innerbox->Add(pair.remove, 420, num*YSEP);

		m_buttons.push_back(pair);

		num++;
	}

	portal->Add(innerbox);

	Gui::Fixed *heading = new Gui::Fixed(470, Gui::Screen::GetFontHeight());
	const float *col = Gui::Theme::Colors::tableHeading;
	heading->Add((new Gui::Label("Item"))->Color(col), 0, 0);
	heading->Add((new Gui::Label("$ to fit"))->Color(col), 200, 0);
	heading->Add((new Gui::Label("$ for removal"))->Color(col), 275, 0);
	heading->Add((new Gui::Label("Wt"))->Color(col), 360, 0);
	heading->Add((new Gui::Label("Fit"))->Color(col), 400, 0);
	heading->Add((new Gui::Label("Remove"))->Color(col), 420, 0);
	outerbox->PackEnd(heading);

	Gui::HBox *body = new Gui::HBox();
	body->PackEnd(portal);
	body->PackEnd(scroll);
	outerbox->PackEnd(body);

	outerbox->SetSpacing(YSEP-Gui::Screen::GetFontHeight());
	Add(outerbox, 0, 0);

}

void StationShipEquipmentForm::ShowAll()
{
	FaceForm::ShowAll();
	RecalcButtonVisibility();
}

void StationShipEquipmentForm::RecalcButtonVisibility()
{
	for (std::list<ButtonPair>::iterator i = m_buttons.begin(); i != m_buttons.end(); i++) {
		Equip::Slot slot = EquipType::types[(*i).type].slot;

		if (Pi::player->m_equipment.FreeSpace(slot))
			(*i).add->Show();
		else
			(*i).add->Hide();

		if (Pi::player->m_equipment.Count(slot, (*i).type))
			(*i).remove->Show();
		else
			(*i).remove->Hide();
	}
}

void StationShipEquipmentForm::FitItem(Equip::Type t) {
	Equip::Slot slot = EquipType::types[t].slot;

	const shipstats_t *stats = Pi::player->CalcStats();
	int freespace = Pi::player->m_equipment.FreeSpace(slot);
	
	if (Pi::player->GetMoney() < m_station->GetPrice(t)) {
		Pi::cpan->MsgLog()->Message("", "You do not have enough money");
		return;
	}

	if (!freespace || stats->free_capacity < EquipType::types[t].mass) {
		Pi::cpan->MsgLog()->Message("", "There is no space on your ship");
		return;
	}

	if (slot == Equip::SLOT_LASER) {
		/* you have a choice of mount points for lasers */
		//OpenChildChatForm(new StationLaserPickMount(t, true));
		return;
	}
	
	Pi::player->m_equipment.Add(t);
	Pi::player->UpdateMass();
	Pi::player->SetMoney(Pi::player->GetMoney() - m_station->GetPrice(t));
	Pi::cpan->MsgLog()->Message("", "Fitting "+std::string(EquipType::types[t].name));

	RecalcButtonVisibility();
}

void StationShipEquipmentForm::RemoveItem(Equip::Type t) {
	Equip::Slot slot = EquipType::types[t].slot;

	int num = Pi::player->m_equipment.Count(slot, t);
	if (!num)
		return;

	Sint64 value = m_station->GetPrice(t) * REMOVAL_VALUE_PERCENT / 100;
	if (num > 1 && slot == Equip::SLOT_LASER) {
		/* you have a choice of mount points for lasers */
		//OpenChildChatForm(new StationLaserPickMount(t, false));
		return;
	}

	Pi::player->m_equipment.Remove(t, 1);
	Pi::player->UpdateMass();
	Pi::player->SetMoney(Pi::player->GetMoney() + value);
	m_station->AddEquipmentStock(t, 1);
	Pi::cpan->MsgLog()->Message("", "Removing "+std::string(EquipType::types[t].name));

	RecalcButtonVisibility();
}
