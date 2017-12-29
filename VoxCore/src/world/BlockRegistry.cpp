
#include "BlockRegistry.h"

#include "world/data/Limits.h"

world::Block & world::BlockRegistry::add(const std::string & name)
{
	for (auto i = 1u; i < size(); ++i)
	{
		if (m_blocks[i].m_id == 0u)
			return add(name, i);
	}
	return add(name, size());
}
world::Block & world::BlockRegistry::add(const std::string & name, unsigned int id)
{
	if (id == 0u || name == "air")
		throw std::invalid_argument("Name 'air' and id '0' are reserved");
	if (id > data::MAX_BLOCK_ID)
		throw std::invalid_argument("Id is out of bounds (range 0 to MAX_BLOCK_ID)");

	while (size() <= id)
		m_blocks.emplace_back();

	Block block;
	block.m_id = id;
	block.m_name = name;

	m_nameToIdMap.emplace(name, id);
	return m_blocks[id] = std::move(block);
}

const world::Block & world::BlockRegistry::operator[](const unsigned int & id) const
{
	return m_blocks[id >= size() ? 0u : id];
}
const world::Block & world::BlockRegistry::operator[](const std::string & name) const
{
	const auto it = m_nameToIdMap.find(name);
	return m_blocks[it == m_nameToIdMap.end() ? 0u : it->second];
}
