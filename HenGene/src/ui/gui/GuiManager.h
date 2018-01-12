
#pragma once

#include "logic/event/EventListener.h"
#include "io/File.h"
#include "ui/Display.h"
#include "ui/gui/Gui.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace asset { class AssetRegistry; }
namespace logic { namespace event { class EventBus; } }

namespace ui
{
	namespace gui
	{
		class GuiManager
		{
		public:
			template<typename Type = Gui>
			bool open(const io::File & file) { return open(file, std::make_unique<Type>()); }
			bool open(const io::File & file, std::unique_ptr<Gui> && gui);
			bool close(const io::File & file);
			Gui * get(const io::File & file) const;

			void process();
			void render() const;

			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }
			inline void inject(const ui::Display & display) { m_display = &display; }
			void inject(logic::event::EventBus & bus);

		private:
			void load(const io::File & file, Gui & gui);

			std::unordered_map<std::string, std::unique_ptr<Gui>> m_guis;
			logic::event::Listener m_displayResize;
			logic::event::Listener m_keyPress;
			logic::event::Listener m_keyRelease;
			logic::event::Listener m_mousePress;
			logic::event::Listener m_mouseRelease;
			logic::event::Listener m_mouseMove;

			const asset::AssetRegistry * m_assets = nullptr;
			const ui::Display * m_display = nullptr;
		};
	}
}