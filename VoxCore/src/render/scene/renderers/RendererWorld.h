
#pragma once

#include "render/scene/Renderer.h"
#include "world/render/UniverseRenderer.h"

namespace render
{
	namespace scene
	{
		class RendererWorld : public Renderer<::world::ComponentWorld>
		{
		public:
			virtual void initialize(core::Engine & engine) override final;
			virtual void process(const Time & t, const Time & dt) override final;
			virtual void render(const RenderContext & context, const Time & t, const Time & dt) const override final;

		private:
			::world::render::UniverseRenderer * m_renderer = nullptr;
		};
	}
}