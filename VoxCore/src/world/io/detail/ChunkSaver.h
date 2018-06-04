
#pragma once

#include "world/detail/data/ChunkData.h"

namespace world
{
	namespace io
	{
		class ChunkSaver
		{
		public:
			void write(const data::ChunkDataCompressed & data) const;
		};
	}
}