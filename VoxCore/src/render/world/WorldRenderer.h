
#pragma once

#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "world/BlockRegistry.h"

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

			void injectBlockRegistry(const ::world::BlockRegistry & registry);
			void injectEventBus(logic::event::EventBus & bus);

			void load(const io::Folder & data);

		private:
			struct Impl;
			std::unique_ptr<Impl> m_impl = nullptr;
		};
	}
}