
#include "StateMainMenu.h"

#include "asset/AssetRef.h"
#include "asset/AssetRegistry.h"
#include "core/Engine.h"
#include "core/scene/Scene.h"
#include "render/Mesh.h"
#include "render/opengl/Program.h"
#include "render/scene/Renderer.h"
#include "render/uboRegistry.h"

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

		virtual void render(const Time & t, const Time & dt, render::RenderPass pass) const override final
		{
			if (pass != render::RenderPass::SOLID)
				return;

			if (m_model != nullptr)
				m_model->set("transform", glm::rotate(glm::mat4{ 1.0f }, (float)(t + dt)(), glm::vec3{ 0.0f, 0.0f, 1.0f }));
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

void logic::state::StateMainMenu::initialize(core::Engine & engine)
{
	auto & scene = engine.getScene();
	scene.registerRenderers<RendererMesh>().initialize(engine);

	const auto entity = scene.createEntity<ComponentMesh>();

	auto & mesh = scene.getEntityData<ComponentMesh>(entity).m_mesh;
	mesh.getIndiceData() = { 0, 1, 2 };
	mesh.getVertexData() = { { -0.5f,-0.5f, 0.0f }, { 0.5f,-0.5f, 0.0f }, { 0.0f, 0.5f, 0.0f } };
	mesh.addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3u, 0u });
	mesh.build();
}
void logic::state::StateMainMenu::deinitialize(core::Engine & engine)
{
	engine.getScene().clearSystems();
	engine.getScene().clearRenderers();
	engine.getScene().clearEntities();
}

void logic::state::StateMainMenu::process(const Time & t, const Time & dt)
{
}
