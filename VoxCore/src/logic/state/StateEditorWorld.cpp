
#include "StateEditorWorld.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

#include "core/scene/Scene.h"
#include "world/Universe.h"
#include "world/util/Query.h"
#include "world/World.h"

void logic::state::StateEditorWorld::initialize(core::Engine & engine)
{
	engine.getGuiManager().open("data/guis/editor_world.xml");
	engine.getUniverse().createWorld("world");

	// Set up a small test world
	auto * world = engine.getUniverse().getWorld("world");
	auto & blocks = world->getBlockRegistry();

	world::util::Query query;
	world->write(query.writeRectangle(blocks["stone"], { -15, -15, 0 }, { 15, 15, 3 }));
	world->write(query.writeRectangle(blocks["dirt"], { -15, -15, 4 }, { 15, 15, 5 }));
	world->write(query.writeRectangle(blocks["grass"], { -15, -15, 6 }, { 15, 15, 6 }));

	// Place camera in a suitable location
	auto & camera = engine.getScene().getCamera(render::scene::CameraType::NORMAL);
	camera.setPosition({ -32, -32, 32 });
	camera.lookTowards({ 0, 0, 0 });
}
void logic::state::StateEditorWorld::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close("data/guis/editor_world.xml");
	engine.getUniverse().destroyWorld("world");
}

void logic::state::StateEditorWorld::process(const Time & t, const Time & dt)
{
}
