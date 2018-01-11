
#pragma once

#include "asset/AssetRegistry.h"
#include "io/File.h"
#include "ui/gui/Gui.h"

#include <pugixml/pugixml.hpp>

namespace ui
{
	namespace gui
	{
		class GuiLoader
		{
		public:
			GuiLoader() = delete;
			GuiLoader(Gui & gui);
			~GuiLoader() = default;

			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }

			void load(const io::File & file);
			void loadScript(const pugi::xml_node & node);
			void loadLayout(const pugi::xml_node & node);

		private:
			const asset::AssetRegistry * m_assets = nullptr;

			Gui * m_gui = nullptr;
		};
	}
}