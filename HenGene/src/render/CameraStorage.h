
#pragma once

#include "render/Camera.h"
#include "render/CameraUtil.h"
#include "render/uboRegistry.h"
#include "ui/Display.h"

namespace render
{
	class CameraStorage
	{
	public:
		CameraStorage() = default;
		CameraStorage(const CameraStorage &) = delete;
		CameraStorage(CameraStorage &&) = delete;
		~CameraStorage() = default;

		CameraStorage & operator=(const CameraStorage &) = delete;
		CameraStorage & operator=(CameraStorage &&) = delete;

		void inject(const uboRegistry & registry);
		void inject(const ui::Display & display);

		void process();

		Camera & getCamera(CameraType type);
		const Camera & getCamera(CameraType type) const;

	private:
		Camera m_cameras[MAX_CAMERA_COUNT];
	};
}