
#pragma once

#include "logic/ecs/detail/ComponentData.h"
#include "logic/ecs/detail/ComponentMask.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace logic
{
	namespace ecs
	{
		class ComponentStorage
		{
		public:
			template<typename Component> void add();
			template<typename First, typename Second, typename ...Remaining> void add();

			template<typename Component> bool has() const;
			template<typename Component> unsigned int getId() const;
			template<typename Component> ComponentData<Component> & getData();
			template<typename Component> const ComponentData<Component> & getData() const;

			template<typename ...Components> ComponentMask getMask() const;

			inline void clear() { m_components.clear(); }
			inline void clearData() { for (auto & component : m_components) component.second.second->clear(); }

		private:
			using ComponentPtr = std::unique_ptr<ComponentDataBase>;
			using ComponentEntry = std::pair<unsigned int, ComponentPtr>;

			template<typename First, typename Second, typename ...Remaining> void getMask(ComponentMask & mask) const;
			template<typename Component> void getMask(ComponentMask & mask) const;

			std::unordered_map<std::type_index, ComponentEntry> m_components;
		};
	}
}

template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::ComponentStorage::add()
{
	add<First>();
	add<Second, Remaining...>();
}
template<typename Component>
inline void logic::ecs::ComponentStorage::add()
{
	if (m_components.size() >= MAX_COMPONENTS)
		throw std::exception("The maximum number of components has been reached");
	if (has<Component>())
		return;

	auto entry = std::make_pair(m_components.size(), std::make_unique<ComponentData<Component>>());
	m_components.emplace(typeid(Component), std::move(entry)).first;
}

template<typename Component>
inline bool logic::ecs::ComponentStorage::has() const
{
	return m_components.find(typeid(Component)) != m_components.end();
}

template<typename Component>
inline unsigned int logic::ecs::ComponentStorage::getId() const
{
	const auto it = m_components.find(typeid(Component));
	if (it == m_components.end())
		throw std::invalid_argument("Component does not exist");
	return it->second.first;
}

template<typename Component>
inline logic::ecs::ComponentData<Component> & logic::ecs::ComponentStorage::getData()
{
	if (!has<Component>())
		add<Component>();
	return *static_cast<ComponentData<Component>*>(m_components[typeid(Component)].second.get());
}
template<typename Component>
inline const logic::ecs::ComponentData<Component>& logic::ecs::ComponentStorage::getData() const
{
	const auto it = m_components.find(typeid(Component));
	if (it == m_components.end())
		throw std::invalid_argument("Component does not exist");
	return *static_cast<ComponentData<Component>*>(it->second.second.get());
}

template<typename ...Components>
inline logic::ecs::ComponentMask logic::ecs::ComponentStorage::getMask() const
{
	ComponentMask mask;
	getMask<Components...>(mask);
	return mask;
}
template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::ComponentStorage::getMask(ComponentMask & mask) const
{
	getMask<First>(mask);
	getMask<Second, Remaining...>(mask);
}
template<typename Component>
inline void logic::ecs::ComponentStorage::getMask(ComponentMask & mask) const
{
	if (has<Component>())
		mask[getId<Component>()] = true;
}
