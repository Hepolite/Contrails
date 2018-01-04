
#pragma once

#include "core/Engine.h"
#include "render/uboRegistry.h"

namespace core
{
	namespace setup
	{
		void setupUbos(Engine & engine);

		namespace detail
		{
			void setupCameraUbo(render::uboRegistry & registry);
			void setupModelUbo(render::uboRegistry & registry);
		}
	}
}