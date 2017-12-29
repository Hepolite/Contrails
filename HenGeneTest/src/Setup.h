
#pragma once

#include "core/allegro/Allegro.h"
#include "ui/Display.h"

namespace setup
{
	struct Context
	{
		core::allegro::Allegro m_allegro;
		ui::Display m_display{ {}, false };
	};
}