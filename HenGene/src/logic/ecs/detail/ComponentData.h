
#pragma once

#include "logic/ecs/detail/Entity.h"

#include <algorithm>
#include <vector>

namespace logic
{
	namespace ecs
	{
		class ComponentDataBase
		{};

		template<typename Component>
		class ComponentData : public ComponentDataBase
		{
		public:
			bool has(EntityID entity) const;

			Component & operator[](EntityID entity);
			const Component & operator[](EntityID entity) const;

		private:
			using EntityDataPair = std::pair<EntityID, Component>;
			using Data = std::vector<EntityDataPair>;

			typename Data::iterator find(EntityID entity);
			typename Data::const_iterator find(EntityID entity) const;

			Data m_data;
		};
	}
}

template<typename Component>
inline typename logic::ecs::ComponentData<Component>::Data::iterator
	logic::ecs::ComponentData<Component>::find(EntityID entity)
{
	return std::lower_bound(m_data.begin(), m_data.end(), entity,
		[](auto & lhs, auto & rhs) { return lhs.first < rhs; }
	);
}
template<typename Component>
inline typename logic::ecs::ComponentData<Component>::Data::const_iterator
	logic::ecs::ComponentData<Component>::find(EntityID entity) const
{
	return std::lower_bound(m_data.begin(), m_data.end(), entity,
		[](auto & lhs, auto & rhs) { return lhs.first < rhs; }
	);
}

template<typename Component>
inline bool logic::ecs::ComponentData<Component>::has(EntityID entity) const
{
	const auto it = find(entity);
	return it == m_data.end() ? false : (it->first == entity);
}

template<typename Component>
inline Component & logic::ecs::ComponentData<Component>::operator[](EntityID entity)
{
	if (m_data.empty() || m_data.back().first < entity)
	{
		m_data.emplace_back(entity, Component{});
		return m_data.back().second;
	}

	const auto it = find(entity);
	if (it->first == entity)
		return it->second;
	else
		return m_data.insert(it, { entity, Component{} })->second;
}
template<typename Component>
inline const Component & logic::ecs::ComponentData<Component>::operator[](EntityID entity) const
{
	const auto it = find(entity);
	if (it != m_data.end() && it->first == entity)
		return it->second;
	else
		throw std::invalid_argument("No data associated with entity (" + std::to_string(entity) + ")");
}
