
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/detail/Entity.h"
#include "logic/ecs/System.h"
#include "util/Physics.h"

#include <memory>
#include <vector>

namespace logic
{
	namespace ecs
	{
		class SystemRegistry
		{
		public:
			SystemRegistry() noexcept = default;
			SystemRegistry(const SystemRegistry &) = delete;
			SystemRegistry(SystemRegistry &&) = delete;
			~SystemRegistry() noexcept = default;

			SystemRegistry & operator=(const SystemRegistry &) = delete;
			SystemRegistry & operator=(SystemRegistry &&) = delete;

			inline void inject(ComponentStorage & components) { m_components = &components; }

			void process(const Time & t, const Time & dt);

			template<typename First, typename Second, typename ...Remaning> void addSystem();
			template<typename System> void addSystem();
			inline void clearSystems() { m_systems.clear(); }

			void addEntity(const Entity & entity);
			void removeEntity(const Entity & entity);
			inline void clearEntities() { for (auto & system : m_systems) system->clear(); }

		private:
			std::vector<std::unique_ptr<SystemBase>> m_systems;

			ComponentStorage * m_components = nullptr;
		};
	}
}

template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::SystemRegistry::addSystem()
{
	addSystem<First>();
	addSystem<Second, Remaining...>();
}
template<typename System>
inline void logic::ecs::SystemRegistry::addSystem()
{
	static_assert(std::is_base_of<SystemBase, System>::value, "System must derive from base system");
	
	auto system = std::make_unique<System>();
	if (m_components != nullptr)
	{
		system->inject(*m_components);
		system->addComponents(*m_components);
		system->assignMask();
	}
	m_systems.push_back(std::move(system));
}