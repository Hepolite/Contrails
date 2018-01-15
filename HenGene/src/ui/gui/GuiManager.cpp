
#include "GuiManager.h"

#include "logic/event/EventBus.h"
#include "ui/gui/detail/GuiLoader.h"

void ui::gui::GuiManager::inject(logic::event::EventBus & bus)
{
	using namespace logic::event;
	m_displayResize = bus.add<DisplayResize>(
		[this](auto & event) { for (auto & it : m_guis) it.second->onEvent(event); }
	);
	m_keyPress = bus.add<KeyPress>
		([this](auto & event) { for (auto & it : m_guis) if (it.second->onEvent(event)) return; }
	);
	m_keyRelease = bus.add<KeyRelease>(
		[this](auto & event) { for (auto & it : m_guis) it.second->onEvent(event); }
	);
	m_mousePress = bus.add<MousePress>(
		[this](auto & event) { for (auto & it : m_guis) if (it.second->onEvent(event)) return; }
	);
	m_mouseRelease = bus.add<MouseRelease>(
		[this](auto & event) { for (auto & it : m_guis) it.second->onEvent(event); }
	);
	m_mouseMove = bus.add<MouseMove>(
		[this](auto & event) { for (auto & it : m_guis) if (it.second->onEvent(event)) return; }
	);
}

bool ui::gui::GuiManager::open(const io::File & file, std::unique_ptr<Gui> && gui)
{
	if (m_guis.find(file.getPath()) != m_guis.end() || !file.exists())
		return false;
	auto & reference = *gui;
	m_guis.emplace(file.getPath(), std::move(gui)).first->second;
	load(file, reference);
	return true;
}
bool ui::gui::GuiManager::close(const io::File & file)
{
	if (m_guis.find(file.getPath()) == m_guis.end())
		return false;
	m_guis.erase(file.getPath());
	return true;
}
ui::gui::Gui * ui::gui::GuiManager::get(const io::File & file) const
{
	const auto it = m_guis.find(file.getPath());
	return it == m_guis.end() ? nullptr : it->second.get();
}

void ui::gui::GuiManager::load(const io::File & file, Gui & gui)
{
	GuiLoader loader{ gui };
	if (m_assets != nullptr)
		loader.inject(*m_assets);
	loader.load(file);

	if (m_display != nullptr)
	{
		gui.getWidgets().get().m_size.m_automatic = false;
		gui.getWidgets().get().m_size.m_size = m_display->getSize();
	}

	gui.getScript().execute("global GUI = GUI_MANAGER.get(File(\"" + file.getPath() + "\"));");
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
