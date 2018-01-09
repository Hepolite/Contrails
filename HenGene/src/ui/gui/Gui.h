
#pragma once

#include "logic/event/Events.h"
#include "logic/script/Script.h"
#include "ui/gui/detail/Widget.h"

namespace ui
{
	namespace gui
	{
		class Gui
		{
			friend class GuiLoader;

		public:
			void onEvent(const logic::event::DisplayResize & event);
			void onEvent(const logic::event::KeyPress & event);
			void onEvent(const logic::event::KeyRelease & event);
			void onEvent(const logic::event::MousePress & event);
			void onEvent(const logic::event::MouseRelease & event);

			void process();
			void render() const;

		private:
			Widget m_widget;

			logic::script::Script m_script;
		};
	}
}