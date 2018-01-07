
#pragma once

#include "core/scene/Scene.h"
#include "util/Physics.h"

namespace render
{
	namespace core
	{
		class Pipeline
		{
		public:
			inline void inject(const ::core::scene::Scene & scene) { m_scene = &scene; }

			void render(const Time & t, const Time & dt) const;

		private:
			const ::core::scene::Scene * m_scene = nullptr;
		};
	}
}