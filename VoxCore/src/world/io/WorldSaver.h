
#pragma once

#include "logic/event/EventListener.h"

namespace logic { namespace event { class EventBus; } }

namespace world
{
	namespace io
	{
		class WorldSaver
		{
		public:
			WorldSaver() = delete;
			WorldSaver(const logic::event::EventBus & bus);
			WorldSaver(const WorldSaver &) = delete;
			WorldSaver(WorldSaver &&) = delete;
			~WorldSaver() = default;

			WorldSaver & operator=(const WorldSaver &) = delete;
			WorldSaver & operator=(WorldSaver &&) = delete;

		private:
			void setupListeners(const logic::event::EventBus & bus);

			logic::event::Listener m_chunkChange;
			logic::event::Listener m_chunkDestroy;
		};
	}
}