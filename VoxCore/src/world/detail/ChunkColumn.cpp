
#include "ChunkColumn.h"

#include "util/Maths.h"

world::Chunk & world::ChunkColumn::createChunk(int cz)
{
	destroyChunk(cz);
	return m_chunks[cz];
}
void world::ChunkColumn::destroyChunk(int cz)
{
	m_chunks.erase(cz);
}

bool world::ChunkColumn::hasChunkAt(int cz) const
{
	return m_chunks.find(cz) != m_chunks.end();
}
world::Chunk * world::ChunkColumn::getChunkAt(int cz) const
{
	const auto it = m_chunks.find(cz);
	return it == m_chunks.end() ? nullptr : &it->second;
}
world::Chunk * world::ChunkColumn::getChunkAbove(int cz) const
{
	const auto it = std::upper_bound(m_chunks.begin(), m_chunks.end(), cz,
		[](const auto & lhs, const auto & rhs) { return lhs < rhs.first; }
	);
	return it == m_chunks.end() ? nullptr : &it->second;
}
world::Chunk * world::ChunkColumn::getChunkBelow(int cz) const
{
	auto it = std::lower_bound(m_chunks.begin(), m_chunks.end(), cz,
		[](const auto & lhs, const auto & rhs) { return lhs.first < rhs; }
	);
	return it == m_chunks.begin() ? nullptr : &(--it)->second;
}
int world::ChunkColumn::getChunkPosAbove(int cz) const
{
	const auto it = std::upper_bound(m_chunks.begin(), m_chunks.end(), cz,
		[](const auto & lhs, const auto & rhs) { return lhs < rhs.first; }
	);
	return it == m_chunks.end() ? std::numeric_limits<int>::max() : it->first;
}
int world::ChunkColumn::getChunkPosBelow(int cz) const
{
	auto it = std::lower_bound(m_chunks.begin(), m_chunks.end(), cz,
		[](const auto & lhs, const auto & rhs) { return lhs.first < rhs; }
	);
	return it == m_chunks.begin() ? std::numeric_limits<int>::min() : (--it)->first;
}

world::Chunk * world::ChunkColumn::getTopmostChunk() const
{
	return empty() ? nullptr : &m_chunks.rbegin()->second;
}
world::Chunk * world::ChunkColumn::getBottommostChunk() const
{
	return empty() ? nullptr : &m_chunks.begin()->second;
}
int world::ChunkColumn::getTopmostChunkPos() const
{
	return empty() ? 0 : m_chunks.rbegin()->first;
}
int world::ChunkColumn::getBottommostChunkPos() const
{
	return empty() ? 0 : m_chunks.begin()->first;
}
