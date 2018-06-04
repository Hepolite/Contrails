
#pragma once

#include "world/detail/data/ChunkData.h"

namespace world
{
	namespace data
	{
		class ChunkDataTranslator
		{
		public:
			static ChunkDataBloated expand(const ChunkDataCompressed & data);
			static ChunkDataCompressed compress(const ChunkDataBloated & data);
		};
	}
}