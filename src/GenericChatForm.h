#ifndef _GENERICCHATFORM_H
#define _GENERICCHATFORM_H

#include <string>
#include "Gui.h"

class GenericChatForm: public Gui::Fixed {
public:
	GenericChatForm();
	virtual ~GenericChatForm() {}
	void Close();
	void Clear();
	void ReInit();
	void SetTitle(const char *title);
	void AddBaseDisplay();
	void AddVideoWidget();
	void UpdateBaseDisplay();
	void OpenChildChatForm(GenericChatForm *form);
	void AddOption(sigc::slot<void,GenericChatForm*,int> slot, const char *text, int val);
	void SetMessage(const char*);

	sigc::signal<void> onClose;

	Gui::Fixed *m_chatRegion;
	Gui::VBox *m_msgregion;
	Gui::VBox *m_optregion;
protected:
	bool hasOpts;
private:
	
	Gui::Label *m_legalstatus;
	Gui::Label *m_money;
	Gui::Label *m_cargoSpaceUsed;
	Gui::Label *m_cargoSpaceFree;
	Gui::Label *m_equipmentMass;
	Gui::Label *m_titleLabel;
};	

#endif /* _GENERICCHATFORM_H */
