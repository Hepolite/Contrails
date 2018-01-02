
#pragma once

#include "world/detail/data/BlockData.h"
#include "world/detail/Limits.h"

#include <glm/vec3.hpp>
#include <vector>

namespace world
{
	namespace data
	{
		class BlockRegion
		{
		public:
			BlockRegion();
			BlockRegion(const glm::ivec3 & position, const glm::ivec3 & size);
			BlockRegion(const BlockRegion &) = delete;
			BlockRegion(BlockRegion &&) noexcept = default;
			~BlockRegion() noexcept = default;

			unsigned int memuse() const;

			BlockRegion & operator=(const BlockRegion &) = delete;
			BlockRegion & operator=(BlockRegion &&) noexcept = default;

			void write(const glm::ivec3 & pos, BlockData & block, ColorData & color);
			void write(const glm::ivec3 & pos, BlockData & block);
			void write(const glm::ivec3 & pos, ColorData & color);
			BlockData readBlock(const glm::ivec3 & pos) const;
			ColorData readColor(const glm::ivec3 & pos) const;

		private:
			std::vector<BlockData> m_blocks;
			std::vector<ColorData> m_colors;

			const glm::ivec3 m_pos;
			const glm::ivec3 m_size;
		};
	}
}