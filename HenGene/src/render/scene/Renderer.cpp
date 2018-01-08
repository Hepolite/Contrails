
#include "Renderer.h"

bool render::scene::RendererBase::isVisibleToCamera(CameraType type) const
{
	return m_mask[static_cast<unsigned int>(type)];
}
void render::scene::RendererBase::setVisibleToCamera(CameraType type, bool visible)
{
	m_mask[static_cast<unsigned int>(type)] = visible;
}

render::RenderPass render::scene::RendererBase::getRenderPass() const
{
	return m_pass;
}
void render::scene::RendererBase::setRenderPass(RenderPass pass)
{
	m_pass = pass;
}
