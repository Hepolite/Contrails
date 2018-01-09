
#pragma once

#include "asset/AssetRegistry.h"
#include "ui/gui/detail/Widget.h"

#include <pugixml/pugixml.hpp>

namespace ui
{
	namespace gui
	{
		class WidgetLoader
		{
		public:
			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }

			void load(Widget & widget, const pugi::xml_node & node);
			void loadActivation(Widget & widget, const pugi::xml_node & node);
			void loadAssets(Widget & widget, const pugi::xml_node & node);
			void loadBorder(Widget & widget, const pugi::xml_node & node);
			void loadFamily(Widget & widget, const pugi::xml_node & node);
			void loadGroup(Widget & widget, const pugi::xml_node & node);
			void loadLink(Widget & widget, const pugi::xml_node & node);
			void loadPosition(Widget & widget, const pugi::xml_node & node);
			void loadSize(Widget & widget, const pugi::xml_node & node);
			void loadState(Widget & widget, const pugi::xml_node & node);

		private:
			const asset::AssetRegistry * m_assets = nullptr;
		};
	}
}
