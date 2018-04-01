
#include "SetupScene.h"

#include "logic/ecs/systems/SystemPhysical.h"
#include "render/scene/renderers/RendererWorld.h"

void core::setup::setupScene(Engine & engine)
{
	auto & scene = engine.getScene();
	scene.clearSystems();
	scene.clearEntities();

	detail::setupSystems(scene);
	detail::setupRenders(scene, engine);
}

void core::setup::detail::setupSystems(scene::Scene & scene)
{
	using namespace logic::ecs;

	scene.registerSystems<SystemMovement, SystemAcceleration, SystemGravitation>();
}
void core::setup::detail::setupRenders(scene::Scene & scene, Engine & engine)
{
	using namespace render::scene;

	scene.registerRenderers<RendererWorld>();
}
