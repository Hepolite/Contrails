
#include "SetupUbos.h"

#include <glm/mat4x4.hpp>

void core::setup::setupUbos(Engine & engine)
{
	auto & registry = engine.getUboRegistry();
	registry.clear();

	detail::setupCameraUbo(registry);
	detail::setupModelUbo(registry);
}

void core::setup::detail::setupCameraUbo(render::uboRegistry & registry)
{
	auto & ubo = registry.add("Camera");
	ubo.add<glm::mat4>("proj");
	ubo.add<glm::mat4>("projInv");
	ubo.add<glm::mat4>("view");
	ubo.add<glm::mat4>("viewInv");
	ubo.add<glm::mat4>("projview");
	ubo.add<glm::mat4>("projviewInv");
	ubo.build();
}
void core::setup::detail::setupModelUbo(render::uboRegistry & registry)
{
	auto & ubo = registry.add("Model");
	ubo.add<glm::mat4>("transform");
	ubo.build();
}