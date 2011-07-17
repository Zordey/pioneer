#ifndef _CHATFORM_H
#define _CHATFORM_H

#include "gui/Gui.h"


class ChatForm : public Gui::Fixed {
public:
	enum ChatFormType { BLANK, FACE };

	virtual ChatFormType GetType() const = 0;

protected:
	ChatForm(float w, float h) : Gui::Fixed(w, h) {}
};


class FaceChatForm : public ChatForm {
public:
	virtual ChatForm::ChatFormType GetType() const { return ChatForm::FACE; }

	virtual int GetFaceFlags() const { return m_faceFlags; }
	virtual unsigned long GetFaceSeed() const { return m_faceSeed; }
	
	void SetFaceFlags(int flags) { m_faceFlags = flags; }
	void SetFaceSeed(unsigned int seed) { m_faceSeed = seed; }

protected:
	FaceChatForm() : ChatForm(470,400), m_faceFlags(0), m_faceSeed(-1UL) {}

private:
	int m_faceFlags;
	unsigned int m_faceSeed;
};


#endif
