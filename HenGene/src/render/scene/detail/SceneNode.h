
#pragma once

#include "render/RenderLayer.h"
#include "util/Physics.h"

#include <functional>
#include <glm/vec3.hpp>

namespace render
{
	namespace scene
	{
		using SceneRender = std::function<void(const Time & t, const Time & dt)>;

		struct SceneNode
		{
			unsigned int m_id = 0u;
			RenderLayer m_layer = RenderLayer::INVISIBLE;
			SceneRender m_render = nullptr;
		};
	}
}