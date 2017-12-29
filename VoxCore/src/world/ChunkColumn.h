
#pragma once

#include "world/Chunk.h"

#include <map>

namespace world
{
	class ChunkColumn
	{
	public:
		ChunkColumn() = default;
		ChunkColumn(const ChunkColumn &) = delete;
		ChunkColumn(ChunkColumn &&) = default;
		~ChunkColumn() = default;

		ChunkColumn & operator=(const ChunkColumn &) = delete;
		ChunkColumn & operator=(ChunkColumn &&) = default;

		inline auto empty() const { return m_chunks.empty(); }

		Chunk & createChunk(int cz);
		void destroyChunk(int cz);

		bool hasChunkAt(int cz) const;
		Chunk * getChunkAt(int cz);
		Chunk * getChunkAbove(int cz);
		Chunk * getChunkBelow(int cz);

		Chunk * getTopmostChunk();
		Chunk * getBottommostChunk();

	private:
		std::map<int, Chunk> m_chunks;
	};
}