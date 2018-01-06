
#pragma once

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

			template<typename First, typename Second, typename ...Remaning> void add();
			template<typename System> void add();

			void process(const Time & t, const Time & dt) const;

		private:
			std::vector<std::unique_ptr<SystemBase>> m_systems;
		};
	}
}

template<typename First, typename Second, typename ...Remaining>
inline void logic::ecs::SystemRegistry::add()
{
	add<First>();
	add<Second, Remaining...>();
}
template<typename System>
inline void logic::ecs::SystemRegistry::add()
{
	static_assert(std::is_base_of<SystemBase, System>::value, "System must derive from base system");
	m_systems.push_back(std::make_unique<System>());
}