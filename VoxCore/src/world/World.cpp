
#include "World.h"

#include "world/ChunkStorage.h"
#include "world/detail/data/BlockRegion.h"

struct world::World::Impl
{
	BlockRegistry m_registry;
	ChunkStorage m_chunks;

	const logic::event::EventBus * m_bus = nullptr;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;

void world::World::injectEventBus(const logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
}

void world::World::write(data::WorldQuery & query)
{
}
void world::World::read(data::WorldQuery & query) const
{
}

const world::BlockRegistry & world::World::extractBlockRegistry() const
{
	return m_impl->m_registry;
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
