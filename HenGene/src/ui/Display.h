
#pragma once

#include <allegro5/display.h>
#include <glm/vec2.hpp>

namespace ui
{
	class Display
	{
	public:
		Display() = delete;
		Display(const glm::ivec2 & size, bool fullscreen);
		Display(const Display &) = delete;
		Display(Display && other);
		~Display();

		Display & operator=(const Display &) = delete;
		Display & operator=(Display && other);

		glm::ivec2 getSize() const;
		bool isFullscreen() const;

		inline auto getHandle() const { return m_handle; }

	private:
		ALLEGRO_DISPLAY * m_handle = nullptr;
	};
}