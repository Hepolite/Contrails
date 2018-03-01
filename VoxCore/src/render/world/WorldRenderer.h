
#pragma once

#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "render/RenderPass.h"
#include "world/World.h"

#include <memory>

namespace render
{
	namespace world
	{
		class WorldRenderer
		{
		public:
			WorldRenderer();
			WorldRenderer(const WorldRenderer &) = delete;
			WorldRenderer(WorldRenderer &&) noexcept;
			~WorldRenderer();

			WorldRenderer & operator=(const WorldRenderer &) = delete;
			WorldRenderer & operator=(WorldRenderer &&) noexcept = default;

			void inject(::logic::event::EventBus & bus);
			void inject(const ::world::World & world);

			void load(const io::Folder & data);
			void process();
			void render(render::RenderPass pass) const;

		private:
			class Impl;
			std::unique_ptr<Impl> m_impl;
		};
	}
}