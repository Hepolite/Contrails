
#include "System.h"

bool logic::ecs::SystemBase::has(const Entity & entity) const
{
	const auto it = find(entity);
	return it == m_entities.end() ? false : (*it == entity.m_id);
}

bool logic::ecs::SystemBase::validate(const Entity & entity) const
{
	return ((entity.m_mask & m_mask) ^ m_mask).none();
}

bool logic::ecs::SystemBase::add(const Entity & entity)
{
	if (!validate(entity) || has(entity))
		return false;

	if (m_entities.empty() || m_entities.back() < entity.m_id)
		m_entities.push_back(entity.m_id);
	else
	{
		const auto it = find(entity);
		if (*it == entity.m_id)
			return false;
		else
			m_entities.insert(it, entity.m_id);
	}
	return true;
}
bool logic::ecs::SystemBase::remove(const Entity & entity)
{
	if (!has(entity))
		return false;
	m_entities.erase(find(entity));
	return true;
}

logic::ecs::SystemBase::Entities::const_iterator logic::ecs::SystemBase::find(const Entity & entity) const
{
	return std::lower_bound(m_entities.begin(), m_entities.end(), entity.m_id,
		[](auto & lhs, auto & rhs) { return lhs < rhs; }
	);
}
