
#pragma once

#include "render/scene/components/ComponentGeneric.h"
#include "render/scene/Renderer.h"

namespace render
{
	namespace scene
	{
		class RendererGeneric : public Renderer<ComponentGeneric>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override final;
			virtual void render(const RenderContext & context, const Time & t, const Time & dt) const override final;
		};
	}
}
