
#pragma once

#include "io/File.h"
#include "io/Folder.h"
#include "world/BlockRegistry.h"
#include "world/detail/Block.h"

#include <pugixml/pugixml.hpp>

namespace world
{
	class BlockLoader
	{
	public:
		inline void injectBlockRegistry(BlockRegistry & registry) { m_registry = &registry; }

		void loadBlocks(const io::Folder & folder) const;
		void loadBlock(const io::File & file) const;

	private:
		BlockRegistry * m_registry = nullptr;
	};

	class BlockVariantLoader
	{
	public:
		void loadVariant(Block & block, const pugi::xml_node & variant, const pugi::xml_node & def) const;

	private:
		void loadLight(Block & block, const pugi::xml_node & light, const pugi::xml_node & def) const;
	};
}