
#pragma once

#include "logic/ecs/System.h"
#include "render/RenderPass.h"
#include "render/scene/CameraUtil.h"

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

			virtual void render(const Time & t, const Time & dt, float pt) const = 0;

			bool isVisibleToCamera(CameraType type) const;
			RenderPass getRenderPass() const;

			void setVisibleToCamera(CameraType type, bool visible);
			void setRenderPass(RenderPass pass);

		private:
			RenderPass m_pass = RenderPass::SOLID;
			CameraMask m_mask;
		};

		template<typename ...Components>
		class Renderer : public RendererBase, public logic::ecs::System<Components...>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override {}
		};
	}
}