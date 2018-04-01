
#pragma once

#include "render/RenderPass.h"
#include "render/scene/CameraUtil.h"

namespace render
{
	struct RenderContext
	{
		scene::CameraType m_camera;
		RenderPass m_renderPass;
		float m_partialFrame;
	};
}