
#include "RendererWorld.h"

#include "asset/AssetRegistry.h"
#include "core/Engine.h"
#include "render/uboRegistry.h"

void render::scene::RendererWorld::initialize(core::Engine & engine)
{
	m_renderer = &engine.getUniverseRenderer();
	m_model = &engine.getUboRegistry().get("Model");

	auto & assets = engine.getAssets();
	for (unsigned int i = 0u; i < RENDER_PASS_COUNT; ++i)
		m_program[i] = assets.get<opengl::Program>("world_chunk");
}

void render::scene::RendererWorld::process(const Time & t, const Time & dt)
{
	const auto & data = getData<::world::ComponentWorld>();
	for (auto & entity : *this)
	{
		auto * world = m_renderer->getWorld(data[entity].m_name);
		if (world != nullptr)
			world->process();
	}
}
void render::scene::RendererWorld::render(const RenderContext & context, const Time & t, const Time & dt) const
{
	m_program[static_cast<int>(context.m_renderPass)]->bind();
	m_model->set("transform", glm::mat4{ 1.0f });

	const auto & data = getData<::world::ComponentWorld>();
	for (auto & entity : *this)
	{
		auto * world = m_renderer->getWorld(data[entity].m_name);
		if (world != nullptr)
			world->render(context.m_renderPass);
	}
}
