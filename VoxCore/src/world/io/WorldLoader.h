
#pragma once

#include "io/Folder.h"
#include "world/io/detail/RegionLoader.h"

#include <glm/vec3.hpp>
#include <mutex>
#include <pugixml/pugixml.hpp>
#include <thread>
#include <vector>

namespace world
{
	namespace io
	{
		class WorldLoader
		{
		public:
			WorldLoader() = delete;
			WorldLoader(const ::io::Folder & root);
			WorldLoader(const WorldLoader &) = delete;
			WorldLoader(WorldLoader &&) = delete;
			~WorldLoader();

			WorldLoader & operator=(const WorldLoader &) = delete;
			WorldLoader & operator=(WorldLoader &&) = delete;

			inline void inject(World & world) { m_world = &world; }

			// ...

			void readWorld();
			void readMetadata() const;
			void readBlockIds(const pugi::xml_node & node) const;

			void finish();

		private:
			bool extract(glm::ivec3 & rpos);
			void work();

			::io::Folder m_root;

			World * m_world = nullptr;
			RegionLoader m_loader;

			std::vector<glm::ivec3> m_tasks;
			std::mutex m_mutex;
			std::thread m_worker;

			bool m_working = true;
		};
	}
}