
#pragma once

#include "ui/gui/detail/Widget.h"

#include <string>
#include <unordered_map>

namespace ui
{
	namespace gui
	{
		class Widgets
		{
		public:
			Widget & create(const std::string & name, const std::string & parent = "");
			Widget & get(const std::string & name = "");
			const Widget & get(const std::string & name = "") const;
			bool has(const std::string & name) const;

		private:
			std::unordered_map<std::string, Widget> m_widgets{ { "", Widget{} } };
		};
	}
}