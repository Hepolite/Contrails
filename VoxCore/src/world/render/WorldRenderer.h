
#pragma once

#include "asset/AssetRef.h"
#include "asset/AssetRegistry.h"
#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"
#include "render/opengl/Program.h"
#include "render/opengl/ubo.h"
#include "render/RenderPass.h"
#include "render/uboRegistry.h"
#include "world/render/BlockRenderRegistry.h"
#include "world/render/BlockTextureAtlas.h"
#include "world/render/detail/meshing/ChunkMesher.h"
#include "world/World.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <memory>
#include <unordered_map>
#include <unordered_set>

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
			void inject(asset::AssetRegistry & assets);
			void inject(logic::event::EventBus & bus);
			void inject(::render::uboRegistry & ubos);

			void load(const io::Folder & data);
			void process();
			void render(::render::RenderPass pass) const;

			inline auto size() { return m_chunks.size(); }

		private:
			void scheduleChunkMeshes();
			void extractChunkMeshes();

			BlockRenderRegistry m_registry;
			BlockTextureAtlas m_texture;
			ChunkMesher m_mesher;

			std::unordered_map<glm::ivec3, std::unique_ptr<ChunkMesh>> m_chunks;
			std::unordered_set<glm::ivec3> m_chunksToMesh;

			asset::Ref<::render::opengl::Program> m_program[::render::RENDER_PASS_COUNT];
			logic::event::Listener m_chunkCreate;
			logic::event::Listener m_chunkChange;
			logic::event::Listener m_chunkDestroy;

			const ::render::opengl::ubo * m_model = nullptr;
			const World * m_world = nullptr;
		};
	}
}