
#include "ChunkStorage.h"

world::Chunk & world::ChunkStorage::createChunk(const glm::ivec3 & cpos)
{
	return getColumn(cpos).createChunk(cpos.z);
}
world::Chunk & world::ChunkStorage::createOrGetChunk(const glm::ivec3 & cpos)
{
	auto & column = getColumn(cpos);
	if (column.hasChunkAt(cpos.z))
		return *column.getChunkAt(cpos.z);
	return column.createChunk(cpos.z);
}
void world::ChunkStorage::destroyChunk(const glm::ivec3 & cpos)
{
	getColumn(cpos).destroyChunk(cpos.z);
}

bool world::ChunkStorage::hasChunkAt(const glm::ivec3 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).hasChunkAt(cpos.z) : false;
}
world::Chunk * world::ChunkStorage::getChunkAt(const glm::ivec3 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).getChunkAt(cpos.z) : nullptr;
}
world::Chunk * world::ChunkStorage::getChunkAbove(const glm::ivec3 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).getChunkAbove(cpos.z) : nullptr;
}
world::Chunk * world::ChunkStorage::getChunkBelow(const glm::ivec3 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).getChunkBelow(cpos.z) : nullptr;
}
glm::ivec3 world::ChunkStorage::getChunkPosAbove(glm::ivec3 cpos) const
{
	cpos.z = hasColumn(cpos) ? getColumn(cpos).getChunkPosAbove(cpos.z) : 0;
	return cpos;
}
glm::ivec3 world::ChunkStorage::getChunkPosBelow(glm::ivec3 cpos) const
{
	cpos.z = hasColumn(cpos) ? getColumn(cpos).getChunkPosBelow(cpos.z) : 0;
	return cpos;
}

world::Chunk * world::ChunkStorage::getTopmostChunk(const glm::ivec2 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).getTopmostChunk() : nullptr;
}
world::Chunk * world::ChunkStorage::getBottommostChunk(const glm::ivec2 & cpos) const
{
	return hasColumn(cpos) ? getColumn(cpos).getBottommostChunk() : nullptr;
}
glm::ivec3 world::ChunkStorage::getTopmostChunkPos(const glm::ivec2 & cpos) const
{
	return glm::ivec3{ cpos, hasColumn(cpos) ? getColumn(cpos).getTopmostChunkPos() : std::numeric_limits<int>::max() };
}
glm::ivec3 world::ChunkStorage::getBottommostChunkPos(const glm::ivec2 & cpos) const
{
	return glm::ivec3{ cpos, hasColumn(cpos) ? getColumn(cpos).getBottommostChunkPos() : std::numeric_limits<int>::min() };
}

bool world::ChunkStorage::hasColumn(const glm::ivec2 & cpos) const
{
	return m_columns.find(cpos) != m_columns.end();
}
world::ChunkColumn & world::ChunkStorage::getColumn(const glm::ivec2 & cpos)
{
	return m_columns[cpos];
}
const world::ChunkColumn & world::ChunkStorage::getColumn(const glm::ivec2 & cpos) const
{
	const auto it = m_columns.find(cpos);
	if (it == m_columns.end())
		throw std::invalid_argument("Chunk column does not exist");
	return it->second;
}
