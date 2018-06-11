
#pragma once

#include "io/Folder.h"
#include "world/World.h"

#include <glm/vec3.hpp>

namespace world
{
	namespace io
	{
		class RegionSaver
		{
		public:
			RegionSaver() = delete;
			RegionSaver(const ::io::Folder & root);
			RegionSaver(const RegionSaver &) = delete;
			RegionSaver(RegionSaver &&) = delete;
			~RegionSaver() = default;

			RegionSaver & operator=(const RegionSaver &) = delete;
			RegionSaver & operator=(RegionSaver &&) = delete;

			void write(const World & world, const glm::ivec3 & rpos) const;

		private:
			::io::Folder m_root;
		};
	}
}