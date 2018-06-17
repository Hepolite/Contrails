
#pragma once

#include "io/Folder.h"
#include "world/io/detail/RegionSaver.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <glm/vec3.hpp>
#include <mutex>
#include <pugixml/pugixml.hpp>
#include <thread>
#include <unordered_set>

namespace logic { namespace event { class EventBus; } }
namespace world { class World; }

namespace world
{
	namespace io
	{
		class WorldSaver
		{
		public:
			WorldSaver() = delete;
			WorldSaver(const ::io::Folder & root);
			WorldSaver(const WorldSaver &) = delete;
			WorldSaver(WorldSaver &&) = delete;
			~WorldSaver();

			WorldSaver & operator=(const WorldSaver &) = delete;
			WorldSaver & operator=(WorldSaver &&) = delete;

			void inject(const World & world);

			// ...

			void schedule(const glm::ivec3 & rpos);
			bool extract(glm::ivec3 & rpos);
			void finish();

			void writeMetadata() const;
			void writeBlockIds(pugi::xml_node & node) const;

		private:
			void work();

			::io::Folder m_root;

			const World * m_world = nullptr;
			RegionSaver m_saver;

			std::unordered_set<glm::ivec3> m_tasks;
			std::mutex m_mutex;
			std::thread m_worker;

			bool m_working = true;
		};
	}
}