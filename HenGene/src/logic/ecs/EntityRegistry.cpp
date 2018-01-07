
#include "EntityRegistry.h"

#include <algorithm>

bool logic::ecs::EntityRegistry::hasEntity(EntityID entity) const
{
	const auto it = findAmongEntities(entity);
	return it != m_entities.end() && it->m_id == entity;
}
logic::ecs::Entity & logic::ecs::EntityRegistry::getEntity(EntityID entity)
{
	auto it = findAmongEntities(entity);
	if (it == m_entities.end() || it->m_id != entity)
		throw std::invalid_argument("Entity " + std::to_string(entity) + " does not exist");
	return *it;
}

logic::ecs::EntityID logic::ecs::EntityRegistry::createEntity()
{
	if (m_available.empty())
	{
		m_entities.push_back({ m_uniqueId, {} });
		return m_uniqueId++;
	}

	const auto id = m_available.back();
	m_available.pop_back();
	m_entities.insert(findAmongEntities(id), { id, {} });
	return id;
}
bool logic::ecs::EntityRegistry::deleteEntity(EntityID entity)
{
	const auto it = findAmongEntities(entity);
	if (it == m_entities.end() || it->m_id != entity)
		return false;
	m_available.insert(findAmongAvailable(entity), it->m_id);
	m_entities.erase(it);
	return true;
}

std::vector<logic::ecs::Entity>::iterator logic::ecs::EntityRegistry::findAmongEntities(EntityID entity)
{
	return std::lower_bound(m_entities.begin(), m_entities.end(), entity,
		[](auto & lhs, auto & rhs) { return lhs.m_id < rhs; }
	);
}
std::vector<logic::ecs::Entity>::const_iterator logic::ecs::EntityRegistry::findAmongEntities(EntityID entity) const
{
	return std::lower_bound(m_entities.begin(), m_entities.end(), entity,
		[](auto & lhs, auto & rhs) { return lhs.m_id < rhs; }
	);
}
std::vector<logic::ecs::EntityID>::const_iterator logic::ecs::EntityRegistry::findAmongAvailable(EntityID entity) const
{
	return std::lower_bound(m_available.begin(), m_available.end(), entity,
		[](auto & lhs, auto & rhs) { return lhs > rhs; }
	);
}
