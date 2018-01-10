
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
			void onEvent(const logic::event::KeyPress & event);
			void onEvent(const logic::event::KeyRelease & event);
			void onEvent(const logic::event::MousePress & event);
			void onEvent(const logic::event::MouseRelease & event);

			void process();
			void render() const;

		private:
			Widgets m_widgets;
			logic::script::Script m_script;
		};
	}
}