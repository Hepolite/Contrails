
#pragma once

#include "util/Physics.h"
#include "render/RenderPass.h"
#include "render/CameraUtil.h"

namespace render
{
	struct RenderContext
	{
		CameraType m_camera;
		RenderPass m_renderPass;
		float m_partialFrame;
	};
}