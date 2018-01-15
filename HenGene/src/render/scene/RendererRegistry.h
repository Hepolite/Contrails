
#pragma once

#include "render/RenderPass.h"
#include "render/scene/Renderer.h"

#include <memory>
#include <vector>

namespace render
{
	namespace scene
	{
		class RendererRegistry
		{
		public:
			void render(const Time & t, const Time & dt, float pt, RenderPass pass) const;

			inline void add(RendererBase * renderer) { m_renderers.push_back(renderer); }
			inline void clear() { m_renderers.clear(); }

		private:
			std::vector<RendererBase *> m_renderers;
		};
	}
}