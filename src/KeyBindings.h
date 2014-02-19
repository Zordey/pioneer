<<<<<<< HEAD
// Copyright © 2008-2013 Pioneer Developers. See AUTHORS.txt for details
=======
// Copyright © 2008-2014 Pioneer Developers. See AUTHORS.txt for details
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef KEYBINDINGS_H
#define KEYBINDINGS_H

#include "libs.h"
#include <iosfwd>

namespace KeyBindings {
	enum Type {
<<<<<<< HEAD
=======
		BINDING_DISABLED,
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
		KEYBOARD_KEY,
		JOYSTICK_BUTTON,
		JOYSTICK_HAT
	};

	struct KeyBinding {
<<<<<<< HEAD
		Type type;

		union {
			struct {
				SDLKey key;
				SDLMod mod;
			} keyboard;

			struct {
				Uint8 joystick;
				Uint8 button;
			} joystickButton;

			struct {
				Uint8 joystick;
				Uint8 hat;
				Uint8 direction;
			} joystickHat;
		} u;

		std::string Description() const;
		bool Matches(const SDL_keysym *sym) const;

		static KeyBinding keyboardBinding(SDLKey key, SDLMod mod);
	};

	struct KeyAction {
		KeyBinding binding;

		sigc::signal<void> onPress;
		sigc::signal<void> onRelease;

		bool IsActive() const;
		void CheckSDLEventAndDispatch(const SDL_Event *event);
	};

=======
		public:
			// constructors
			static bool FromString(const char *str, KeyBinding &binding);
			static KeyBinding FromString(const char *str);
			static KeyBinding FromKeyMod(SDL_Keycode key, SDL_Keymod mod);
			static KeyBinding FromJoystickButton(Uint8 joystick, Uint8 button);
			static KeyBinding FromJoystickHat(Uint8 joystick, Uint8 hat, Uint8 direction);

			KeyBinding(): type(BINDING_DISABLED) {
				u.keyboard.key = SDLK_UNKNOWN;
				u.keyboard.mod = KMOD_NONE;
			}

			std::string ToString() const; // for serialisation
			std::string Description() const; // for display to the user

			bool IsActive() const;
			bool Matches(const SDL_Keysym *sym) const;
			bool Matches(const SDL_JoyButtonEvent *joy) const;
			bool Matches(const SDL_JoyHatEvent *joy) const;

			void Clear() { memset(this, 0, sizeof(*this)); }

			bool Enabled() const { return (type != BINDING_DISABLED); }

			friend std::ostream &operator<<(std::ostream &oss, const KeyBinding &kb);

		private:
			Type type;
			union {
				struct {
					SDL_Keycode key;
					SDL_Keymod mod;
				} keyboard;

				struct {
					Uint8 joystick;
					Uint8 button;
				} joystickButton;

				struct {
					Uint8 joystick;
					Uint8 hat;
					Uint8 direction;
				} joystickHat;
			} u;
	};

	struct KeyAction {
		KeyBinding binding1;
		KeyBinding binding2;

		sigc::signal<void> onPress;
		sigc::signal<void> onRelease;

		void SetFromString(const char *str);
		std::string ToString() const;

		bool IsActive() const;
		void CheckSDLEventAndDispatch(const SDL_Event *event);

		bool Matches(const SDL_Keysym *sym) const;
	};

>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	enum AxisDirection {
		POSITIVE,
		NEGATIVE
	};

	struct AxisBinding {
		Uint8 joystick;
		Uint8 axis;
		AxisDirection direction;

		AxisBinding();
		AxisBinding(Uint8 joystick, Uint8 axis, AxisDirection direction);
		float GetValue();
		std::string Description() const;
<<<<<<< HEAD
=======

		void Clear() {
			memset(this, 0, sizeof(*this));
		}

		static bool FromString(const char *str, AxisBinding &binding);
		static AxisBinding FromString(const char *str);
		std::string ToString() const;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
	};

	struct BindingPrototype {
		const char *label, *function;
		KeyAction *kb;
		AxisBinding *ab;
	};

	void InitBindings();
	void UpdateBindings();

<<<<<<< HEAD
	bool KeyBindingFromString(const std::string &str, KeyBinding *kb);
	KeyBinding KeyBindingFromString(const std::string &str);
	std::string KeyBindingToString(const KeyBinding &kb);
	bool AxisBindingFromString(const std::string &str, AxisBinding *ab);
	AxisBinding AxisBindingFromString(const std::string &str);
	std::string AxisBindingToString(const AxisBinding &ab);

	void DispatchSDLEvent(const SDL_Event *event);

#define KEY_BINDING(name,a,b,c) extern KeyAction name;
=======
	void DispatchSDLEvent(const SDL_Event *event);

#define KEY_BINDING(name,a,b,c,d) extern KeyAction name;
>>>>>>> 16a7bbac5db66645663dbc7deb29f65b5d4fe755
#define AXIS_BINDING(name,a,b,c) extern AxisBinding name;
#include "KeyBindings.inc.h"

#define BINDING_PAGE(name) extern const BindingPrototype BINDING_PROTOS_ ## name[];
#include "KeyBindings.inc.h"

} // namespace KeyBindings

#endif /* KEYBINDINGS_H */
