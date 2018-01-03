
#include "StateStartup.h"

#include "asset/AssetRegistry.h"
#include "asset/AssetUtil.h"
#include "asset/factory/LoaderShaderProgram.h"
#include "logic/event/EventBus.h"
#include "logic/event/Events.h"
#include "render/opengl/Program.h"

#include <glm/glm.hpp>

namespace
{
	void setupubos(core::Engine & engine)
	{
		auto & ubos = engine.extractuboRegistry();
		ubos.clear();

		auto & camera = ubos.add("Camera");
		camera.add<glm::mat4>("proj");
		camera.add<glm::mat4>("projInv");
		camera.add<glm::mat4>("view");
		camera.add<glm::mat4>("viewInv");
		camera.add<glm::mat4>("projview");
		camera.add<glm::mat4>("projviewInv");
		camera.build();

		auto & model = ubos.add("Model");
		model.add<glm::mat4>("transform");
		model.build();
	}

	void setupAssets(core::Engine & engine)
	{
		auto & assets = engine.extractAssets();
		assets.clear();

		asset::util::setupLoaderFactory<render::opengl::Program, asset::util::LoaderShaderProgram>(
			assets, "data/shaders", "xml", "data/shaders", engine.extractuboRegistry()
		);
	}
}

logic::state::StateStartup::StateStartup(core::Engine & engine)
{
	setupubos(engine);
	setupAssets(engine);

	engine.extractEventBus().add<logic::event::DisplayClose>([&engine](auto &) { engine.stop(); });
}