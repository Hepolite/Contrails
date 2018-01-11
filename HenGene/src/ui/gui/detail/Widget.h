
#pragma once

#include "ui/gui/detail/Data.h"

#include <string>

namespace ui
{
	namespace gui
	{
		struct Widget
		{
			Activation m_activation;
			Assets m_assets;
			Border m_border;
			Family m_family;
			Group m_group;
			Header m_header;
			Link m_link;
			Logic m_logic;
			Position m_position;
			Render m_render;
			Size m_size;
			State m_state;
		};
	}
}