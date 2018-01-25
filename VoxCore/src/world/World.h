
#pragma once

#include "world/BlockRegistry.h"
#include "world/detail/data/BlockData.h"

#include <memory>

namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }

namespace world
{
	namespace data
	{
		class BlockRegion;
		class WorldQuery;
	}
	class Chunk;

	class World
	{
	public:
		World();
		World(const World &) = delete;
		World(World &&) noexcept;
		~World();

		World & operator=(const World &) = delete;
		World & operator=(World &&) noexcept;

		// ...

		void inject(core::scene::Scene & scene);
		void inject(const logic::event::EventBus & bus);
		void inject(const BlockRegistry & registry);

		const data::BlockRegion extractRenderData(const glm::ivec3 & cpos) const;

		const BlockRegistry & getBlockRegistry() const;

		// ...

		Chunk & createChunk(const glm::ivec3 & cpos);
		void destroyChunk(const glm::ivec3 & cpos);

		bool hasChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAbove(const glm::ivec3 & cpos) const;
		Chunk * getChunkBelow(const glm::ivec3 & cpos) const;

		Chunk * getTopmostChunk(const glm::ivec2 & cpos) const;
		Chunk * getBottommostChunk(const glm::ivec2 & cpos) const;

		// ...

		void write(data::WorldQuery & query);
		void write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color);
		void write(const glm::ivec3 & pos, data::BlockData & block);
		void write(const glm::ivec3 & pos, data::ColorData & color);

		void read(data::WorldQuery & query) const;
		data::BlockData readBlock(const glm::ivec3 & pos) const;
		data::ColorData readColor(const glm::ivec3 & pos) const;

		// ...

		void markLightingChange(const glm::ivec3 & cpos);

		void propagateLight();

	private:
		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}