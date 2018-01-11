
#pragma once

#include "ui/gui/detail/Widget.h"
#include "ui/gui/detail/Widgets.h"

#include <glm/vec2.hpp>

namespace ui
{
	namespace gui
	{
		class Processor
		{
		public:
			Processor() = delete;
			Processor(const Widgets & widgets, Widget & widget);
			Processor(const Processor &) = default;
			Processor(Processor &&) = default;
			virtual ~Processor() = default;

			Processor & operator=(const Processor &) = default;
			Processor & operator=(Processor &&) = default;

			virtual void operator()(const glm::vec2 & pos);

			const Widget & getParent() const;
			const Widget & getChild(const std::string & name) const;

			glm::vec2 calculatePosition() const;
			glm::vec2 calculateSize() const;

		protected:
			const Widgets * m_widgets = nullptr;
			Widget * m_widget = nullptr;
		};
	}
}