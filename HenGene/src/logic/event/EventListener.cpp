
#include "EventListener.h"

#include "logic/event/EventBus.h"

logic::event::Listener::Listener(const std::type_index & identifier, Priority priority, unsigned int id, EventBus * bus)
	: m_identifier(identifier), m_priority(priority), m_id(id), m_bus(bus)
{}
logic::event::Listener::Listener(Listener && other)
{
	*this = std::move(other);
}
logic::event::Listener::~Listener()
{
	m_bus->remove(*this);
}

logic::event::Listener & logic::event::Listener::operator=(Listener && other)
{
	if (this != &other)
	{
		m_id = other.m_id;
		m_priority = other.m_priority;
		m_identifier = other.m_identifier;
		m_bus = other.m_bus;

		other.m_bus = nullptr;
	}
	return *this;
}
