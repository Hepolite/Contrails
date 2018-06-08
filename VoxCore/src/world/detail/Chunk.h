
#pragma once

#include <glm/vec3.hpp>
#include <memory>

namespace world
{
	namespace data
	{
		class BlockData;
		class BlockRegion;
		class ColorData;
		class ChunkDataBloated;
		class ChunkDataCompressed;
		class ChunkQuery;
		struct LightPropagationNode;
	}

	class Chunk
	{
	public:
		Chunk();
		Chunk(const Chunk &) = delete;
		Chunk(Chunk &&) = delete;
		~Chunk();

		Chunk & operator=(const Chunk &) = delete;
		Chunk & operator=(Chunk &&) = delete;

		void compress();
		void expand();

		void setFastUnsafe(unsigned int index, const data::BlockData & block, const data::ColorData & color);
		void setFastUnsafe(unsigned int index, const data::BlockData & block);
		void setFastUnsafe(unsigned int index, const data::ColorData & color);
		void write(data::ChunkQuery & query);
		void write(unsigned int index, data::BlockData & block, data::ColorData & color);
		void write(unsigned int index, data::BlockData & block);
		void write(unsigned int index, data::ColorData & color);
		void read(data::ChunkQuery & query) const;
		void read(data::BlockRegion & region, const glm::ivec3 & source, const glm::ivec3 & target, const glm::ivec3 & size) const;
		data::BlockData readBlock(unsigned int index) const;
		data::ColorData readColor(unsigned int index) const;
		data::ChunkDataCompressed readData() const;

		bool pollLightPropagation(data::LightPropagationNode & node, unsigned int channel);
		void pushLightPropagation(const data::LightPropagationNode & node, unsigned int channel);
		bool pollLightRemoval(data::LightPropagationNode & node, unsigned int channel);
		void pushLightRemoval(const data::LightPropagationNode & node, unsigned int channel);

		bool empty() const;
		bool compressed() const;

	private:
		std::unique_ptr<data::ChunkDataBloated> m_bloated;
		std::unique_ptr<data::ChunkDataCompressed> m_compressed;
	};
}