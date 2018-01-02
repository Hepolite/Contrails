
#include "WorldRenderer.h"

#include "render/world/BlockRenderRegistry.h"
#include "render/world/BlockTextureAtlas.h"

#include "render/world/detail/BlockRenderLoader.h"

struct render::world::WorldRenderer::Impl
{
	BlockRenderRegistry m_blocks;
	BlockTextureAtlas m_atlas;

	const::world::BlockRegistry * m_registry = nullptr;
	logic::event::EventBus * m_bus = nullptr;
};

render::world::WorldRenderer::WorldRenderer()
{
	m_impl = std::make_unique<Impl>();
}
render::world::WorldRenderer::~WorldRenderer() = default;

void render::world::WorldRenderer::injectBlockRegistry(const::world::BlockRegistry & registry)
{
	m_impl->m_registry = &registry;
}
void render::world::WorldRenderer::injectEventBus(logic::event::EventBus & bus)
{
	m_impl->m_bus = &bus;
}

void render::world::WorldRenderer::load(const io::Folder & data)
{
	if (m_impl->m_registry == nullptr)
		throw std::exception("Attempted to load world renderer resources without block registry");

	BlockRenderLoader loader;
	loader.injectBlockRegistry(*m_impl->m_registry);
	loader.injectBlocks(m_impl->m_blocks);
	loader.injectTextureAtlas(m_impl->m_atlas);
	loader.loadBlocks(data);
}
