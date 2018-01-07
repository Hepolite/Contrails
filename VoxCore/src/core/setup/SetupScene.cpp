
#include "SetupScene.h"

#include "logic/ecs/systems/SystemPhysical.h"

void core::setup::setupScene(Engine & engine)
{
	auto & scene = engine.getScene();
	scene.clearSystems();
	scene.clearEntities();

	detail::setupSystems(scene);
}

void core::setup::detail::setupSystems(scene::Scene & scene)
{
	using namespace logic::ecs;

	scene.registerSystems<SystemMovement, SystemAccelerate>();
}
