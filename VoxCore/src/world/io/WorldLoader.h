
#pragma once

#include "io/Folder.h"
#include "world/io/detail/RegionLoader.h"

#include <pugixml/pugixml.hpp>

namespace world
{
	namespace io
	{
		class WorldLoader
		{
		public:
			WorldLoader() = delete;
			WorldLoader(const ::io::Folder & root);

			inline void inject(World & world) { m_world = &world; }

			// ...

			void readWorld() const;
			void readMetadata() const;
			void readBlockIds(const pugi::xml_node & node) const;

			void finish();

		private:
			RegionLoader m_loader;

			::io::Folder m_root;
			World * m_world = nullptr;
		};
	}
}