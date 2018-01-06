
#include "StateMainMenu.h"

#include "asset/AssetRegistry.h"
#include "core/Engine.h"
#include "render/uboRegistry.h"

#include <glm/gtc/matrix_transform.hpp>

namespace
{
	const render::opengl::ubo * model = nullptr;
}

void logic::state::StateMainMenu::initialize(core::Engine & engine)
{
	m_mesh.getIndiceData() = { 0, 1, 2 };
	m_mesh.getVertexData() = {
		{-0.5f,-0.5f, 0.0f },
		{ 0.5f,-0.5f, 0.0f },
		{ 0.0f, 0.5f, 0.0f }
	};
	m_mesh.addAttribute({ 0u, render::opengl::DataFormat::FLOAT, 3u, 0u });
	m_mesh.build();

	m_program = engine.getAssets().get<render::opengl::Program>("test");
	model = &engine.getUboRegistry().get("Model");
}
void logic::state::StateMainMenu::deinitialize(core::Engine & engine)
{
}

void logic::state::StateMainMenu::process(const Time & t, const Time & dt)
{
}
void logic::state::StateMainMenu::render(const Time & t, const Time & dt) const
{
	if (model != nullptr)
		model->set("transform", glm::rotate(glm::mat4{ 1.0f }, (float)(t + dt)(), glm::vec3{ 0.0f, 0.0f, 1.0f }));
	if (m_program != nullptr)
		m_program->bind();
	m_mesh.render();
}
