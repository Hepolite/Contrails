
#include "RendererRegistry.h"

void render::scene::RendererRegistry::render(const Time & t, const Time & dt, float pt, RenderPass pass, CameraType camera) const
{
	RenderContext context{ camera, pass, pt };
	for (const auto & renderer : m_renderers)
		renderer->render(context, t, dt);
}
