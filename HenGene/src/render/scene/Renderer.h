
#pragma once

#include "logic/ecs/System.h"
#include "render/RenderContext.h"

namespace render
{
	namespace scene
	{
		class RendererBase
		{
		public:
			RendererBase() = default;
			RendererBase(const RendererBase &) = delete;
			RendererBase(RendererBase &&) = delete;
			virtual ~RendererBase() = default;

			RendererBase & operator=(const RendererBase &) = delete;
			RendererBase & operator=(RendererBase &&) = delete;

			virtual void render(const RenderContext & context, const Time & t, const Time & dt) const = 0;
		};

		template<typename ...Components>
		class Renderer : public RendererBase, public logic::ecs::System<Components...>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override {}
		};
	}
}