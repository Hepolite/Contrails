
#pragma once

#include "render/allegro/Allegro.h"
#include "ui/Display.h"

#include <memory>

namespace
{
	std::shared_ptr<render::allegro::Allegro> allegro;
	std::shared_ptr<ui::Display> display;
}

namespace setup
{
	struct Context
	{
		Context()
		{
			if (allegro == nullptr)
				allegro = std::make_shared<render::allegro::Allegro>();
			if (display == nullptr)
				display = std::make_shared<ui::Display>(glm::ivec2{ 640, 480 }, false);

			m_allegro = allegro;
			m_display = display;
		}

		std::shared_ptr<render::allegro::Allegro> m_allegro;
		std::shared_ptr<ui::Display> m_display;
	};
}