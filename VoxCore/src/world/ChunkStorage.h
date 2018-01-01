
#pragma once

#define GLM_ENABLE_EXPERIMENTAL

#include "world/detail/Chunk.h"
#include "world/detail/ChunkColumn.h"

#include <glm/gtx/hash.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <unordered_map>

namespace world
{
	class ChunkStorage
	{
	public:
		Chunk & createChunk(const glm::ivec3 & cpos);
		void destroyChunk(const glm::ivec3 & cpos);

		bool hasChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAt(const glm::ivec3 & cpos) const;
		Chunk * getChunkAbove(const glm::ivec3 & cpos) const;
		Chunk * getChunkBelow(const glm::ivec3 & cpos) const;

		Chunk * getTopmostChunk(const glm::ivec2 & cpos) const;
		Chunk * getBottommostChunk(const glm::ivec2 & cpos) const;

	private:
		bool hasColumn(const glm::ivec2 & cpos) const;
		ChunkColumn & getColumn(const glm::ivec2 & cpos);
		const ChunkColumn & getColumn(const glm::ivec2 & cpos) const;

		std::unordered_map<glm::ivec2, ChunkColumn> m_columns;
	};
}