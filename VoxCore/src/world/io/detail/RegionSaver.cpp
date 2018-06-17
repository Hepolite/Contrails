
#include "RegionSaver.h"

#include "world/detail/Limits.h"

#include <fstream>
#include <string>

namespace
{
	io::File getRegionFile(const io::Folder & root, const glm::ivec3 & rpos, const std::string & extension)
	{
		const auto name = std::to_string(rpos.x) + "_" + std::to_string(rpos.y) + "_" + std::to_string(rpos.z);
		return { root.getPath() + "/" + name + "." + extension };
	}
}

world::io::RegionSaver::RegionSaver(const::io::Folder & root) : m_root(root) {}

void world::io::RegionSaver::write(const World & world, const glm::ivec3 & rpos) const
{
	const auto file = getRegionFile(m_root, rpos, "rvd");
	m_root.create();
	file.erase();

	std::fstream stream{ file.getPath(), std::ios::out | std::ios::binary };
	if (!stream.is_open())
		return;

	glm::ivec3 pos;
	for (pos.x = 0; pos.x < data::REGION_SIZE<int>; ++pos.x)
	for (pos.y = 0; pos.y < data::REGION_SIZE<int>; ++pos.y)
	for (pos.z = 0; pos.z < data::REGION_SIZE<int>; ++pos.z)
	{
		const auto cpos = rpos * data::REGION_SIZE<int> + pos;
		if (!world.hasChunkAt(cpos))
			continue;

		const auto data = world.extractStorageData(cpos);
		const auto blockSize = data.sizeBlocks();
		const auto blockData = data.dataBlocks();
		const auto colorSize = data.sizeColors();
		const auto colorData = data.dataColors();

		stream.write(reinterpret_cast<const char *>(&pos), sizeof(pos));
		stream.write(reinterpret_cast<const char *>(&blockSize), sizeof(blockSize));
		stream.write(reinterpret_cast<const char *>(&colorSize), sizeof(colorSize));
		stream.write(reinterpret_cast<const char *>(blockData), blockSize * sizeof(data::ChunkBlockDataNode));
		stream.write(reinterpret_cast<const char *>(colorData), colorSize * sizeof(data::ChunkColorDataNode));
	}
	stream.close();
}