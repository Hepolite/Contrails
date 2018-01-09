
#pragma once

namespace ui { class Display; }

namespace setup
{
	struct Context
	{
		Context();

		ui::Display & getDisplay() const;
	};
}