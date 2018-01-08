
#include "World.h"

#include "core/scene/Scene.h"
#include "logic/event/EventBus.h"
#include "world/ChunkStorage.h"
#include "world/detail/data/BlockRegion.h"

struct world::World::Impl
{
	BlockRegistry m_registry;
	ChunkStorage m_chunks;

	core::scene::Scene * m_scene = nullptr;
	const logic::event::EventBus * m_bus = nullptr;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;

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

void world::World::write(data::WorldQuery & query)
{
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block, data::ColorData & color)
{
	auto & chunk = m_impl->m_chunks.createOrGetChunk(pos >> data::CHUNK_SIZE_LG<int>);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block, color);
}
void world::World::write(const glm::ivec3 & pos, data::BlockData & block)
{
	auto & chunk = m_impl->m_chunks.createOrGetChunk(pos >> data::CHUNK_SIZE_LG<int>);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), block);
}
void world::World::write(const glm::ivec3 & pos, data::ColorData & color)
{
	auto & chunk = m_impl->m_chunks.createOrGetChunk(pos >> data::CHUNK_SIZE_LG<int>);
	chunk.write(data::toIndex(pos & data::CHUNK_SIZE_BITS<int>), color);
}
void world::World::read(data::WorldQuery & query) const
{
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
