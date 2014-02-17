<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LANG_H
#define _LANG_H

#include <vector>
#include <string>
#include <map>

namespace Lang {

<<<<<<< HEAD
bool LoadStrings(const std::string &lang);
const std::vector<std::string> &GetAvailableLanguages();
const std::map<std::string, const char*> &GetDictionary();
const std::string &GetCurrentLanguage();
=======
class Resource {
public:
	Resource(const std::string &name, const std::string &langCode) :
		m_name(name), m_langCode(langCode), m_loaded(false) {}

	const std::string &GetName()     const { return m_name; }
	const std::string &GetLangCode() const { return m_langCode; }

	bool Load();

	Uint32 GetNumStrings() const { return m_strings.size(); }

	const std::string &Get(const std::string &token) const;

	static std::vector<std::string> GetAvailableLanguages(const std::string &resourceName);

	typedef std::map<std::string,std::string>::const_iterator StringIterator;
	StringIterator Begin() const { return m_strings.begin(); }
	StringIterator End() const { return m_strings.end(); }


private:
	std::string m_name;
	std::string m_langCode;

	bool m_loaded;

	std::map<std::string,std::string> m_strings;
};
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

// declare all strings
#define DECLARE_STRING(x) extern char x[];
#include "LangStrings.inc.h"
#undef DECLARE_STRING

<<<<<<< HEAD
=======
void MakeCore(Resource &res);
const Resource &GetCore();

Resource GetResource(const std::string &name, const std::string &langCode);

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

#endif
