
#include "ChunkDataTranslator.h"

world::data::ChunkDataBloated world::data::ChunkDataTranslator::expand(const ChunkDataCompressed & data)
{
	return {};
}
world::data::ChunkDataCompressed world::data::ChunkDataTranslator::compress(const ChunkDataBloated & data)
{
	ChunkDataCompressed result;

	// Compress block data
	ChunkBlockDataNode block = { 1u, data.getBlockFastUnsafe(0u) };
	for (unsigned int i = 1u; i < CHUNK_SIZE_VOLUME<unsigned int>; ++i)
	{
		const auto next = data.getBlockFastUnsafe(i);
		if (block.m_data != next)
		{
			result.m_blocks.push_back(block);
			block.m_data = next;
		}
		++block.m_index;
	}
	result.m_blocks.push_back(block);

	// Compress color data
	ChunkColorDataNode color = { 1u, data.getColorFastUnsafe(0u) };
	for (unsigned int i = 1u; i < CHUNK_SIZE_VOLUME<unsigned int>; ++i)
	{
		const auto next = data.getColorFastUnsafe(i);
		if (color.m_data != next)
		{
			result.m_colors.push_back(color);
			color.m_data = next;
		}
		++color.m_index;
	}
	result.m_colors.push_back(color);

	return result;
}
