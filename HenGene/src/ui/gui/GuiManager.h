
#pragma once

#include "io/File.h"
#include "ui/gui/Gui.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace asset { class AssetRegistry; }

namespace ui
{
	namespace gui
	{
		class GuiManager
		{
		public:
			template<typename Type = Gui> bool open(const io::File & file);
			template<typename Type = Gui> bool close(const io::File & file);

			void process();
			void render() const;

			inline void inject(const asset::AssetRegistry & assets) { m_assets = &assets; }

		private:
			void load(const io::File & file, Gui & gui);

			const asset::AssetRegistry * m_assets = nullptr;

			std::unordered_map<std::string, std::unique_ptr<Gui>> m_guis;
		};
	}
}

template<typename Type>
inline bool ui::gui::GuiManager::open(const io::File & file)
{
	if (m_guis.find(file.getPath()) != m_guis.end() || !file.exists())
		return false;
	auto & gui = m_guis.emplace(file.getPath(), std::make_unique<Type>()).first->second;
	load(file, *gui);
	return true;
}
template<typename Type>
inline bool ui::gui::GuiManager::close(const io::File & file)
{
	if (m_guis.find(file.getPath()) == m_guis.end())
		return false;
	m_guis.erase(file.getPath());
	return true;
}
