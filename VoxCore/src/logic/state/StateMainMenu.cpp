
#include "StateMainMenu.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

void logic::state::StateMainMenu::initialize(core::Engine & engine)
{
	engine.getGuiManager().open("data/guis/main_menu.xml");
}
void logic::state::StateMainMenu::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close("data/guis/main_menu.xml");
}

void logic::state::StateMainMenu::process(const Time & t, const Time & dt)
{
}
