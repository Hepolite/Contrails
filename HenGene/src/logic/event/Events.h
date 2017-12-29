
#pragma once

#include "ui/Mouse.h"
#include "ui/Keyboard.h"

#include <glm/vec2.hpp>

namespace logic
{
	namespace event
	{
		struct DisplayClose {};			// User clicks display [x] button
		struct DisplaySwitchIn {};		// User focuses the display
		struct DisplaySwitchOut {};		// User focuses some other window
		struct DisplayResize			// User resizes the display
		{
			const glm::ivec2 m_size;			// New size of the display
		};

		// ...

		struct KeyPress					// User press a key on the keyboard
		{
			const int m_key;					// The key the user pressed
			const unsigned int m_modifiers;		// The modifiers that were active (i.e. shift, ctrl, etc.)
		};
		struct KeyRelease				// User releases a key on the keyboard
		{
			const int m_key;					// The key the user released
			const unsigned int m_modifiers;		// The modifiers that were active (i.e. shift, ctrl, etc.)
		};
		struct KeyUnichar				// User inputs a character
		{
			const int m_unichar;				// The character the user typed
			const unsigned int m_modifiers;		// The modifiers that were active (i.e. shift, ctrl, etc.)
		};

		// ...

		struct MouseEnterDisplay {};	// User moves cursor into display
		struct MouseLeaveDisplay {};	// User moves cursor out of display
		struct MousePress				// User press mouse button inside the display
		{
			const ui::mouse::Button m_button;	// The button the user pressed
			const float m_pressure;				// The pressure the user applied on the button
			const glm::vec2 m_pos;				// The position the user clicked
			const glm::vec2 m_scroll;			// The current scroll position when the user clicked
		};
		struct MouseRelease				// User releases mouse button inside the display
		{
			const ui::mouse::Button m_button;	// The button the user pressed
			const float m_pressure;				// The pressure the user applied on the button
			const glm::vec2 m_pos;				// The position the user clicked
			const glm::vec2 m_scroll;			// The current scroll position when the user clicked
		};
		struct MouseMove				// User moves cursor inside the display
		{
			const glm::vec2 m_pos;				// The current position of the cursor
			const glm::vec2 m_posDelta;			// The change in the position of the cursor
			const glm::vec2 m_scroll;			// The current scroll position of the cursor
			const glm::vec2 m_scrollDelta;		// The change in the scroll position of the cursor
		};
	}
}