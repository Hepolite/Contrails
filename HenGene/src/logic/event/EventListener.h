
#pragma once

#include "logic/event/EventPriority.h"

#include <typeindex>

namespace logic
{
	namespace event
	{
		struct Listener
		{
			const std::type_index m_identifier;
			const Priority m_priority;
			const unsigned int m_id;
		};
	}
}