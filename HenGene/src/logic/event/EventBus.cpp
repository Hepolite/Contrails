
#include "EventBus.h"

void logic::event::EventBus::remove(const Listener & listener)
{
	const auto& itMap = m_listeners.find(listener.m_identifier);
	if (itMap != m_listeners.end())
	{
		auto& map = itMap->second;
		auto itPtr = map.find(listener.m_priority);
		if (itPtr != map.end())
			itPtr->second->erase(listener.m_id);
	}
}
