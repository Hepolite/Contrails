
#include "RegionLoader.h"

#include "world/detail/data/ChunkData.h"
#include "world/detail/Limits.h"
#include "world/World.h"

#include <fstream>

namespace
{
	io::File getRegionFile(const io::Folder & root, const glm::ivec3 & rpos, const std::string & extension)
	{
		const auto name = std::to_string(rpos.x) + "_" + std::to_string(rpos.y) + "_" + std::to_string(rpos.z);
		return { root.getPath() + "/" + name + "." + extension };
	}
}

void world::io::RegionLoader::read(World & world, const glm::ivec3 & rpos) const
{
	const auto file = getRegionFile(m_root, rpos, "rvd");
	if (!file.exists())
		return;

	std::fstream stream{ file.getPath(), std::ios::in | std::ios::binary };
	if (!stream.is_open())
		return;

	while (!stream.eof())
	{
		glm::ivec3 pos;
		stream.read(reinterpret_cast<char *>(&pos), sizeof(pos));

		size_t blocks, colors;
		stream.read(reinterpret_cast<char *>(&blocks), sizeof(blocks));
		stream.read(reinterpret_cast<char *>(&colors), sizeof(colors));

		data::ChunkDataCompressed data;
		for (size_t i = 0; i < blocks; ++i)
		{
			data::ChunkBlockDataNode block;
			stream.read(reinterpret_cast<char *>(&block), sizeof(block));
			data.blocks().push_back(block);
		}
		for (size_t i = 0; i < colors; ++i)
		{
			data::ChunkColorDataNode color;
			stream.read(reinterpret_cast<char *>(&color), sizeof(color));
			data.colors().push_back(color);
		}

		const auto cpos = rpos * data::REGION_SIZE<int> + pos;
		world.injectStorageData(cpos, std::move(data));
	}
	stream.close();
}
