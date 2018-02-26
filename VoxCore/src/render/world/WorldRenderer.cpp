
#include "WorldRenderer.h"

#include "logic/event/ChunkEvents.h"
#include "render/world/BlockRenderRegistry.h"
#include "render/world/BlockTextureAtlas.h"
#include "render/world/detail/BlockRenderLoader.h"
#include "render/world/detail/meshing/ChunkMesher.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <plog/Log.h>
#include <glm/gtx/hash.hpp>
#include <unordered_map>

class render::world::WorldRenderer::Impl
{
public:
	void process();

	void scheduleChunkMeshing(const glm::ivec3 & cpos);
	void injectMesh(const glm::ivec3 & cpos, std::unique_ptr<ChunkMesh> && mesh);
	void eraseMesh(const glm::ivec3 & cpos);

	BlockRenderRegistry m_blocks;
	BlockTextureAtlas m_atlas;
	ChunkMesher m_mesher;

	const ::world::World * m_world = nullptr;

	::logic::event::EventBus * m_bus = nullptr;
	logic::event::Listener m_chunkCreate;
	logic::event::Listener m_chunkChange;
	logic::event::Listener m_chunkDestroy;

private:
	std::unordered_map<glm::ivec3, std::unique_ptr<ChunkMesh>> m_chunks;
};

void render::world::WorldRenderer::Impl::process()
{
	ChunkMeshTask task;
	while (m_mesher.extractTask(task))
		injectMesh(task.m_cpos, std::move(task.m_mesh));
}

void render::world::WorldRenderer::Impl::scheduleChunkMeshing(const glm::ivec3 & cpos)
{
	m_mesher.scheduleTask({ cpos, m_world->extractRenderData(cpos), {} });
}

void render::world::WorldRenderer::Impl::injectMesh(const glm::ivec3 & cpos, std::unique_ptr<ChunkMesh> && mesh)
{
	m_chunks[cpos] = std::move(mesh);
}
void render::world::WorldRenderer::Impl::eraseMesh(const glm::ivec3 & cpos)
{
	m_chunks.erase(cpos);
}

// ...

render::world::WorldRenderer::WorldRenderer()
{
	m_impl = std::make_unique<Impl>();
}
render::world::WorldRenderer::WorldRenderer(WorldRenderer &&) noexcept = default;
render::world::WorldRenderer::~WorldRenderer() = default;

void render::world::WorldRenderer::inject(::logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
	m_impl->m_chunkCreate = bus.add<logic::event::ChunkCreate>([this](auto & event)
	{
		if (m_impl->m_world == event.m_world)
			m_impl->scheduleChunkMeshing(event.m_cpos);
	});
	m_impl->m_chunkCreate = bus.add<logic::event::ChunkChange>([this](auto & event)
	{
		if (m_impl->m_world == event.m_world)
			m_impl->scheduleChunkMeshing(event.m_cpos);
	});
	m_impl->m_chunkDestroy = bus.add<logic::event::ChunkDestroy>([this](auto & event)
	{
		if (m_impl->m_world == event.m_world)
			m_impl->eraseMesh(event.m_cpos);
	});
}
void render::world::WorldRenderer::inject(const ::world::World & world)
{
	m_impl->m_world = &world;
}

void render::world::WorldRenderer::load(const io::Folder & data)
{
	if (m_impl->m_world == nullptr)
	{
		LOG_WARNING << "Attempted to load world renderer before world has been injected";
		return;
	}

	BlockRenderLoader loader;
	loader.inject(m_impl->m_world->getBlockRegistry());
	loader.inject(m_impl->m_blocks);
	loader.inject(m_impl->m_atlas);
	loader.loadBlocks(data);
}
