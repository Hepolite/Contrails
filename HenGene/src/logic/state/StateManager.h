
#pragma once

#include "logic/state/State.h"
#include "util/Physics.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace core { class Engine; }

namespace logic
{
	namespace state
	{
		class StateManager
		{
		public:
			using StateType = std::type_index;
			using StatePtr = std::shared_ptr<StateBase>;

			StateManager() = default;
			StateManager(const StateManager &) = delete;
			StateManager(StateManager &&) = delete;
			~StateManager() = default;

			StateManager & operator=(const StateManager &) = delete;
			StateManager & operator=(StateManager &&) = delete;

			inline void inject(core::Engine & engine) { m_engine = &engine; }

			void process(const Time & t, const Time & dt);

			void clear();
			StateType set(const StatePtr & state);
			StateType add(const StatePtr & state);
			bool remove(const StateType & handle);
			bool has(const StateType & handle) const;

		private:
			using States = std::unordered_map<StateType, StatePtr>;
			States m_states, m_statesToAdd, m_statesToRemove;

			core::Engine * m_engine = nullptr;
		};
	}
}