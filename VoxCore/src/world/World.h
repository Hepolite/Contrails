
#pragma once

#include "io/Folder.h"
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

		void load(const io::Folder & data);
		void process();

		// ...

		void inject(const logic::event::EventBus & bus);
		void inject(const BlockRegistry & registry);

		data::BlockRegion extractRenderData(const glm::ivec3 & cpos) const;

		const BlockRegistry & getBlockRegistry() const;

		// ...

		Chunk & createChunk(const glm::ivec3 & cpos, bool initLight = false);
		void destroyChunk(const glm::ivec3 & cpos);

		bool hasChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAbove(const glm::ivec3 & cpos) const;
		Chunk * getChunkBelow(const glm::ivec3 & cpos) const;
		glm::ivec3 getChunkPosAbove(glm::ivec3 cpos) const;
		glm::ivec3 getChunkPosBelow(glm::ivec3 cpos) const;

		Chunk * getTopmostChunk(const glm::ivec2 & cpos) const;
		Chunk * getBottommostChunk(const glm::ivec2 & cpos) const;
		glm::ivec3 getTopmostChunkPos(const glm::ivec2 & cpos) const;
		glm::ivec3 getBottommostChunkPos(const glm::ivec2 & cpos) const;

		// ...

		void write(data::WorldQuery & query);
		void write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color);
		void write(const glm::ivec3 & pos, data::BlockData & block);
		void write(const glm::ivec3 & pos, data::ColorData & color);

		void read(data::WorldQuery & query) const;
		data::BlockData readBlock(const glm::ivec3 & pos) const;
		data::ColorData readColor(const glm::ivec3 & pos) const;

		// ...

		void markChunkChange(const glm::ivec3 & cpos);
		void markChunkChange(const glm::ivec3 & cpos, const glm::uvec3 & min, const glm::uvec3 & max);

		void markLightPropagation(const glm::ivec3 & cpos);
		void markLightRemoval(const glm::ivec3 & cpos);

	private:
		void initializeLight(const glm::ivec3 & cpos);
		void calculateLight();

		bool emptyNeighborhood(const glm::ivec3 & cpos) const;
		void handleChunkChange(const glm::ivec3 & cpos, const glm::ivec3 & min, const glm::ivec3 & max);

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}