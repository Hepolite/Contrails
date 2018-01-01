
#pragma once

#include "logic/event/EventBus.h"
#include "world/BlockRegistry.h"

#include <memory>

namespace world
{
	namespace data
	{
		class BlockData;
		class ColorData;
		class ChunkDataBloated;
		class WorldQuery;
	}

	class World
	{
	public:
		World();
		World(const World &) = delete;
		World(World &&) noexcept;
		~World();

		World & operator=(const World &) = delete;
		World & operator=(World &&) noexcept;

		void injectBlockRegistry(const BlockRegistry & registry);
		void injectEventBus(const logic::event::EventBus & bus);

		void write(data::WorldQuery & query);
		void read(data::WorldQuery & query) const;

		data::ChunkDataBloated & extractChunkData(const glm::ivec3 & cpos);

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}