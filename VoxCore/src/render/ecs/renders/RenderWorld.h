
#pragma once

#include "render/scene/Renderer.h"
#include "render/world/UniverseRenderer.h"
#include "world/Universe.h"

namespace render
{
	namespace ecs
	{
		class RenderWorld : public scene::Renderer<::world::ComponentWorld>
		{
		public:
			inline void insert(world::UniverseRenderer & renderer) { m_renderer = &renderer; }
			
			virtual void process(const Time & t, const Time & dt) override final;
			virtual void render(const Time & t, const Time & dt, float pt) const override final;

		private:
			world::UniverseRenderer * m_renderer = nullptr;
		};
	}
}