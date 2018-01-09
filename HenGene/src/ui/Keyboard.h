
#pragma once

#include <allegro5/keycodes.h>
#include <string>

namespace ui
{
	namespace keyboard
	{
		int nameToKey(const std::string & name);
		int nameToModifier(const std::string & name);
	}
}