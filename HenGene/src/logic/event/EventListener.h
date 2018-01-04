
#pragma once

#include "logic/event/EventPriority.h"

#include <typeindex>

namespace logic
{
	namespace event
	{
		struct Listener
		{
			std::type_index m_identifier = std::type_index(typeid(void));
			Priority m_priority = Priority::MONITOR;
			unsigned int m_id = 0u;
		};
	}
}