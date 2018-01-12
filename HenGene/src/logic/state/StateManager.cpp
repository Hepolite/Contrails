
#include "StateManager.h"

void logic::state::StateManager::process(const Time & t, const Time & dt)
{
	if (m_engine != nullptr)
	{
		for (auto & it : m_statesToAdd)
			it.second->initialize(*m_engine);
		for (auto & it : m_statesToRemove)
			it.second->deinitialize(*m_engine);
	}
	m_statesToAdd.clear();
	m_statesToRemove.clear();

	for (auto & it : m_states)
		it.second->process(t, dt);
}

void logic::state::StateManager::clear()
{
	for (auto & it : m_states)
		m_statesToRemove.emplace(it);
	m_states.clear();
}

logic::state::StateManager::StateType logic::state::StateManager::set(const StatePtr & state)
{
	clear();
	return add(state);
}
logic::state::StateManager::StateType logic::state::StateManager::add(const StatePtr & state)
{
	if (state == nullptr)
		throw std::invalid_argument("Cannot accept a null state");
	if (has(state->type()))
		throw std::invalid_argument("The given state has already been added");
	m_states.emplace(state->type(), state);
	m_statesToAdd.emplace(state->type(), state);
	return state->type();
}
bool logic::state::StateManager::remove(const StateType & handle)
{
	if (!has(handle))
		return false;
	m_statesToRemove.emplace(*m_states.find(handle));
	m_states.erase(handle);
	return true;
}

bool logic::state::StateManager::has(const StateType & handle) const
{
	return m_states.find(handle) != m_states.end();
}
