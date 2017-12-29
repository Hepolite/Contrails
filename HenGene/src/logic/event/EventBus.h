
#pragma once

#include "logic/event/EventListener.h"
#include "logic/event/EventListenerCollection.h"
#include "logic/event/EventPriority.h"

#include <memory>
#include <typeindex>
#include <unordered_map>

namespace logic
{
	namespace event
	{
		class EventBus
		{
		public:
			template<typename Event> void post(Event & event) const;
			template<typename Event> void post(Event && event) const;

			template<typename Event, Priority priority> Listener add(const Callback<Event> & callback);
			template<typename Event> Listener add(const CallbackConst<Event> & callback);

			void remove(const Listener & listener);

		private:
			template<typename Event, Priority priority> void post(Event & event) const;

			template<typename Event, Priority priority> ListenerCollection<Event> & getCollection();
			template<typename Event, Priority priority> ListenerCollection<Event> * getCollection() const;
			template<typename Event> ListenerCollectionConst<Event> & getCollection();
			template<typename Event> ListenerCollectionConst<Event> * getCollection() const;

			using CollectionPtr = std::unique_ptr<ListenerCollectionBase>;
			using CollectionMap = std::unordered_map<Priority, CollectionPtr>;

			std::unordered_map<std::type_index, CollectionMap> m_listeners;
			unsigned int m_uniqueId = 0u;
		};
	}
}

template<typename Event>
inline void logic::event::EventBus::post(Event & event) const
{
	post<Event, Priority::FIRST>(event);
	post<Event, Priority::EARLY>(event);
	post<Event, Priority::MIDDLE>(event);
	post<Event, Priority::LATE>(event);
	post<Event, Priority::LAST>(event);

	const auto collection = getCollection<Event>();
	if (collection != nullptr)
	{
		for (const auto& it : collection->m_callbacks)
			it.second(event);
	}
}
template<typename Event>
inline void logic::event::EventBus::post(Event && event) const
{
	post(event);
}
template<typename Event, logic::event::Priority priority>
inline void logic::event::EventBus::post(Event & event) const
{
	const auto collection = getCollection<Event, priority>();
	if (collection != nullptr)
	{
		for (const auto& it : collection->m_callbacks)
			it.second(event);
	}
}

template<typename Event, logic::event::Priority priority>
inline logic::event::Listener logic::event::EventBus::add(const Callback<Event> & callback)
{
	getCollection<Event, priority>().m_callbacks.emplace(m_uniqueId, callback);
	return Listener{ typeid(Event), priority, m_uniqueId++ };
}
template<typename Event>
inline logic::event::Listener logic::event::EventBus::add(const CallbackConst<Event> & callback)
{
	getCollection<Event>().m_callbacks.emplace(m_uniqueId, callback);
	return Listener{ typeid(Event), Priority::MONITOR, m_uniqueId++ };
}

template<typename Event, logic::event::Priority priority>
inline logic::event::ListenerCollection<Event> & logic::event::EventBus::getCollection()
{
	static_assert(priority != Priority::MONITOR, "Illegal priority specified");
	auto& map = m_listeners[typeid(Event)];
	auto& it = map.find(priority);
	if (it == map.end())
		it = map.insert({ priority, std::make_unique<ListenerCollection<Event>>() }).first;
	return *static_cast<ListenerCollection<Event>*>(it->second.get());
}
template<typename Event, logic::event::Priority priority>
inline logic::event::ListenerCollection<Event> * logic::event::EventBus::getCollection() const
{
	static_assert(priority != Priority::MONITOR, "Illegal priority specified");
	const auto collectionIt = m_listeners.find(typeid(Event));
	if (collectionIt == m_listeners.end())
		return nullptr;
	const auto& collection = collectionIt->second;
	const auto it = collection.find(priority);
	return it == collection.end() ? nullptr : static_cast<ListenerCollection<Event>*>(it->second.get());
}
template<typename Event>
inline logic::event::ListenerCollectionConst<Event> & logic::event::EventBus::getCollection()
{
	auto& map = m_listeners[typeid(Event)];
	auto it = map.find(Priority::MONITOR);
	if (it == map.end())
		it = map.insert({ Priority::MONITOR, std::make_unique<ListenerCollectionConst<Event>>() }).first;
	return *static_cast<ListenerCollectionConst<Event>*>(it->second.get());
}
template<typename Event>
inline logic::event::ListenerCollectionConst<Event> * logic::event::EventBus::getCollection() const
{
	const auto collectionIt = m_listeners.find(typeid(Event));
	if (collectionIt == m_listeners.end())
		return nullptr;
	const auto& collection = collectionIt->second;
	const auto it = collection.find(Priority::MONITOR);
	return it == collection.end() ? nullptr : static_cast<ListenerCollectionConst<Event>*>(it->second.get());
}