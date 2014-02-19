<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "GuiRadioGroup.h"
#include "GuiISelectable.h"

namespace Gui {
void RadioGroup::Add(ISelectable *b)
{
	b->onSelect.connect(sigc::bind(sigc::mem_fun(*this, &RadioGroup::OnSelected), b));
	m_members.push_back(b);
}

void RadioGroup::OnSelected(ISelectable *b)
{
	for(std::list<ISelectable*>::iterator i = m_members.begin(); i != m_members.end(); ++i) {
		if (*i != b) {
			(*i)->SetSelected(false);
		}
	}
}

void RadioGroup::SetSelected(int member_idx)
{
	int idx = 0;
	for(std::list<ISelectable*>::iterator i = m_members.begin(); i != m_members.end(); ++i, ++idx) {
		(*i)->SetSelected(idx == member_idx);
	}
}

}

