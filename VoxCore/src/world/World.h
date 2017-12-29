
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "world/ChunkColumn.h"
#include "world/data/BlockData.h"
#include "world/data/WorldQuery.h"

#include "logic/event/EventBus.h"

#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

namespace world
{
	class World
	{
	public:
		World() = default;
		World(const logic::event::EventBus & bus) : m_eventBus(&bus) {}
		World(const World &) = delete;
		World(World &&) = default;
		~World() = default;

		World & operator=(const World &) = delete;
		World & operator=(World &&) = default;

		// ...

		void write(data::WorldQuery & query);
		void write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color);
		void read(data::WorldQuery & query) const;
		void read(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color) const;

		// ...

		Chunk & createChunk(const glm::ivec3 & cpos);
		void destroyChunk(const glm::ivec3 & cpos);
		
		bool hasChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAt(const glm::ivec3 & cpos);
		Chunk * getChunkAbove(const glm::ivec3 & cpos);
		Chunk * getChunkBelow(const glm::ivec3 & cpos);

		Chunk * getTopmostChunk(const glm::ivec2 & cpos);
		Chunk * getBottommostChunk(const glm::ivec2 & cpos);

	private:
		bool hasColumn(const glm::ivec2 & cpos) const;
		ChunkColumn & getColumn(const glm::ivec2 & cpos);
		const ChunkColumn & getColumn(const glm::ivec2 & cpos) const;

		// ...

		const logic::event::EventBus * m_eventBus = nullptr;

		std::unordered_map<glm::ivec2, ChunkColumn> m_columns;
	};
}