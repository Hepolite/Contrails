
#include "CameraStorage.h"

void render::scene::CameraStorage::inject(const uboRegistry & registry)
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].inject(registry);
}
void render::scene::CameraStorage::inject(const ui::Display & display)
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].inject(display);
}

void render::scene::CameraStorage::process()
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].process();
}

render::scene::Camera & render::scene::CameraStorage::getCamera(CameraType type)
{
	return m_cameras[static_cast<unsigned int>(type)];
}
const render::scene::Camera & render::scene::CameraStorage::getCamera(CameraType type) const
{
	return m_cameras[static_cast<unsigned int>(type)];
}
