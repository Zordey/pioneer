// Copyright © 2008-2012 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _UI_MULTILINETEXT_H
#define _UI_MULTILINETEXT_H

#include "Widget.h"
#include "SmartPtr.h"

namespace UI {

class TextLayout;

class MultiLineText: public Widget {
public:
	virtual Point PreferredSize();
	virtual void Layout();
	virtual void Draw();

	MultiLineText *SetText(const std::string &text);
	MultiLineText *AppendText(const std::string &text);

protected:
	friend class Context;
	MultiLineText(Context *context, const std::string &text);

private:
	std::string m_text;
	ScopedPtr<TextLayout> m_layout;
	Point m_preferredSize;
};

}

#endif
