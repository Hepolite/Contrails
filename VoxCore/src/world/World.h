
#pragma once

#include "logic/event/EventBus.h"
#include "world/BlockRegistry.h"

#include <memory>
#include <string>

namespace world
{
	namespace data
	{
		class BlockData;
		class BlockRegion;
		class ColorData;
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

		const BlockRegistry & extractBlockRegistry() const;
		const data::BlockRegion extractRenderData(const glm::ivec3 & cpos) const;

		void write(data::WorldQuery & query);
		void read(data::WorldQuery & query) const;

	private:
		std::string m_name;

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}