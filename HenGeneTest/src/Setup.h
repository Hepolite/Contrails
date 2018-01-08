
#pragma once

#include "render/allegro/Allegro.h"
#include "ui/Display.h"

namespace setup
{
	struct Context
	{
		render::allegro::Allegro m_allegro;
		ui::Display m_display{ {}, false };
	};
}