
#pragma once

#include "ui/gui/detail/Data.h"

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
			Link m_link;
			Position m_position;
			Size m_size;
			State m_state;
		};
	}
}