
#include "Keyboard.h"

#include <unordered_map>

namespace
{
	const std::unordered_map<std::string, int> namesToKeys = {
		{ "A", ALLEGRO_KEY_A },
		{ "B", ALLEGRO_KEY_B },
		{ "C", ALLEGRO_KEY_C },
		{ "D", ALLEGRO_KEY_D },
		{ "E", ALLEGRO_KEY_E },
		{ "F", ALLEGRO_KEY_F },
		{ "G", ALLEGRO_KEY_G },
		{ "H", ALLEGRO_KEY_H },
		{ "I", ALLEGRO_KEY_I },
		{ "J", ALLEGRO_KEY_J },
		{ "K", ALLEGRO_KEY_K },
		{ "L", ALLEGRO_KEY_L },
		{ "M", ALLEGRO_KEY_M },
		{ "N", ALLEGRO_KEY_N },
		{ "O", ALLEGRO_KEY_O },
		{ "P", ALLEGRO_KEY_P },
		{ "Q", ALLEGRO_KEY_Q },
		{ "R", ALLEGRO_KEY_R },
		{ "S", ALLEGRO_KEY_S },
		{ "T", ALLEGRO_KEY_T },
		{ "U", ALLEGRO_KEY_U },
		{ "V", ALLEGRO_KEY_V },
		{ "W", ALLEGRO_KEY_W },
		{ "X", ALLEGRO_KEY_X },
		{ "Y", ALLEGRO_KEY_Y },
		{ "Z", ALLEGRO_KEY_Z },
		{ "0", ALLEGRO_KEY_0 }, { "pad 0", ALLEGRO_KEY_PAD_0 },
		{ "1", ALLEGRO_KEY_1 }, { "pad 1", ALLEGRO_KEY_PAD_1 },
		{ "2", ALLEGRO_KEY_2 }, { "pad 2", ALLEGRO_KEY_PAD_2 },
		{ "3", ALLEGRO_KEY_3 }, { "pad 3", ALLEGRO_KEY_PAD_3 },
		{ "4", ALLEGRO_KEY_4 }, { "pad 4", ALLEGRO_KEY_PAD_4 },
		{ "5", ALLEGRO_KEY_5 }, { "pad 5", ALLEGRO_KEY_PAD_5 },
		{ "6", ALLEGRO_KEY_6 }, { "pad 6", ALLEGRO_KEY_PAD_6 },
		{ "7", ALLEGRO_KEY_7 }, { "pad 7", ALLEGRO_KEY_PAD_7 },
		{ "8", ALLEGRO_KEY_8 }, { "pad 8", ALLEGRO_KEY_PAD_8 },
		{ "9", ALLEGRO_KEY_9 }, { "pad 9", ALLEGRO_KEY_PAD_9 },
		{ "F1", ALLEGRO_KEY_F1 },
		{ "F2", ALLEGRO_KEY_F2 },
		{ "F3", ALLEGRO_KEY_F3 },
		{ "F4", ALLEGRO_KEY_F4 },
		{ "F5", ALLEGRO_KEY_F5 },
		{ "F6", ALLEGRO_KEY_F6 },
		{ "F7", ALLEGRO_KEY_F7 },
		{ "F8", ALLEGRO_KEY_F8 },
		{ "F9", ALLEGRO_KEY_F9 },
		{ "F10", ALLEGRO_KEY_F10 },
		{ "F11", ALLEGRO_KEY_F11 },
		{ "F12", ALLEGRO_KEY_F12 },
		{ "escape", ALLEGRO_KEY_ESCAPE },
		{ "~", ALLEGRO_KEY_TILDE },
		{ "-", ALLEGRO_KEY_MINUS },
		{ "=", ALLEGRO_KEY_EQUALS },
		{ "backspace", ALLEGRO_KEY_BACKSPACE },
		{ "tab", ALLEGRO_KEY_TAB },
		{ "{", ALLEGRO_KEY_OPENBRACE },
		{ "}", ALLEGRO_KEY_CLOSEBRACE },
		{ "enter", ALLEGRO_KEY_ENTER },
		{ ";", ALLEGRO_KEY_SEMICOLON },
		{ "\"", ALLEGRO_KEY_QUOTE },
		{ "\\", ALLEGRO_KEY_BACKSLASH },
		{ ",", ALLEGRO_KEY_COMMA },
		{ ".", ALLEGRO_KEY_FULLSTOP },
		{ "/", ALLEGRO_KEY_SLASH },
		{ "space", ALLEGRO_KEY_SPACE },
		{ "insert", ALLEGRO_KEY_INSERT },
		{ "delete", ALLEGRO_KEY_DELETE },
		{ "home", ALLEGRO_KEY_HOME },
		{ "end", ALLEGRO_KEY_END },
		{ "page up", ALLEGRO_KEY_PGUP },
		{ "page down", ALLEGRO_KEY_PGDN },
		{ "left", ALLEGRO_KEY_LEFT },
		{ "right", ALLEGRO_KEY_RIGHT },
		{ "up", ALLEGRO_KEY_UP },
		{ "down", ALLEGRO_KEY_DOWN },
		{ "pad /", ALLEGRO_KEY_PAD_SLASH },
		{ "pad *", ALLEGRO_KEY_PAD_ASTERISK },
		{ "pad -", ALLEGRO_KEY_PAD_MINUS },
		{ "pad +", ALLEGRO_KEY_PAD_PLUS },
		{ "pad delete", ALLEGRO_KEY_PAD_DELETE },
		{ "pad enter", ALLEGRO_KEY_PAD_ENTER },
		{ "print screen", ALLEGRO_KEY_PRINTSCREEN },
		{ "pause", ALLEGRO_KEY_PAUSE },
		{ "lshift", ALLEGRO_KEY_LSHIFT },
		{ "rshift", ALLEGRO_KEY_RSHIFT },
		{ "lctrl", ALLEGRO_KEY_LCTRL },
		{ "rctrl", ALLEGRO_KEY_RCTRL },
		{ "alt", ALLEGRO_KEY_ALT },
		{ "altgr", ALLEGRO_KEY_ALTGR },
		{ "lwin", ALLEGRO_KEY_LWIN },
		{ "rwin", ALLEGRO_KEY_RWIN },
		{ "menu", ALLEGRO_KEY_MENU },
		{ "scroll lock", ALLEGRO_KEY_SCROLLLOCK },
		{ "num lock", ALLEGRO_KEY_NUMLOCK },
		{ "caps lock", ALLEGRO_KEY_CAPSLOCK },
	};

	const std::unordered_map<std::string, int> namesToModifiers = {
		{ "shift", ALLEGRO_KEYMOD_SHIFT },
		{ "ctrl", ALLEGRO_KEYMOD_CTRL },
		{ "alt", ALLEGRO_KEYMOD_ALT },
	};
}

int ui::keyboard::nameToKey(const std::string & name)
{
	const auto it = namesToKeys.find(name);
	return it == namesToKeys.end() ? ALLEGRO_KEY_UNKNOWN : it->second;
}
int ui::keyboard::nameToModifier(const std::string & name)
{
	const auto it = namesToModifiers.find(name);
	return it == namesToModifiers.end() ? 0 : it->second;
}