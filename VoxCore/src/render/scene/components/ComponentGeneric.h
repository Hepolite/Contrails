
#pragma once

#include "render/RenderContext.h"
#include "util/Physics.h"

#include <functional>

namespace render
{
	namespace scene
	{
		struct ComponentGeneric
		{
			std::function<void(const Time &, const Time &)> m_processer;
			std::function<void(const RenderContext &, const Time &, const Time &)> m_renderer;
		};
	}
}