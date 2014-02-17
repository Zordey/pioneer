<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#include "libs.h"
#include "Lang.h"
#include "FileSystem.h"
#include "StringRange.h"
#include "utils.h"
#include "text/TextSupport.h"
<<<<<<< HEAD
=======
#include "json/json.h"
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#include <map>
#include <set>

namespace Lang {

<<<<<<< HEAD
// XXX we're allocating a KB for each translatable string
// that's... not very nice (though I guess it "doesn't matter" with virtual memory and multi-GB of RAM)
static const int STRING_RECORD_SIZE = 1024;
#define DECLARE_STRING(x) char x[STRING_RECORD_SIZE];
#include "LangStrings.inc.h"
#undef DECLARE_STRING

}

namespace {

// declaring value type as const char* so that we can give out a const reference to the real
// token map without allowing external code to modify token text
// unfortunately, this means we don't have write access internally either,
// so we have to const_cast<> to initialise the token values.
// this could be avoided by using a custom class for the value type
// (or std::string, but then we'd be changing the way translated text is stored)
typedef std::map<std::string, const char*> token_map;
static token_map s_token_map;
static std::string s_current_language("English");

static struct init_string_helper_class {
	init_string_helper_class() {
#define DECLARE_STRING(x)  s_token_map.insert(std::make_pair(#x, Lang::x)); Lang::x[0] = '\0';
#include "LangStrings.inc.h"
#undef DECLARE_STRING
	}
} init_string_helper;

=======
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
static bool ident_head(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_');
}

static bool ident_tail(char c)
{
	return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_');
}

<<<<<<< HEAD
static bool valid_token(StringRange tok)
{
	if (tok.Empty()) return false;
	if (!ident_head(tok[0])) return false;
	for (const char *c = tok.begin + 1; c != tok.end; ++c) {
		if (!ident_tail(*c)) return false;
	}
	return true;
}

// returns 0 on success, or a line number on error
static int valid_utf8(StringRange data)
{
	const char *c = data.begin;
	int line = 1;
	while (c != data.end) {
		Uint32 chr;
		int n = Text::utf8_decode_char(&chr, c);
		if (!n) return line;
		if (chr == '\n') ++line;
		c += n;
	}
	return 0;
}

struct StringFileParser {
public:
	StringFileParser(const std::string &filename, StringRange range);

	bool Finished() const { return m_data.Empty() && m_token.Empty(); }
	void Next();

	const std::string &GetFileName() const { return m_filename; }

	StringRange GetToken() const { return m_token; }
	int GetTokenLineNumber() const { return m_tokenLine; }
	StringRange GetText() const { return m_text; }
	int GetTextLineNumber() const { return m_textLine; }

	const std::string &GetAdjustedText() const { return m_adjustedText; }

private:
	StringRange NextLine();
	void SkipBlankLines();
	void ScanText();

	std::string m_filename;
	StringRange m_data;
	StringRange m_token;
	StringRange m_text;
	int m_lineNo;
	int m_tokenLine;
	int m_textLine;
	std::string m_adjustedText;
};

StringFileParser::StringFileParser(const std::string &filename, StringRange range):
	m_filename(filename), m_data(range), m_lineNo(0), m_tokenLine(-1), m_textLine(-1)
{
	assert(m_data.begin && m_data.end);
	m_data = m_data.StripUTF8BOM();
	SkipBlankLines();
	Next();
}

void StringFileParser::Next()
{
	if (!m_data.Empty()) {
		m_token = NextLine();
		m_tokenLine = m_lineNo;
		m_text = NextLine();
		m_textLine = m_lineNo;
		SkipBlankLines();

		if (!m_text.Empty() && (m_text[0] == '"') && (m_text[m_text.Size()-1] == '"')) {
			++m_text.begin;
			--m_text.end;
		}

		// adjust for escaped newlines
		{
			m_adjustedText.clear();
			m_adjustedText.reserve(m_text.Size());

			const char *end1 = (m_text.end - 1);
			const char *c;
			for (c = m_text.begin; c < end1; ++c) {
				if (c[0] == '\\' && c[1] == 'n') {
					++c;
					m_adjustedText += '\n';
				} else {
					m_adjustedText += *c;
				}
			}
			if (c != m_text.end) {
				m_adjustedText += *c++;
			}
			assert(c == m_text.end);
		}

		if (!valid_token(m_token)) {
			fprintf(stderr, "Invalid token '%.*s' at %s:%d\n", int(m_token.Size()), m_token.begin, m_filename.c_str(), m_tokenLine);
		}

		if (m_token.Empty()) {
			fprintf(stderr, "Blank token at %s:%d\n", m_filename.c_str(), m_tokenLine);
		}

		if (m_text.Empty()) {
			fprintf(stderr, "Blank string for token '%.*s' (at %s:%d)\n", int(m_token.Size()), m_token.begin, m_filename.c_str(), m_textLine);
		}
	} else {
		m_token.begin = m_token.end = 0;
		m_tokenLine = m_lineNo;
		m_text.begin = m_text.end = 0;
		m_textLine = m_lineNo;
		m_adjustedText.clear();
	}
}

StringRange StringFileParser::NextLine()
{
	if (!m_data.Empty()) {
		++m_lineNo;
		StringRange line = m_data.ReadLine();
		return line.StripSpace();
	} else
		return m_data;
}

void StringFileParser::SkipBlankLines()
{
	if (!m_data.Empty()) {
		StringRange line;
		// skip empty lines and comments
		while (!m_data.Empty() && (line.Empty() || line[0] == '#')) line = NextLine();
		--m_lineNo;
		m_data.begin = line.begin;
	}
}

static void ResetStringData()
{
	const char *badstring = "<badstring>";
	size_t sz = strlen(badstring) + 1;
#define DECLARE_STRING(x) memcpy(Lang::x, badstring, sz);
#include "LangStrings.inc.h"
#undef DECLARE_STRING
}

static std::vector<std::string> EnumAvailableLanguages()
{
	std::vector<std::string> languages;

	for (FileSystem::FileEnumerator files(FileSystem::gameDataFiles, "lang"); !files.Finished(); files.Next()) {
		assert(files.Current().IsFile());
		const std::string &path = files.Current().GetPath();
		if (ends_with(path, ".txt")) {
			const std::string name = files.Current().GetName();
			languages.push_back(name.substr(0, name.size() - 4));
=======
static bool valid_token(const std::string &token)
{
	if (token.empty()) return false;
	if (!ident_head(token[0])) return false;
	for (unsigned int i = 1; i < token.size(); i++)
		if (!ident_tail(token[i])) return false;
	return true;
}

bool Resource::Load()
{
	if (m_loaded)
		return true;

	Json::Reader reader;
	Json::Value data;

	std::string filename = "lang/" + m_name + "/" + m_langCode + ".json";
	RefCountedPtr<FileSystem::FileData> fd = FileSystem::gameDataFiles.ReadFile(filename);
	if (!fd) {
		fprintf(stderr, "couldn't open language file '%s'\n", filename.c_str());
		return false;
	}

	if (!reader.parse(fd->GetData(), fd->GetData()+fd->GetSize(), data)) {
		fprintf(stderr, "couldn't read language file '%s': %s\n", filename.c_str(), reader.getFormattedErrorMessages().c_str());
		return false;
	}

	fd.Reset();

	for (Json::Value::iterator i = data.begin(); i != data.end(); ++i) {
		const std::string token(i.key().asString());
		if (token.empty()) {
			fprintf(stderr, "%s: found empty token, skipping it\n", filename.c_str());
			continue;
		}
		if (!valid_token(token)) {
			fprintf(stderr, "%s: invalid token '%s', skipping it\n", filename.c_str(), token.c_str());
			continue;
		}

		Json::Value message((*i).get("message", Json::nullValue));
		if (message.isNull()) {
			fprintf(stderr, "%s: no 'message' key for token '%s', skipping it\n", filename.c_str(), token.c_str());
			continue;
		}

		if (!message.isString()) {
			fprintf(stderr, "%s: value for token '%s' is not a string, skipping it\n", filename.c_str(), token.c_str());
			continue;
		}

		std::string text(message.asString());
		if (text.empty()) {
			fprintf(stderr, "%s: empty value for token '%s', skipping it\n", filename.c_str(), token.c_str());
			continue;
		}

		// extracted quoted string
		if (text[0] == '"' && text[text.size()-1] == '"')
			text = text.substr(1, text.size()-2);

		// adjust for escaped newlines
		{
			std::string adjustedText;
			adjustedText.reserve(text.size());

			unsigned int ii;
			for (ii = 0; ii < text.size()-1; ii++) {
				const char *c = &text[ii];
				if (c[0] == '\\' && c[1] == 'n') {
					ii++;
					adjustedText += '\n';
				}
				else
					adjustedText += *c;
			}
			if (ii != text.size())
				adjustedText += text[ii++];
			assert(ii == text.size());
			text = adjustedText;
		}

		m_strings[token] = text;
	}

	m_loaded = true;
	return true;
}

const std::string &Resource::Get(const std::string &token) const
{
	std::map<std::string,std::string>::const_iterator i = m_strings.find(token);
	if (i == m_strings.end()) {
		static const std::string empty;
		return empty;
	}
	return (*i).second;
}

std::vector<std::string> Resource::GetAvailableLanguages(const std::string &resourceName)
{
	std::vector<std::string> languages;

	for (FileSystem::FileEnumerator files(FileSystem::gameDataFiles, "lang/" + resourceName); !files.Finished(); files.Next()) {
		assert(files.Current().IsFile());
		const std::string &path = files.Current().GetPath();
		if (ends_with_ci(path, ".json")) {
			const std::string name = files.Current().GetName();
			languages.push_back(name.substr(0, name.size() - 5));
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		}
	}

	return languages;
}

<<<<<<< HEAD
=======

// XXX we're allocating a KB for each translatable string
// that's... not very nice (though I guess it "doesn't matter" with virtual memory and multi-GB of RAM)
static const int STRING_RECORD_SIZE = 1024;
#define DECLARE_STRING(x) char x[STRING_RECORD_SIZE];
#include "LangStrings.inc.h"
#undef DECLARE_STRING

//
// declaring value type as const char* so that we can give out a const reference to the real
// token map without allowing external code to modify token text
// unfortunately, this means we don't have write access internally either,
// so we have to const_cast<> to initialise the token values.
// this could be avoided by using a custom class for the value type
// (or std::string, but then we'd be changing the way translated text is stored)
typedef std::map<std::string, const char*> token_map;
static token_map s_token_map;

static struct init_string_helper_class {
	init_string_helper_class() {
#define DECLARE_STRING(x)  s_token_map.insert(std::make_pair(#x, Lang::x)); Lang::x[0] = '\0';
#include "LangStrings.inc.h"
#undef DECLARE_STRING
	}
} init_string_helper;


>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
static void copy_string(char *buf, const char *str, size_t strsize, size_t bufsize)
{
	size_t sz = std::min(strsize, bufsize-1);
	memcpy(buf, str, sz);
	buf[sz] = '\0';
}

<<<<<<< HEAD
} // anonymous namespace

namespace Lang {

bool LoadStrings(const std::string &lang)
{
	int errline;
	std::set<std::string> seen, missing;

	ResetStringData();

	std::string filename = "lang/English.txt";
	RefCountedPtr<FileSystem::FileData> english_data = FileSystem::gameDataFiles.ReadFile(filename);
	if (!english_data) {
		fprintf(stderr, "couldn't open string file '%s'\n", filename.c_str());
		return false;
	}

	errline = valid_utf8(english_data->AsStringRange());
	if (errline) {
		fprintf(stderr, "invalid UTF-8 code in line %d of '%s'\n", errline, filename.c_str());
		return false;
	}

	seen.clear();
	for (StringFileParser parser(filename, english_data->AsStringRange()); !parser.Finished(); parser.Next()) {
		const std::string token = parser.GetToken().ToString();
		token_map::iterator it = s_token_map.find(token);
		if (it != s_token_map.end()) {
			seen.insert(token);
			const std::string &text = parser.GetAdjustedText();
			if (text.size() >= size_t(STRING_RECORD_SIZE))
				fprintf(stderr, "WARNING: language text is too long -- it will be cut off!\n");
			// XXX const_cast is ugly, but see note for declaration of tokens map
			char *record = const_cast<char*>(it->second);
			copy_string(record, text.c_str(), text.size(), STRING_RECORD_SIZE);
		} else {
			fprintf(stderr, "unknown language token '%s' at %s:%d\n", token.c_str(), parser.GetFileName().c_str(), parser.GetTokenLineNumber());
		}
	}

	english_data.Reset();

	if (seen.size() != s_token_map.size()) {
		fprintf(stderr, "string file '%s' has missing tokens:\n", filename.c_str());
		for (token_map::iterator it = s_token_map.begin(); it != s_token_map.end(); ++it) {
			if (!seen.count(it->first)) {
				fprintf(stderr, "  %s\n", it->first.c_str());
				missing.insert(it->first);
			}
		}
	}

	if (lang == "English")
		return (seen.size() == s_token_map.size());

	filename = "lang/" + lang + ".txt";
	RefCountedPtr<FileSystem::FileData> lang_data = FileSystem::gameDataFiles.ReadFile(filename);
	if (!lang_data) {
		fprintf(stderr, "couldn't open string file '%s'\n", filename.c_str());
		return false;
	}

	errline = valid_utf8(lang_data->AsStringRange());
	if (errline) {
		fprintf(stderr, "invalid UTF-8 code in line %d of '%s'\n", errline, filename.c_str());
		return false;
	}

	seen.clear();
	for (StringFileParser parser(filename, lang_data->AsStringRange()); !parser.Finished(); parser.Next()) {
		const std::string token = parser.GetToken().ToString();
		token_map::iterator it = s_token_map.find(token);
		if (it != s_token_map.end()) {
			seen.insert(token);
			const std::string &text = parser.GetAdjustedText();
			if (text.size() >= size_t(STRING_RECORD_SIZE))
				fprintf(stderr, "WARNING: language text is too long -- it will be cut off!\n");
			// XXX const_cast is ugly, but see note for declaration of tokens map
			char *record = const_cast<char*>(it->second);
			copy_string(record, text.c_str(), text.size(), STRING_RECORD_SIZE);
		} else {
			fprintf(stderr, "unknown language token '%s' at %s:%d\n", token.c_str(), parser.GetFileName().c_str(), parser.GetTokenLineNumber());
		}
	}

	if (seen.size() != s_token_map.size()) {
		fprintf(stderr, "string file '%s' has missing tokens:\n", filename.c_str());
		for (token_map::iterator it = s_token_map.begin(); it != s_token_map.end(); ++it) {
			if (!seen.count(it->first)) {
				fprintf(stderr, "  %s\n", it->first.c_str());
			} else {
				missing.erase(it->first);
			}
		}
	}

	if (!missing.empty()) {
		fprintf(stderr, "no strings found for the following tokens:\n");
		for (std::set<std::string>::iterator it = missing.begin(); it != missing.end(); ++it) {
			fprintf(stderr, "  %s\n", it->c_str());
		}
		return false;
	}

	s_current_language = lang;

	return true;
}

const std::vector<std::string> &GetAvailableLanguages()
{
	static std::vector<std::string> languages = EnumAvailableLanguages();
	return languages;
}

const std::map<std::string, const char*> &GetDictionary()
{
    return s_token_map;
}

const std::string &GetCurrentLanguage()
{
	return s_current_language;
=======
static Resource s_coreResource("core", "<unknown>");

void MakeCore(Resource &res)
{
	assert(res.GetName() == "core");

	res.Load();

	for (token_map::iterator i = s_token_map.begin(); i != s_token_map.end(); ++i) {
		const std::string &token = i->first;
		std::string text = res.Get(token);

		if (text.empty()) {
			fprintf(stderr, "%s/%s: token '%s' not found\n", res.GetName().c_str(), res.GetLangCode().c_str(), token.c_str());
			text = token;
		}

		if (text.size() > size_t(STRING_RECORD_SIZE)) {
			fprintf(stderr, "%s/%s: text for token '%s' is too long and will be truncated\n", res.GetName().c_str(), res.GetLangCode().c_str(), token.c_str());
			text.resize(STRING_RECORD_SIZE);
		}

		// const_cast so we can set the string, see above
		char *record = const_cast<char*>(i->second);
		copy_string(record, text.c_str(), text.size(), STRING_RECORD_SIZE);
	}

	s_coreResource = res;
}

const Resource &GetCore()
{
	return s_coreResource;
}

static std::map<std::string,Resource> m_cachedResources;

Resource GetResource(const std::string &name, const std::string &langCode)
{
	auto key = name + ":" + langCode;

	auto i = m_cachedResources.find(key);
	if (i != m_cachedResources.end())
		return i->second;

	Lang::Resource res = Lang::Resource(name, langCode);
	bool loaded = res.Load();
	if (!loaded) {
		if (langCode != "en") {
			fprintf(stderr, "couldn't load language resource %s/%s, trying %s/en\n", name.c_str(), langCode.c_str(), name.c_str());
			res = Lang::Resource(name, "en");
			loaded = res.Load();
			key = name + ":" + "en";
		}
		if (!loaded)
			fprintf(stderr, "couldn't load language resource %s/en\n", name.c_str());
	}

	if (loaded)
		m_cachedResources.insert(std::make_pair(key, res));

	return res;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
}

} // namespace Lang
