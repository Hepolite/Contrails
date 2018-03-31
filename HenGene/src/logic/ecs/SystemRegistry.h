
#pragma once

#include "logic/ecs/ComponentStorage.h"
#include "logic/ecs/detail/Entity.h"
#include "logic/ecs/System.h"
#include "util/Physics.h"

#include <memory>
#include <vector>

namespace core { class Engine; }

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

			inline void inject(core::Engine & engine) { m_engine = &engine; }
			inline void inject(ComponentStorage & components) { m_components = &components; }

			void process(const Time & t, const Time & dt) const;

			template<typename First, typename Second, typename ...Remaning> void addSystem();
			template<typename System> System & addSystem();
			inline void clearSystems() { m_systems.clear(); }

			void addEntity(const Entity & entity);
			void removeEntity(const Entity & entity);
			inline void clearEntities() { for (auto & system : m_systems) system->clear(); }

		private:
			std::vector<std::unique_ptr<SystemBase>> m_systems;

			core::Engine * m_engine = nullptr;
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
inline System & logic::ecs::SystemRegistry::addSystem()
{
	static_assert(std::is_base_of<SystemBase, System>::value, "System must derive from base system");
	
	auto system = std::make_unique<System>();
	if (m_engine != nullptr)
		system->initialize(*m_engine);
	if (m_components != nullptr)
	{
		system->inject(*m_components);
		system->addComponents(*m_components);
		system->assignMask();
	}
	m_systems.push_back(std::move(system));
	return *static_cast<System *>(m_systems.back().get());
}