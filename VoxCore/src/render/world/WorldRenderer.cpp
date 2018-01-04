
#include "WorldRenderer.h"

#include "render/world/BlockRenderRegistry.h"
#include "render/world/BlockTextureAtlas.h"
#include "render/world/detail/BlockRenderLoader.h"
/*
struct render::world::WorldRenderer::Impl
{
	BlockRenderRegistry m_blocks;
	BlockTextureAtlas m_atlas;

	::world::World * m_world = nullptr;
	logic::event::EventBus * m_bus = nullptr;
};
*/
render::world::WorldRenderer::WorldRenderer()
{
	//m_impl = std::make_unique<Impl>();
}
render::world::WorldRenderer::~WorldRenderer() = default;

void render::world::WorldRenderer::inject(logic::event::EventBus & bus)
{
	//m_impl->m_bus = &bus;
}
void render::world::WorldRenderer::inject(::world::World & world)
{
	//m_impl->m_world = &world;
}

void render::world::WorldRenderer::load(const ::world::BlockRegistry & registry, const io::Folder & data)
{
	BlockRenderLoader loader;
	loader.inject(registry);
	//loader.inject(m_impl->m_blocks);
	//loader.inject(m_impl->m_atlas);
	loader.loadBlocks(data);
}
