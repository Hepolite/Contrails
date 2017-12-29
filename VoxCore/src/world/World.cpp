
#include "World.h"

#include "logic/event/ChunkEvents.h"

namespace
{
	void preconstructChunksAroundPosition(world::World & world, const glm::ivec3 & cpos)
	{
		glm::ivec3 cp;
		for (cp.x = cpos.x - 1; cp.x <= cpos.x + 1; ++cp.x)
		for (cp.y = cpos.y - 1; cp.y <= cpos.y + 1; ++cp.y)
		for (cp.z = cpos.z - 1; cp.z <= cpos.z + 1; ++cp.z)
		{
			if (!world.hasChunkAt(cp))
				world.createChunk(cp);
		}
	}
	void preconstructChunksOnWriteQuery(world::World & world, world::data::WorldQuery & query)
	{
		for (const auto & it : query)
			preconstructChunksAroundPosition(world, it.first);
	}
}

bool world::World::hasColumn(const glm::ivec2 & cpos) const
{
	return m_columns.find(cpos) != m_columns.end();
}
world::ChunkColumn & world::World::getColumn(const glm::ivec2 & cpos)
{
	return m_columns[cpos];
}
const world::ChunkColumn & world::World::getColumn(const glm::ivec2 & cpos) const
{
	return m_columns.find(cpos)->second;
}

// ...

world::Chunk & world::World::createChunk(const glm::ivec3 & cpos)
{
	if (hasChunkAt(cpos))
		throw std::invalid_argument("Chunk already exists at the given position");

	auto & chunk = getColumn({ cpos.x, cpos.y }).createChunk(cpos.z);
	if (m_eventBus != nullptr)
		m_eventBus->post(logic::event::ChunkCreate{ this, cpos });
	return chunk;
}
void world::World::destroyChunk(const glm::ivec3 & cpos)
{
	if (!hasChunkAt(cpos))
		throw std::invalid_argument("Chunk does not exist at the given position");

	if (m_eventBus != nullptr)
		m_eventBus->post(logic::event::ChunkDestroy{ this, cpos });
	getColumn({ cpos.x, cpos.y }).destroyChunk(cpos.z);
}

bool world::World::hasChunkAt(const glm::ivec3 & cpos) const
{
	if (!hasColumn(cpos))
		return false;
	return getColumn({ cpos.x, cpos.y }).hasChunkAt(cpos.z);
}
world::Chunk * world::World::getChunkAt(const glm::ivec3 & cpos)
{
	return getColumn({ cpos.x, cpos.y }).getChunkAt(cpos.z);
}
world::Chunk * world::World::getChunkAbove(const glm::ivec3 & cpos)
{
	return getColumn({ cpos.x, cpos.y }).getChunkAbove(cpos.z);
}
world::Chunk * world::World::getChunkBelow(const glm::ivec3 & cpos)
{
	return getColumn({ cpos.x, cpos.y }).getChunkBelow(cpos.z);
}

world::Chunk * world::World::getTopmostChunk(const glm::ivec2 & cpos)
{
	return getColumn({ cpos.x, cpos.y }).getTopmostChunk();
}
world::Chunk * world::World::getBottommostChunk(const glm::ivec2 & cpos)
{
	return getColumn({ cpos.x, cpos.y }).getBottommostChunk();
}

// ...


void world::World::write(data::WorldQuery & query)
{
	preconstructChunksOnWriteQuery(*this, query);
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color)
{
	preconstructChunksAroundPosition(*this, pos >> data::CHUNK_SIZE_LG<int>);
}

void world::World::read(data::WorldQuery & query) const
{
}
void world::World::read(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color) const
{
}