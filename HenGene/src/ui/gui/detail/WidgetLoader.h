
#pragma once

#include "ui/gui/detail/Widget.h"
#include "ui/gui/detail/Widgets.h"

#include <pugixml/pugixml.hpp>

namespace asset { class AssetRegistry; }

namespace ui
{
	namespace gui
	{
		class WidgetLoader
		{
		public:
			WidgetLoader() = delete;
			WidgetLoader(Widgets & widgets, Widget & widget);
			~WidgetLoader() = default;

			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }

			void load(const pugi::xml_node & node);
			void loadActivation(const pugi::xml_node & node);
			void loadAssets(const pugi::xml_node & node);
			void loadBorder(const pugi::xml_node & node);
			void loadFamily(const pugi::xml_node & node);
			void loadGroup(const pugi::xml_node & node);
			void loadHeader(const pugi::xml_node & node);
			void loadLink(const pugi::xml_node & node);
			void loadPosition(const pugi::xml_node & node);
			void loadSize(const pugi::xml_node & node);
			void loadState(const pugi::xml_node & node);

		private:
			const asset::AssetRegistry * m_assets = nullptr;

			Widgets * m_widgets = nullptr;
			Widget * m_widget = nullptr;
		};
	}
}
