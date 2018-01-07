
#pragma once

#include "render/scene/Camera.h"
#include "render/scene/CameraUtil.h"

namespace render
{
	namespace scene
	{
		class CameraStorage
		{
		public:


		private:
			Camera m_cameras[MAX_CAMERA_COUNT];
		};
	}
}