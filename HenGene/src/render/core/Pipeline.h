
#pragma once

#include "util/Physics.h"
#include "render/scene/Scene.h"

namespace render
{
	namespace core
	{
		class Pipeline
		{
		public:
			inline void inject(const scene::Scene & scene) { m_scene = &scene; }

			void render(const Time & t, const Time & dt) const;

		private:
			const scene::Scene * m_scene;
		};
	}
}