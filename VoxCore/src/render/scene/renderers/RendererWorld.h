
#pragma once

#include "asset/AssetRef.h"
#include "render/opengl/Program.h"
#include "render/opengl/ubo.h"
#include "render/scene/Renderer.h"
#include "world/Universe.h"
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
			asset::Ref<opengl::Program> m_program[RENDER_PASS_COUNT];

			::world::render::UniverseRenderer * m_renderer = nullptr;
			const opengl::ubo * m_model = nullptr;
		};
	}
}