
#include "World.h"

#include "logic/event/ChunkEvents.h"
#include "world/data/Light.h"

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

void world::World::propagateLight()
{
	while (!m_markedForLighting.empty())
	{
		std::unordered_set<glm::ivec3> chunks;
		m_markedForLighting.swap(chunks);

		for (const auto & cpos : chunks)
			data::LightPropagator{ *this, cpos }.propagate();
	}
}

// ...

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
	auto & chunk = getColumn({ cpos.x, cpos.y }).createChunk(cpos.z);
	if (m_eventBus != nullptr)
		m_eventBus->post(logic::event::ChunkCreate{ this, cpos });
	return chunk;
}
void world::World::destroyChunk(const glm::ivec3 & cpos)
{
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
world::Chunk * world::World::getChunkAt(const glm::ivec3 & cpos) const
{
	if (!hasColumn(cpos))
		return nullptr;
	return getColumn({ cpos.x, cpos.y }).getChunkAt(cpos.z);
}
world::Chunk * world::World::getChunkAbove(const glm::ivec3 & cpos) const
{
	if (!hasColumn(cpos))
		return nullptr;
	return getColumn({ cpos.x, cpos.y }).getChunkAbove(cpos.z);
}
world::Chunk * world::World::getChunkBelow(const glm::ivec3 & cpos) const
{
	if (!hasColumn(cpos))
		return nullptr;
	return getColumn({ cpos.x, cpos.y }).getChunkBelow(cpos.z);
}

world::Chunk * world::World::getTopmostChunk(const glm::ivec2 & cpos) const
{
	if (!hasColumn(cpos))
		return nullptr;
	return getColumn({ cpos.x, cpos.y }).getTopmostChunk();
}
world::Chunk * world::World::getBottommostChunk(const glm::ivec2 & cpos) const
{
	if (!hasColumn(cpos))
		return nullptr;
	return getColumn({ cpos.x, cpos.y }).getBottommostChunk();
}

// ...

void world::World::write(data::WorldQuery & query)
{
	preconstructChunksOnWriteQuery(*this, query);

	for (auto & q : query)
	{
		auto chunk = getChunkAt(q.first);
		if (chunk != nullptr)
		{
			chunk->write(q.second);
			markAsChanged(q.first, q.second.min(), q.second.max());
		}
	}
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color)
{
	const glm::ivec3 cpos = pos >> data::CHUNK_SIZE_LG<int>;
	const glm::uvec3 bpos = pos & data::CHUNK_SIZE_BITS<int>;

	preconstructChunksAroundPosition(*this, cpos);

	auto chunk = getChunkAt(cpos);
	if (chunk != nullptr)
	{
		chunk->write(bpos, block, color);
		markAsChanged(cpos, bpos, bpos);
	}
}

void world::World::read(data::WorldQuery & query) const
{
	for (auto & q : query)
	{
		auto chunk = getChunkAt(q.first);
		if (chunk != nullptr)
			chunk->read(q.second);
	}
}
void world::World::read(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color) const
{
	auto chunk = getChunkAt(pos >> data::CHUNK_SIZE_LG<int>);
	if (chunk != nullptr)
		chunk->write(pos & data::CHUNK_SIZE_BITS<int>, block, color);
}

void world::World::markForLighting(const glm::ivec3 & cpos)
{
	m_markedForLighting.insert(cpos);
}
void world::World::markAsChanged(const glm::ivec3 & cpos, const glm::uvec3 & min, const glm::uvec3 & max)
{
	markForLighting(cpos);

	if (m_eventBus != nullptr)
		m_eventBus->post(logic::event::ChunkChange{ this, cpos, min, max });
}
