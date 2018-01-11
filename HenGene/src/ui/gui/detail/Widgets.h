
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

			inline auto begin() { return m_widgets.begin(); }
			inline auto begin() const { return m_widgets.begin(); }
			inline auto end() { return m_widgets.end(); }
			inline auto end() const { return m_widgets.end(); }

		private:
			std::unordered_map<std::string, Widget> m_widgets{ { "", Widget{} } };
		};
	}
}