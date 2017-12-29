
#pragma once

#include "world/Block.h"

#include <string>
#include <vector>
#include <unordered_map>

namespace world
{
	class BlockRegistry
	{
	public:
		BlockRegistry() = default;
		BlockRegistry(const BlockRegistry &) = delete;
		BlockRegistry(BlockRegistry &&) = delete;
		~BlockRegistry() = default;

		BlockRegistry & operator=(const BlockRegistry &) = delete;
		BlockRegistry & operator=(BlockRegistry &&) = delete;

		inline auto size() const { return m_blocks.size(); }

		Block & add(const std::string & name);
		Block & add(const std::string & name, unsigned int id);

		const Block & operator[](const unsigned int & id) const;
		const Block & operator[](const std::string & name) const;

	private:
		std::vector<Block> m_blocks{ 1 };
		std::unordered_map<std::string, unsigned int> m_nameToIdMap{ { "air", 0u } };
	};
}