
#include "World.h"

#include "world/ChunkStorage.h"

struct world::World::Impl
{
	BlockRegistry m_registry;
	ChunkStorage m_chunks;

	const logic::event::EventBus * m_eventBus = nullptr;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;