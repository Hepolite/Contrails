
#pragma once

#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"
#include "render/RenderPass.h"
#include "world/render/BlockRenderRegistry.h"
#include "world/render/BlockTextureAtlas.h"
#include "world/render/detail/meshing/ChunkMesher.h"
#include "world/World.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <memory>
#include <unordered_map>

namespace world
{
	namespace render
	{
		class WorldRenderer
		{
		public:
			WorldRenderer();
			WorldRenderer(const WorldRenderer &) = delete;
			WorldRenderer(WorldRenderer &&) noexcept = default;
			~WorldRenderer() = default;

			WorldRenderer & operator=(const WorldRenderer &) = delete;
			WorldRenderer & operator=(WorldRenderer &&) noexcept = default;

			void inject(const World & world);
			void inject(logic::event::EventBus & bus);

			void load(const io::Folder & data);
			void process();
			void render(::render::RenderPass pass) const;

			inline auto size() { return m_chunks.size(); }

		private:
			void handleChunkMeshes();

			BlockRenderRegistry m_registry;
			BlockTextureAtlas m_texture;
			ChunkMesher m_mesher;

			std::unordered_map<glm::ivec3, std::unique_ptr<ChunkMesh>> m_chunks;

			logic::event::Listener m_chunkCreate;
			logic::event::Listener m_chunkChange;
			logic::event::Listener m_chunkDestroy;

			const World * m_world = nullptr;
		};
	}
}