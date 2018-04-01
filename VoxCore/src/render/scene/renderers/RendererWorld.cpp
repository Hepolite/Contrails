
#include "RendererWorld.h"

#include "core/Engine.h"

void render::scene::RendererWorld::initialize(core::Engine & engine)
{
	m_renderer = &engine.getUniverseRenderer();
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
	const auto & data = getData<::world::ComponentWorld>();
	for (auto & entity : *this)
	{
		auto * world = m_renderer->getWorld(data[entity].m_name);
		if (world != nullptr)
			world->render(context.m_renderPass);
	}
}
