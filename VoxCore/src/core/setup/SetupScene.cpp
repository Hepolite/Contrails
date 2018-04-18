
#include "SetupScene.h"

#include "logic/ecs/systems/SystemPhysical.h"
#include "render/scene/renderers/RendererMesh.h"
#include "render/scene/renderers/RendererWorld.h"

#include <glm/vec3.hpp>

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

	scene.registerRenderers<RendererMesh<glm::vec3>>();	// Used by editors
	scene.registerRenderers<RendererWorld>();			// Used by world renderers
}
