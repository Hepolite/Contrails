
#include "World.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "world/detail/ChunkStorage.h"
#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/LightPropagation.h"
#include "world/detail/data/WorldQuery.h"

#include <glm/gtx/hash.hpp>
#include <unordered_set>

struct world::World::Impl
{
	BlockRegistry m_registry;
	ChunkStorage m_chunks;

	core::scene::Scene * m_scene = nullptr;
	const logic::event::EventBus * m_bus = nullptr;

	std::unordered_set<glm::ivec3> m_chunksToLight;
	std::unordered_set<glm::ivec3> m_chunksToDarken;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;

// ...

const world::BlockRegistry & world::World::getBlockRegistry() const
{
	return m_impl->m_registry;
}

void world::World::inject(core::scene::Scene & scene)
{
	m_impl->m_scene = &scene;
}
void world::World::inject(const logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
}
void world::World::inject(const BlockRegistry & registry)
{
	for (unsigned int i = 1u; i < registry.size(); ++i)
	{
		const auto & block = registry[i];
		auto & newBlock = m_impl->m_registry.add(block.m_name, block.m_id);
		newBlock.m_phase = block.m_phase;
		newBlock.m_lightAbsorbed = block.m_lightAbsorbed;
		newBlock.m_lightEmitted = block.m_lightEmitted;
		newBlock.m_lightFiltered = block.m_lightFiltered;
	}
}

const world::data::BlockRegion world::World::extractRenderData(const glm::ivec3 & cpos) const
{
	constexpr const auto SIZE = data::CHUNK_SIZE<int>;
	constexpr const auto EDGE = SIZE - 1;

	data::BlockRegion region{ glm::ivec3{ -1 }, glm::ivec3{ data::CHUNK_SIZE<int> + 2 } };

	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos))
		chunk->read(region, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ SIZE, SIZE, SIZE });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos - glm::ivec3{ 1, 0, 0 }))
		chunk->read(region, glm::ivec3{ EDGE, 0, 0 }, glm::ivec3{ -1, 0, 0 }, glm::ivec3{ 1, SIZE, SIZE });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos + glm::ivec3{ 1, 0, 0 }))
		chunk->read(region, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ SIZE, 0, 0 }, glm::ivec3{ 1, SIZE, SIZE });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos - glm::ivec3{ 0, 1, 0 }))
		chunk->read(region, glm::ivec3{ 0, EDGE, 0 }, glm::ivec3{ 0, -1, 0 }, glm::ivec3{ SIZE, 1, SIZE });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos + glm::ivec3{ 0, 1, 0 }))
		chunk->read(region, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, SIZE, 0 }, glm::ivec3{ SIZE, 1, SIZE });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos - glm::ivec3{ 0, 0, 1 }))
		chunk->read(region, glm::ivec3{ 0, 0, EDGE }, glm::ivec3{ 0, 0, -1 }, glm::ivec3{ SIZE, SIZE, 1 });
	if (const auto chunk = m_impl->m_chunks.getChunkAt(cpos + glm::ivec3{ 0, 0, 1 }))
		chunk->read(region, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 0, SIZE }, glm::ivec3{ SIZE, SIZE, 1 });

	return region;
}

// ...

world::Chunk & world::World::createChunk(const glm::ivec3 & cpos, bool initLight)
{
	glm::ivec3 pos;
	for (pos.x = cpos.x - 1; pos.x <= cpos.x + 1; ++pos.x)
	for (pos.y = cpos.y - 1; pos.y <= cpos.y + 1; ++pos.y)
	for (pos.z = cpos.z - 1; pos.z <= cpos.z + 1; ++pos.z)
	{
		if (!m_impl->m_chunks.hasChunkAt(pos))
		{
			m_impl->m_chunks.createChunk(pos);
			if (initLight)
				initializeLight(pos);
		}
	}
	return *m_impl->m_chunks.getChunkAt(cpos);
}
void world::World::destroyChunk(const glm::ivec3 & cpos)
{
	m_impl->m_chunks.destroyChunk(cpos);
}

bool world::World::hasChunkAt(const glm::ivec3 & cpos) const
{
	return m_impl->m_chunks.hasChunkAt(cpos);
}
world::Chunk * world::World::getChunkAt(const glm::ivec3 & cpos) const
{
	return m_impl->m_chunks.getChunkAt(cpos);
}
world::Chunk * world::World::getChunkAbove(const glm::ivec3 & cpos) const
{
	return m_impl->m_chunks.getChunkAbove(cpos);
}
world::Chunk * world::World::getChunkBelow(const glm::ivec3 & cpos) const
{
	return m_impl->m_chunks.getChunkBelow(cpos);
}

world::Chunk * world::World::getTopmostChunk(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getTopmostChunk(cpos);
}
world::Chunk * world::World::getBottommostChunk(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getBottommostChunk(cpos);
}

// ...

void world::World::write(data::WorldQuery & query)
{
	for (auto & it : query)
	{
		createChunk(it.first, true).write(it.second);
		markLightRemoval(it.first);
		markLightPropagation(it.first);
	}
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block, color);
	markLightRemoval(cpos);
	markLightPropagation(cpos);
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block);
	markLightRemoval(cpos);
	markLightPropagation(cpos);
}
void world::World::write(const glm::ivec3 & pos, data::ColorData & color)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), color);
	markLightRemoval(cpos);
	markLightPropagation(cpos);
}

void world::World::read(data::WorldQuery & query) const
{
	for (auto & it : query)
	{
		if (const auto * chunk = m_impl->m_chunks.getChunkAt(it.first))
			chunk->read(it.second);
	}
}
world::data::BlockData world::World::readBlock(const glm::ivec3 & pos) const
{
	auto chunk = m_impl->m_chunks.getChunkAt(pos >> data::CHUNK_SIZE_LG<int>);
	if (chunk == nullptr)
		return data::BlockData{};
	return chunk->readBlock(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>));
}
world::data::ColorData world::World::readColor(const glm::ivec3 & pos) const
{
	auto chunk = m_impl->m_chunks.getChunkAt(pos >> data::CHUNK_SIZE_LG<int>);
	if (chunk == nullptr)
		return data::ColorData{};
	return chunk->readColor(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>));
}

// ...

void world::World::markLightPropagation(const glm::ivec3 & cpos)
{
	m_impl->m_chunksToLight.insert(cpos);
}
void world::World::markLightRemoval(const glm::ivec3 & cpos)
{
	m_impl->m_chunksToDarken.insert(cpos);
}

void world::World::initializeLight(const glm::ivec3 & cpos)
{
	auto * chunk = getChunkAt(cpos);
	if (chunk == nullptr)
		return;

	if (auto * above = m_impl->m_chunks.getChunkAbove(cpos))
	{
		glm::uvec3 pos{ 0, 0, 0 };
		for (pos.x = 0u; pos.x < data::CHUNK_SIZE<unsigned int>; ++pos.x)
		for (pos.y = 0u; pos.y < data::CHUNK_SIZE<unsigned int>; ++pos.y)
		{
			const auto index = data::toIndex(pos);
			const auto block = above->readBlock(index);
			const auto color = above->readColor(index);
			above->pushLightPropagation({ index, block.getLight() }, 0u);
			above->pushLightPropagation({ index, color.getColor().r }, 1u);
			above->pushLightPropagation({ index, color.getColor().g }, 2u);
			above->pushLightPropagation({ index, color.getColor().b }, 3u);
		}
		markLightPropagation(m_impl->m_chunks.getChunkPosAbove(cpos));
	}
	else
	{
		glm::uvec3 pos;
		for (pos.x = 0u; pos.x < data::CHUNK_SIZE<unsigned int>; ++pos.x)
		for (pos.y = 0u; pos.y < data::CHUNK_SIZE<unsigned int>; ++pos.y)
		for (pos.z = 0u; pos.z < data::CHUNK_SIZE<unsigned int>; ++pos.z)
			chunk->setFastUnsafe(data::toIndex(pos), data::BlockData{ 0u, data::MAX_BLOCK_LIGHT }, data::ColorData{});
	}
}
void world::World::calculateLight()
{
	while (!m_impl->m_chunksToDarken.empty())
	{
		std::unordered_set<glm::ivec3> m_chunks;
		std::swap(m_impl->m_chunksToDarken, m_chunks);

		for (auto & it : m_chunks)
			;
	}
	while (!m_impl->m_chunksToLight.empty())
	{
		std::unordered_set<glm::ivec3> m_chunks;
		std::swap(m_impl->m_chunksToLight, m_chunks);

		for (auto & it : m_chunks)
			;
	}
}