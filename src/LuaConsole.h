<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUACONSOLE_H
#define _LUACONSOLE_H

#include "LuaManager.h"
#include "ui/Widget.h"
#include "RefCounted.h"
#include <deque>

namespace UI {
	class TextEntry;
	class MultiLineText;
	class Scroller;
}

class LuaConsole {
public:
	LuaConsole();
	virtual ~LuaConsole();

	void Toggle();

	bool IsActive() const { return m_active; }
	void AddOutput(const std::string &line);

	static void Register();
private:
<<<<<<< HEAD
	bool OnFilterKeys(const SDL_keysym*);
	void OnKeyPressed(const SDL_keysym*);
	void UpdateCompletion(const std::string & statement);
	void ExecOrContinue();
=======
	void OnKeyPressed(const SDL_Keysym*);
	void OnTextChanged();
	void UpdateCompletion(const std::string & statement);
	void ExecOrContinue();
	void RunAutoexec();
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755

	std::deque<std::string> m_statementHistory;
	std::string m_stashedStatement;
	int m_historyPosition;
	int m_nextOutputLine;

	std::string m_precompletionStatement;
	std::vector<std::string> m_completionList;
	unsigned int m_currentCompletion;
};

#endif /* _LUACONSOLE_H */
