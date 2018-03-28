
#include "StateEditorWorld.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

void logic::state::StateEditorWorld::initialize(core::Engine & engine)
{
	engine.getGuiManager().open("data/guis/editor_world.xml");
}
void logic::state::StateEditorWorld::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close("data/guis/editor_world.xml");
}

void logic::state::StateEditorWorld::process(const Time & t, const Time & dt)
{
}
