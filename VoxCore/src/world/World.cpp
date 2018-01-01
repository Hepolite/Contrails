
#include "World.h"

#include "world/ChunkStorage.h"

struct world::World::Impl
{
	ChunkStorage m_chunks;

	const BlockRegistry * m_registry = nullptr;
	const logic::event::EventBus * m_eventBus = nullptr;
};

world::World::World()
{
	m_impl = std::make_unique<Impl>();
}
world::World::World(World &&) noexcept = default;
world::World::~World() = default;

world::World & world::World::operator=(World &&) noexcept = default;