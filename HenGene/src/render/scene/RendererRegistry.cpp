
#include "RendererRegistry.h"

void render::scene::RendererRegistry::render(const Time & t, const Time & dt, float pt, RenderPass pass) const
{
	for (const auto & renderer : m_renderers)
	{
		if (renderer->getRenderPass() == pass)
			renderer->render(t, dt, pt);
	}
}
