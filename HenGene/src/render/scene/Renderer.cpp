
#include "Renderer.h"

bool render::scene::RendererBase::isVisibleToCamera(CameraType type) const
{
	return m_mask[static_cast<unsigned int>(type)];
}
void render::scene::RendererBase::setVisibleToCamera(CameraType type, bool visible)
{
	m_mask[static_cast<unsigned int>(type)] = visible;
}
