
#include "StateEditorWorld.h"

#include "core/Engine.h"
#include "ui/gui/GuiManager.h"

#include "asset/AssetRef.h"
#include "asset/AssetRegistry.h"
#include "core/scene/Scene.h"
#include "render/Mesh.h"
#include "render/opengl/Program.h"
#include "render/scene/Renderer.h"
#include "render/uboRegistry.h"
#include "util/Maths.h"
#include "world/Universe.h"
#include "world/util/Query.h"
#include "world/World.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>

namespace
{
	struct ComponentMesh
	{
		render::Mesh<glm::vec3> m_mesh;
	};

	class RendererMesh : public render::scene::Renderer<ComponentMesh>
	{
	public:
		void initialize(core::Engine & engine)
		{
			m_program = engine.getAssets().get<render::opengl::Program>("test");
			m_model = &engine.getUboRegistry().get("Model");
		}

		virtual void render(const Time & t, const Time & dt, float pt) const override final
		{
			if (m_model != nullptr)
				m_model->set("transform", glm::rotate(glm::mat4{ 1.0f }, (float)(t + dt * pt)(), glm::vec3{ 0.0f, 0.0f, 1.0f }));
			if (m_program != nullptr)
				m_program->bind();

			auto & meshes = getData<ComponentMesh>();
			for (const auto & entity : *this)
				meshes[entity].m_mesh.render();
		}

	private:
		asset::Ref<render::opengl::Program> m_program;
		const render::opengl::ubo * m_model = nullptr;
	};
}

void logic::state::StateEditorWorld::initialize(core::Engine & engine)
{
	engine.getGuiManager().open("data/guis/editor_world.xml");

	auto & scene = engine.getScene();
	scene.registerRenderers<RendererMesh>().initialize(engine);
	scene.getCameras().getCamera(render::scene::CameraType::NORMAL).setPosition({ -15.0f, -15.0f, 20.0f });
	scene.getCameras().getCamera(render::scene::CameraType::NORMAL).lookTowards({ 0.0f, 0.0f, 0.0f });

	auto entity = scene.createEntity<ComponentMesh>();
	auto & mesh = scene.getEntityData<ComponentMesh>(entity).m_mesh;
	mesh.getIndiceData() = { 0u, 1u, 2u };
	mesh.getVertexData() = { { -0.5f, -0.5f, 0.0f }, { 0.5f, -0.5f, 0.0f }, { 0.0f, 0.5f, 0.0f } };
	mesh.addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3u, 0u });
	mesh.build();

	engine.getUniverse().createWorld("world");
	auto * world = engine.getUniverse().getWorld("world");
	auto query = world::util::Query{}.writeRectangle(
		world->getBlockRegistry()["stone"],
		{ 0, 0, 0 },
		{ world::data::CHUNK_SIZE_BITS<int>, world::data::CHUNK_SIZE_BITS<int>, 8 }
	);
	world->write(query);
}
void logic::state::StateEditorWorld::deinitialize(core::Engine & engine)
{
	engine.getGuiManager().close("data/guis/editor_world.xml");

	engine.getScene().clearSystems();
	engine.getScene().clearRenderers();
	engine.getScene().clearEntities();
}

void logic::state::StateEditorWorld::process(const Time & t, const Time & dt)
{
}
