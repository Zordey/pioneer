#ifndef _LUACONSOLE_H
#define _LUACONSOLE_H

#include "LuaManager.h"
#include "gui/GuiBox.h"

namespace Gui {
	class Label;
	class TextEntry;
}

class TextureFont;

class LuaConsole : public Gui::VBox {
public:
	explicit LuaConsole(int displayedOutputLines);
	virtual ~LuaConsole();

	bool isActive() const;
	Gui::TextEntry *textEntryField() const { return m_entryField; }
	void addOutput(const std::string &line);

	static void Register();
private:
	bool onFilterKeys(const SDL_keysym*);
	void onKeyPressed(const SDL_keysym*);

	void execOrContinue();

	std::vector<std::string> m_statementHistory;
	Gui::TextEntry *m_entryField;
	std::vector<Gui::Label*> m_outputLines;
	int m_nextOutputLine;
	TextureFont *m_font;
	const int m_maxOutputLines;
};

#endif /* _LUACHATFORM_H */
