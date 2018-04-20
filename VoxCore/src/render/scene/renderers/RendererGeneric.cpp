
#include "RendererGeneric.h"

void render::scene::RendererGeneric::process(const Time & t, const Time & dt)
{
	auto & data = getData<ComponentGeneric>();
	for (auto & entity : *this)
	{
		if (auto & processor = data[entity].m_processer)
			processor(t, dt);
	}
}
void render::scene::RendererGeneric::render(const RenderContext & context, const Time & t, const Time & dt) const
{
	auto & data = getData<ComponentGeneric>();
	for (auto & entity : *this)
	{
		if (auto & renderer = data[entity].m_renderer)
			renderer(context, t, dt);
	}
}