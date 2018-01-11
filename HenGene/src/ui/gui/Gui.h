
#pragma once

#include "logic/event/Events.h"
#include "logic/script/Script.h"
#include "ui/gui/detail/Widgets.h"

namespace ui
{
	namespace gui
	{
		class Gui
		{
		public:
			Gui() = default;
			Gui(const Gui &) = delete;
			Gui(Gui &&) = default;
			~Gui() = default;

			Gui & operator=(const Gui &) = delete;
			Gui & operator=(Gui &&) = default;

			void onEvent(const logic::event::DisplayResize & event);
			bool onEvent(const logic::event::KeyPress & event);
			void onEvent(const logic::event::KeyRelease & event);
			bool onEvent(const logic::event::MousePress & event);
			bool onEvent(const logic::event::MouseMove & event);
			void onEvent(const logic::event::MouseRelease & event);

			void process();
			void render() const;

			inline auto & getWidgets() { return m_widgets; }
			inline auto & getWidgets() const { return m_widgets; }
			inline auto & getScript() { return m_script; }
			inline auto & getScript() const { return m_script; }

		private:
			void process(Widget & widget, const glm::vec2 & offset);
			void render(const Widget & widget, const glm::vec2 & offset) const;

			bool onEvent(const logic::event::MousePress & event, Widget & widget);
			bool onEvent(const logic::event::MouseMove & event, Widget & widget, const glm::vec2 & offset);
			void onEvent(const logic::event::MouseRelease & event, Widget & widget);
			
			Widgets m_widgets;
			logic::script::Script m_script;
		};
	}
}