
#pragma once

#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "world/BlockRegistry.h"
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
			WorldRenderer(WorldRenderer &&) noexcept = default;
			~WorldRenderer();

			WorldRenderer & operator=(const WorldRenderer &) = delete;
			WorldRenderer & operator=(WorldRenderer &&) noexcept = default;

			void inject(logic::event::EventBus & bus);
			void inject(::world::World & world);

			void load(const ::world::BlockRegistry & registry, const io::Folder & data);

		private:
			//struct Impl;
			//std::unique_ptr<Impl> m_impl = nullptr;
		};
	}
}