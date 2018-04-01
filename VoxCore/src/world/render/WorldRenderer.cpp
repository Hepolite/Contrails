
#include "WorldRenderer.h"

#include "logic/event/ChunkEvents.h"
#include "world/render/detail/BlockRenderLoader.h"
#include "world/detail/Limits.h"

#include <glm/gtc/matrix_transform.hpp>
#include <plog/Log.h>

world::render::WorldRenderer::WorldRenderer()
{
	m_mesher.inject(m_registry);
}

void world::render::WorldRenderer::inject(const World & world)
{
	m_world = &world;
}
void world::render::WorldRenderer::inject(logic::event::EventBus & bus)
{
	m_chunkCreate = bus.add<logic::event::ChunkCreate>([this](auto & event) { m_chunks[event.m_cpos] = nullptr; });
	m_chunkDestroy = bus.add<logic::event::ChunkDestroy>([this](auto & event) { m_chunks.erase(event.m_cpos); });
	m_chunkChange = bus.add<logic::event::ChunkChange>([this](auto & event)
	{
		if (m_world == event.m_world)
			m_mesher.scheduleTask({ event.m_cpos, m_world->extractRenderData(event.m_cpos), std::make_unique<ChunkMesh>() });
	});
}
void world::render::WorldRenderer::inject(asset::AssetRegistry & assets)
{
	for (unsigned int i = 0u; i < ::render::RENDER_PASS_COUNT; ++i)
		m_program[i] = assets.get<::render::opengl::Program>("world_chunk");
}
void world::render::WorldRenderer::inject(::render::uboRegistry & ubos)
{
	m_model = &ubos.get("Model");
}

void world::render::WorldRenderer::load(const io::Folder & data)
{
	if (m_world == nullptr)
	{
		LOG_WARNING << "Attempted to load world renderer before world has been injected";
		return;
	}

	BlockRenderLoader loader;
	loader.inject(m_world->getBlockRegistry());
	loader.inject(m_registry);
	loader.inject(m_texture);
	loader.loadBlocks(data);

	m_texture.build();
}

void world::render::WorldRenderer::process()
{
	handleChunkMeshes();
}
void world::render::WorldRenderer::render(::render::RenderPass pass) const
{
	m_program[static_cast<int>(pass)]->bind();
	m_texture.bind();
	for (const auto & it : m_chunks)
	{
		if (it.second != nullptr)
		{
			m_model->set("transform", glm::translate(glm::mat4{ 1.0f }, glm::vec3{ it.first * world::data::CHUNK_SIZE<int> }));
			(*it.second)[static_cast<unsigned int>(pass)].render();
		}
	}
}

void world::render::WorldRenderer::handleChunkMeshes()
{
	ChunkMeshTask task;
	while (m_mesher.extractTask(task))
	{
		if (m_chunks.find(task.m_cpos) == m_chunks.end())
			continue;

		for (unsigned int i = 0u; i < ::render::RENDER_PASS_COUNT; ++i)
		{
			auto & mesh = (*task.m_mesh)[i];
			mesh.addAttribute({ 0u, ::render::opengl::DataFormat::FLOAT, 3u, 0u });
			mesh.addAttribute({ 1u, ::render::opengl::DataFormat::FLOAT, 3u, 12u });
			mesh.addAttribute({ 2u, ::render::opengl::DataFormat::FLOAT, 3u, 24u });
			mesh.addAttribute({ 3u, ::render::opengl::DataFormat::FLOAT, 4u, 36u });
			mesh.build();
		}
		m_chunks[task.m_cpos] = std::move(task.m_mesh);
	}
}
