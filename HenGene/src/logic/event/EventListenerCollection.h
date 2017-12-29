
#pragma once

#include <functional>
#include <unordered_map>

namespace logic
{
	namespace event
	{
		template<typename Event> using Callback = std::function<void(Event&)>;
		template<typename Event> using CallbackConst = std::function<void(const Event&)>;

		class ListenerCollectionBase
		{
		public:
			virtual ~ListenerCollectionBase() = default;

			virtual void erase(unsigned int id) = 0;
		};

		template<typename Event>
		class ListenerCollection : public ListenerCollectionBase
		{
			friend class EventBus;

		private:
			virtual void erase(unsigned int id) override final { m_callbacks.erase(id); }

			std::unordered_map<unsigned int, Callback<Event>> m_callbacks;
		};
		template<typename Event>
		class ListenerCollectionConst : public ListenerCollectionBase
		{
			friend class EventBus;

		private:
			virtual void erase(unsigned int id) override final { m_callbacks.erase(id); }

			std::unordered_map<unsigned int, CallbackConst<Event>> m_callbacks;
		};
	}
}