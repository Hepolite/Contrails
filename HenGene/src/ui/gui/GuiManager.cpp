
#include "GuiManager.h"

#include "ui/gui/detail/GuiLoader.h"

void ui::gui::GuiManager::load(const io::File & file, Gui & gui)
{
	GuiLoader loader{ gui };
	if (m_assets != nullptr)
		loader.inject(*m_assets);
	loader.load(file);
}

void ui::gui::GuiManager::process()
{
	for (const auto & it : m_guis)
		it.second->process();
}
void ui::gui::GuiManager::render() const
{
	for (const auto & it : m_guis)
		it.second->render();
}
