
#pragma once

#include "io/Folder.h"
#include "logic/event/EventListener.h"

#include <pugixml/pugixml.hpp>

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
			~WorldSaver() = default;

			WorldSaver & operator=(const WorldSaver &) = delete;
			WorldSaver & operator=(WorldSaver &&) = delete;

			void inject(const World & world);
			void inject(logic::event::EventBus & bus);

			void writeMetadata() const;
			void writeBlockIds(pugi::xml_node & node) const;

		private:
			void setupListeners(logic::event::EventBus & bus);

			const World * m_world = nullptr;

			logic::event::Listener m_chunkChange;
			logic::event::Listener m_chunkDestroy;

			::io::Folder m_root;
		};
	}
}