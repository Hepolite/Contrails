
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
			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }

			void load(Gui & gui, const io::File & file);
			void loadScript(Gui & gui, const pugi::xml_node & node);
			void loadLayout(Gui & gui, const pugi::xml_node & node);

		private:
			const asset::AssetRegistry * m_assets = nullptr;
		};
	}
}