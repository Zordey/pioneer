<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef UI_DROPDOWN_H
#define UI_DROPDOWN_H

#include "Container.h"

namespace UI {

class Background;
class Label;
class Icon;
class List;

class DropDown : public Container {
public:
	virtual Point PreferredSize();
	virtual void Layout();
<<<<<<< HEAD

	DropDown *AddOption(const std::string &text);
	const std::string &GetSelectedOption() const;
	void Clear();

=======
	virtual void Update();

	DropDown *AddOption(const std::string &text);
	void Clear();

	size_t NumItems() const;
	bool IsEmpty() const;

	const std::string &GetSelectedOption() const;
	bool SetSelectedOption(const std::string &option);
	int GetSelectedIndex() const;
	void SetSelectedIndex(const int index);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	sigc::signal<void,unsigned int,const std::string &> onOptionSelected;

protected:
	friend class Context;
	DropDown(Context *context);

	void HandleClick();
	void HandleMouseOver();
	void HandleMouseOut();

private:
	Background *m_container;
	Label *m_label;
	Icon *m_icon;

	bool HandlePopupClick();
<<<<<<< HEAD
	void TogglePopup();

	RefCountedPtr<List> m_popup;
	bool m_popupActive;
=======

	RefCountedPtr<List> m_popup;
	bool m_popupWantToggle;
	bool m_popupActive;

	sigc::connection m_contextClickCon;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
};

}

#endif
