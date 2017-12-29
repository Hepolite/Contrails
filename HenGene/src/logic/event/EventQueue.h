
#pragma once

#include "logic/event/EventBus.h"

#include <allegro5/events.h>

namespace logic
{
	namespace event
	{
		class EventQueue
		{
		public:
			EventQueue();
			EventQueue(const EventQueue &) = delete;
			EventQueue(EventQueue &&) = delete;
			~EventQueue();

			EventQueue & operator=(const EventQueue &) = delete;
			EventQueue & operator=(EventQueue &&) = delete;

			void update(const EventBus & bus);

			bool add(ALLEGRO_EVENT_SOURCE* source);
			bool remove(ALLEGRO_EVENT_SOURCE* source);

		private:
			ALLEGRO_EVENT_QUEUE * m_handle = nullptr;
		};
	}
}