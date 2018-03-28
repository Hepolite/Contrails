
#include "BlockRenderRegistry.h"

#include "world/detail/Limits.h"

world::render::data::BlockRender & world::render::BlockRenderRegistry::operator[](const unsigned int & id)
{
	if (id >= ::world::data::MAX_BLOCK_ID)
		throw std::out_of_range("Block id out of bounds");
	if (id >= m_blocks.size())
	{
		m_blocks.reserve(id);
		for (unsigned int i = m_blocks.size(); i <= id; ++i)
			m_blocks.emplace_back();
	}
	return m_blocks[id];
}
const world::render::data::BlockRender & world::render::BlockRenderRegistry::operator[](const unsigned int & id) const
{
	if (id >= m_blocks.size())
		throw std::out_of_range("Block id out of bounds");
	return m_blocks[id];
}