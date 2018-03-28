
#pragma once

#include "world/detail/data/BlockData.h"
#include "world/detail/Limits.h"
#include "world/render/BlockRenderRegistry.h"
#include "world/render/detail/data/TextureData.h"
#include "world/render/detail/meshing/ChunkMeshTask.h"
#include "world/util/Side.h"

#include <array>

namespace world
{
	namespace render
	{
		using BlockData = ::world::data::BlockData;
		using ColorData = ::world::data::ColorData;
		using TextureData = data::TextureData;

		using BlockRegion = ::world::data::BlockRegion;
		using Side = ::world::util::Side;

		struct MeshFace
		{
			glm::uvec2 m_pos;
			glm::uvec2 m_size;
			BlockData m_block;
			ColorData m_color;
			TextureData m_texture;
		};

		class LayerData
		{
		public:
			inline bool operator==(const LayerData & other) const { return m_data == other.m_data; }
			inline bool operator!=(const LayerData & other) const { return m_data != other.m_data; }

			void set(const BlockData & block, const ColorData & color, const TextureData & texture);
			BlockData getBlock() const;
			ColorData getColor() const;
			TextureData getTexture() const;

			inline void erase() { m_data = 0ull; }
			inline auto empty() const { return m_data == 0ull; }

		private:
			uint64_t m_data = 0ull;
		};

		class LayerMask
		{
		public:
			void put(const glm::uvec2 & pos, const LayerData & data);
			LayerData get(const glm::uvec2 & pos) const;

			bool extract(MeshFace & face);

		private:
			void erase(const glm::uvec2 & start, const glm::uvec2 & end);
			bool findExtractionPos();
			glm::uvec2 getExtractionSize() const;

			std::array<LayerData, ::world::data::CHUNK_SIZE_AREA<unsigned int>> m_data;
			glm::uvec2 m_pos{};
		};

		// ...

		class NaiveGreedyMesher
		{
		public:
			inline void inject(ChunkMesh & mesh) { m_mesh = &mesh; }
			inline void inject(const BlockRegion & data) { m_data = &data; }
			inline void inject(const BlockRenderRegistry & renders) { m_renders = &renders; }

			void build();
			void buildLayer(unsigned int layer, LayerMask && mask, const Side & side);
			void buildFace(const glm::ivec3 & pos, const MeshFace & face, const Side & side);

			LayerMask getLayerMask(unsigned int layer, const Side & side) const;
			LayerData getLayerData(const glm::ivec3 & pos, const Side & side) const;

		private:
			ChunkMesh * m_mesh;
			const BlockRegion * m_data;
			const BlockRenderRegistry * m_renders;

			unsigned int m_offsetIndex[::render::RENDER_PASS_COUNT] = { 0u };
		};
	}
}