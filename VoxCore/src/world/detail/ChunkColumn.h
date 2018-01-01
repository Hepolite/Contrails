
#pragma once

#include "world/detail/Chunk.h"

#include <map>
#include <memory>

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
		Chunk * getChunkAt(int cz) const;
		Chunk * getChunkAbove(int cz) const;
		Chunk * getChunkBelow(int cz) const;

		Chunk * getTopmostChunk() const;
		Chunk * getBottommostChunk() const;

	private:
		mutable std::map<int, Chunk> m_chunks;
	};
}