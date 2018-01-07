
#include "RendererRegistry.h"

void render::scene::RendererRegistry::render(const Time & t, const Time & dt, RenderPass pass) const
{
	for (const auto & renderer : m_renderers)
		renderer->render(t, dt, pass);
}
