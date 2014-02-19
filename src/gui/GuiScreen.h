<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _GUISCREEN_H
#define _GUISCREEN_H

#include "Gui.h"
#include "FontCache.h"
#include "text/TextureFont.h"
#include "graphics/RenderState.h"
#include <list>
#include <stack>

namespace Graphics { class Renderer; }

namespace Gui {
	class Screen {
	public:
		static void Init(Graphics::Renderer *renderer, int real_width, int real_height, int ui_width, int ui_height);
		static void Uninit();
		static void Draw();
		static void AddBaseWidget(Widget *w, int x, int y);
		static void RemoveBaseWidget(Widget *w);
		static void OnMouseMotion(SDL_MouseMotionEvent *e);
		static void OnClick(SDL_MouseButtonEvent *e);
<<<<<<< HEAD
		static void OnKeyDown(const SDL_keysym *sym);
		static void OnKeyUp(const SDL_keysym *sym);
=======
		static void OnKeyDown(const SDL_Keysym *sym);
		static void OnKeyUp(const SDL_Keysym *sym);
		static void OnTextInput(const SDL_TextInputEvent *e);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		static void EnterOrtho();
		static void LeaveOrtho();
		static int GetWidth() { return width; }
		static int GetHeight() { return height; }
		// gluProject but fixes UI/screen size mismatch
		static bool Project(const vector3d &in, vector3d &out);
<<<<<<< HEAD
		friend void Widget::SetShortcut(SDLKey key, SDLMod mod);
=======
		friend void Widget::SetShortcut(SDL_Keycode key, SDL_Keymod mod);
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		friend Widget::~Widget();
		static bool IsBaseWidget(const Widget *);
		static void GetCoords2Pixels(float scale[2]) {
			scale[0] = fontScale[0];
			scale[1] = fontScale[1];
		}
		static const float* GetCoords2Pixels() { return fontScale; }
		static void SetFocused(Widget *w, bool enableKeyRepeat = false);
		static void ClearFocus();
		static bool IsFocused(Widget *w) {
			return w == focusedWidget;
		}

		static void PushFont(RefCountedPtr<Text::TextureFont> font) { s_fontStack.push(font); }
		static void PushFont(std::string name) { PushFont(s_fontCache.GetTextureFont(name)); }
		static void PopFont() { s_fontStack.pop(); };
		static RefCountedPtr<Text::TextureFont> GetFont() { return s_fontStack.size() ? s_fontStack.top() : s_defaultFont; }
		static RefCountedPtr<Text::TextureFont> GetDefaultFont() { return s_defaultFont; }

		static float GetFontHeight(Text::TextureFont *font = 0);
		static float GetFontDescender(Text::TextureFont *font = 0);

		static void RenderString(const std::string &s, float xoff, float yoff, const Color &color = Color::WHITE, Text::TextureFont *font = 0);
		static void MeasureString(const std::string &s, float &w, float &h, Text::TextureFont *font = 0);
		static int PickCharacterInString(const std::string &s, float x, float y, Text::TextureFont *font = 0);
		static void MeasureCharacterPos(const std::string &s, int charIndex, float &x, float &y, Text::TextureFont *font = 0);
		static void RenderMarkup(const std::string &s, const Color &color = Color::WHITE, Text::TextureFont *font = 0);

		static Graphics::Renderer *GetRenderer() { return s_renderer; }

		static Graphics::RenderState *alphaBlendState;
		static Graphics::Material* flatColorMaterial;

	private:
		static void AddShortcutWidget(Widget *w);
		static void RemoveShortcutWidget(Widget *w);
		static void SDLEventCoordToScreenCoord(int sdlev_x, int sdlev_y, float *x, float *y);

		static bool initted;
		static int width, height;
		static int realWidth, realHeight;
		static float invRealWidth, invRealHeight;
		static std::list<Widget*> kbshortcut_widgets;
		static std::list<Widget*> mouseHoveredWidgets;
		static float fontScale[2];
		static Gui::Fixed *baseContainer;
		static Gui::Widget *focusedWidget;
		static void OnDeleteFocusedWidget();
<<<<<<< HEAD
		static GLdouble modelMatrix[16];
		static GLdouble projMatrix[16];
=======
		static matrix4x4f modelMatrix;
		static matrix4x4f projMatrix;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		static GLint viewport[4];

		static FontCache s_fontCache;
		static std::stack< RefCountedPtr<Text::TextureFont> > s_fontStack;
		static RefCountedPtr<Text::TextureFont> s_defaultFont;

		static Graphics::Renderer *s_renderer;
	};
}

#endif /* _GUISCREEN_H */
