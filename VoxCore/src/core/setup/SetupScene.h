
#pragma once

#include "core/Engine.h"
#include "core/scene/Scene.h"

namespace core
{
	namespace setup
	{
		void setupScene(Engine & engine);

		namespace detail
		{
			void setupSystems(scene::Scene & scene);
			void setupRenders(scene::Scene & scene, Engine & engine);
		}
	}
}