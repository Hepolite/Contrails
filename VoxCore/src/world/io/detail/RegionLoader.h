
#pragma once

#include "io/Folder.h"

#include <glm/vec3.hpp>

namespace world
{
	class World;

	namespace io
	{
		class RegionLoader
		{
		public:
			RegionLoader() = delete;
			RegionLoader(const ::io::Folder & root) : m_root(root) {}

			void read(World & world, const glm::ivec3 & rpos) const;

		private:
			::io::Folder m_root;
		};
	}
}