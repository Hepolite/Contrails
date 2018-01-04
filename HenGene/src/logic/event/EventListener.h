
#pragma once

#include "logic/event/EventPriority.h"

#include <memory>
#include <typeindex>

namespace logic
{
	namespace event
	{
		class EventBus;

		struct Listener
		{
			Listener() = default;
			Listener(const std::type_index & identifier, Priority priority, unsigned int id, EventBus * bus);
			Listener(const Listener &) = delete;
			Listener(Listener && other);
			~Listener();

			Listener & operator=(const Listener &) = delete;
			Listener & operator=(Listener && other);

			std::type_index m_identifier = std::type_index(typeid(void));
			Priority m_priority = Priority::MONITOR;
			unsigned int m_id = 0u;

			EventBus * m_bus = nullptr;
		};
	}
}