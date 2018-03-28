
#include "CameraStorage.h"

void render::CameraStorage::inject(const uboRegistry & registry)
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].inject(registry);
}
void render::CameraStorage::inject(const ui::Display & display)
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].inject(display);
}

void render::CameraStorage::process()
{
	for (unsigned int i = 0; i < MAX_CAMERA_COUNT; ++i)
		m_cameras[i].process();
}

render::Camera & render::CameraStorage::getCamera(CameraType type)
{
	return m_cameras[static_cast<unsigned int>(type)];
}
const render::Camera & render::CameraStorage::getCamera(CameraType type) const
{
	return m_cameras[static_cast<unsigned int>(type)];
}
