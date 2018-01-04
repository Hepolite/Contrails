
#pragma once

#include "logic/event/EventBus.h"
#include "world/World.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace world
{
	class Universe
	{
	public:
		Universe() = default;
		Universe(const Universe &) = delete;
		Universe(Universe &&) = delete;
		~Universe() = default;

		Universe & operator=(const Universe &) = delete;
		Universe & operator=(Universe &&) = delete;

		void createWorld(const std::string & name);
		void destroyWorld(const std::string & name);
		bool hasWorld(const std::string & name) const;
		World * getWorld(const std::string & name) const;

		inline void inject(logic::event::EventBus & bus) { m_bus = &bus; }

	private:
		std::unordered_map<std::string, std::unique_ptr<World>> m_worlds;

		logic::event::EventBus * m_bus = nullptr;
	};
}