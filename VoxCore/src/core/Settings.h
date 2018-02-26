
#pragma once

#include <glm/vec2.hpp>

namespace core
{
	struct Settings
	{
		struct Display
		{
			glm::ivec2 m_size{ 640, 480 };
			bool m_fullscreen = false;
		} m_display;

		struct MainLoop
		{
			double m_fps = 60.0;
			double m_ups = 60.0;
		} m_loop;
	};
}