
#pragma once

#include "world/BlockRegistry.h"
#include "world/detail/data/BlockData.h"

#include <memory>
#include <string>

namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }

namespace world
{
	namespace data
	{
		class BlockRegion;
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

		void inject(core::scene::Scene & scene);
		void inject(const logic::event::EventBus & bus);

		void injectBlockRegistry(const BlockRegistry & registry);
		const data::BlockRegion extractRenderData(const glm::ivec3 & cpos) const;

		// ...

		const BlockRegistry & getBlockRegistry() const;

		void write(data::WorldQuery & query);
		void write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color);
		void write(const glm::ivec3 & pos, data::BlockData & block);
		void write(const glm::ivec3 & pos, data::ColorData & color);
		void read(data::WorldQuery & query) const;
		data::BlockData readBlock(const glm::ivec3 & pos) const;
		data::ColorData readColor(const glm::ivec3 & pos) const;

	private:
		std::string m_name;

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}