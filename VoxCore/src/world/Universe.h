
#pragma once

#include "world/World.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }

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

		inline void inject(core::scene::Scene & scene) { m_scene = &scene; }
		inline void inject(logic::event::EventBus & bus) { m_bus = &bus; }

		void createWorld(const std::string & name);
		void destroyWorld(const std::string & name);
		bool hasWorld(const std::string & name) const;
		World * getWorld(const std::string & name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<World>> m_worlds;

		core::scene::Scene * m_scene = nullptr;
		logic::event::EventBus * m_bus = nullptr;
	};
}