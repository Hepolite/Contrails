
#include "World.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "logic/event/ChunkEvents.h"
#include "util/MathGeneric.h"
#include "world/detail/ChunkStorage.h"
#include "world/detail/BlockLoader.h"
#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/LightPropagation.h"
#include "world/detail/data/WorldQuery.h"

#include <glm/gtx/hash.hpp>
#include <unordered_set>

struct world::World::Impl
{
	BlockRegistry m_registry;
	ChunkStorage m_chunks;

	const logic::event::EventBus * m_bus = nullptr;

	std::unordered_set<glm::ivec3> m_chunksToLight;
	std::unordered_set<glm::ivec3> m_chunksToDarken;
	std::unordered_map<glm::ivec3, std::pair<glm::uvec3, glm::uvec3>> m_chunkChanges;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;

void world::World::load(const io::Folder & data)
{
	BlockLoader loader;
	loader.inject(m_impl->m_registry);
	loader.loadBlocks(data);
}
void world::World::process()
{
	calculateLight();
}

// ...

const world::BlockRegistry & world::World::getBlockRegistry() const
{
	return m_impl->m_registry;
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

world::data::BlockRegion world::World::extractRenderData(const glm::ivec3 & cpos) const
{
	static constexpr auto SIZE = data::CHUNK_SIZE<int>;
	static constexpr auto EDGE = SIZE - 1;

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
			if (m_impl->m_bus != nullptr)
				m_impl->m_bus->post(logic::event::ChunkCreate{ this, pos });
			if (initLight)
				initializeLight(pos);
		}
	}
	return *m_impl->m_chunks.getChunkAt(cpos);
}
void world::World::destroyChunk(const glm::ivec3 & cpos)
{
	glm::ivec3 pos;
	for (pos.x = cpos.x - 1; pos.x <= cpos.x + 1; ++pos.x)
	for (pos.y = cpos.y - 1; pos.y <= cpos.y + 1; ++pos.y)
	for (pos.z = cpos.z - 1; pos.z <= cpos.z + 1; ++pos.z)
	{
		if (emptyNeighborhood(pos))
		{
			if (m_impl->m_bus != nullptr)
				m_impl->m_bus->post(logic::event::ChunkDestroy { this, pos });
			m_impl->m_chunks.destroyChunk(pos);
		}
	}
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
glm::ivec3 world::World::getChunkPosAbove(glm::ivec3 cpos) const
{
	return m_impl->m_chunks.getChunkPosAbove(cpos);
}
glm::ivec3 world::World::getChunkPosBelow(glm::ivec3 cpos) const
{
	return m_impl->m_chunks.getChunkPosBelow(cpos);
}

world::Chunk * world::World::getTopmostChunk(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getTopmostChunk(cpos);
}
world::Chunk * world::World::getBottommostChunk(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getBottommostChunk(cpos);
}
glm::ivec3 world::World::getTopmostChunkPos(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getTopmostChunkPos(cpos);
}
glm::ivec3 world::World::getBottommostChunkPos(const glm::ivec2 & cpos) const
{
	return m_impl->m_chunks.getBottommostChunkPos(cpos);
}

bool world::World::emptyNeighborhood(const glm::ivec3 & cpos) const
{
	glm::ivec3 pos;
	for (pos.x = cpos.x - 1; pos.x <= cpos.x + 1; ++pos.x)
	for (pos.y = cpos.y - 1; pos.y <= cpos.y + 1; ++pos.y)
	for (pos.z = cpos.z - 1; pos.z <= cpos.z + 1; ++pos.z)
	{
		const auto * chunk = getChunkAt(pos);
		if (chunk != nullptr && !chunk->empty())
			return false;
	}
	return true;
}

// ...

void world::World::write(data::WorldQuery & query)
{
	for (auto & it : query)
	{
		createChunk(it.first, true).write(it.second);
		handleChunkChange(it.first, it.second.min(), it.second.max());
	}
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block, color);
	handleChunkChange(cpos, pos, pos);
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block);
	handleChunkChange(cpos, pos, pos);
}
void world::World::write(const glm::ivec3 & pos, data::ColorData & color)
{
	const auto cpos = pos >> data::CHUNK_SIZE_LG<int>;
	auto & chunk = createChunk(cpos);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), color);
	handleChunkChange(cpos, pos, pos);
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

void world::World::handleChunkChange(const glm::ivec3 & cpos, const glm::ivec3 & min, const glm::ivec3 & max)
{
	markLightPropagation(cpos);
	markLightRemoval(cpos);
	markLightPropagation(cpos);
	markChunkChange(cpos, min, max);

	const auto * chunk = getChunkAt(cpos);
	if (chunk != nullptr && chunk->empty())
		destroyChunk(cpos);
}

// ...

void world::World::markChunkChange(const glm::ivec3 & cpos)
{
	markChunkChange(cpos, glm::uvec3{}, glm::uvec3{ data::CHUNK_SIZE_BITS<unsigned int> });
}
void world::World::markChunkChange(const glm::ivec3 & cpos, const glm::uvec3 & min, const glm::uvec3 & max)
{
	if (m_impl->m_bus != nullptr)
		m_impl->m_bus->post(logic::event::ChunkChange { this, cpos, min, max });
}
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
			const auto light = above->readBlock(index).getLight();
			const auto color = above->readColor(index).getColor();
			above->pushLightPropagation({ index, light }, data::LIGHT_PROPAGATION_CHANNEL_SUN);
			above->pushLightPropagation({ index, (color.r << 16u) | (color.g << 8u) | color.b }, data::LIGHT_PROPAGATION_CHANNEL_COLOR);
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
	markChunkChange(cpos);
}
void world::World::calculateLight()
{
	while (!m_impl->m_chunksToDarken.empty())
	{
		std::unordered_set<glm::ivec3> chunks;
		std::swap(m_impl->m_chunksToDarken, chunks);

		for (auto & it : chunks)
		{
			if (auto * chunk = getChunkAt(it))
			{
				data::LightSunRemover{ *this, it }.spread(*chunk);
				data::LightColorRemover{ *this, it }.spread(*chunk);
				markChunkChange(it);
			}
		}
	}
	while (!m_impl->m_chunksToLight.empty())
	{
		std::unordered_set<glm::ivec3> chunks;
		std::swap(m_impl->m_chunksToLight, chunks);

		for (auto & it : chunks)
		{
			if (auto * chunk = getChunkAt(it))
			{
				data::LightSunPropagator{ *this, it }.spread(*chunk);
				data::LightColorPropagator{ *this, it }.spread(*chunk);
				markChunkChange(it);
			}
		}
	}
}
