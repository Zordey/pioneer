<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "NumberLabel.h"
#include "StringF.h"
<<<<<<< HEAD
=======
#include "Lang.h"
#include "utils.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

namespace UI {

NumberLabel::NumberLabel(Context *context, Format format) :
	Label(context, ""),
	m_format(format)
{
	SetValue(0.0);

	RegisterBindPoint("value", sigc::mem_fun(this, &NumberLabel::BindValue));
	RegisterBindPoint("valuePercent", sigc::mem_fun(this, &NumberLabel::BindValuePercent));
}

NumberLabel *NumberLabel::SetValue(double v)
{
	m_value = v;
	switch (m_format) {
		case FORMAT_NUMBER_2DP:
			SetText(to_string(v, "f.2"));
			break;

		case FORMAT_INTEGER:
			SetText(to_string(Uint32(v+0.5), "u"));
			break;

		case FORMAT_PERCENT:
			SetText(stringf("%0{f.2}%%", v*100.0));
			break;

		case FORMAT_PERCENT_INTEGER:
			SetText(stringf("%0{u}%%", Uint32(v*100.0+0.5)));
			break;

<<<<<<< HEAD
=======
		case FORMAT_MASS_TONNES:
			SetText(stringf(Lang::NUMBER_TONNES, formatarg("mass", v)));
			break;

		case FORMAT_MONEY:
			SetText(format_money(Sint64(v*100)));
			break;

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		default:
		case FORMAT_NUMBER:
			SetText(to_string(v, "f"));
			break;
	}

	return this;
}

void NumberLabel::BindValue(PropertyMap &p, const std::string &k)
{
<<<<<<< HEAD
	double v;
	p.Get(k, v);
	SetValue(Clamp(v, 0.0, 1.0));
=======
	double v = 0.0;
	p.Get(k, v);
	SetValue(v);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

void NumberLabel::BindValuePercent(PropertyMap &p, const std::string &k)
{
<<<<<<< HEAD
	double v;
=======
	double v = 0.0;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	p.Get(k, v);
	SetValue(Clamp(v, 0.0, 100.0)*0.01);
}

}
