
#pragma once

#include "world/io/UniverseSaver.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }
namespace world { class World; }

namespace world
{
	struct ComponentWorld
	{
		std::string m_name;
	};

	class Universe
	{
	public:
		Universe();
		Universe(const Universe &) = delete;
		Universe(Universe &&) = delete;
		~Universe();

		Universe & operator=(const Universe &) = delete;
		Universe & operator=(Universe &&) = delete;

		void inject(core::scene::Scene & scene);
		void inject(logic::event::EventBus & bus);

		void createWorld(const std::string & name, bool autosave = false);
		void destroyWorld(const std::string & name);
		bool hasWorld(const std::string & name) const;
		World * getWorld(const std::string & name) const;

	private:
		std::unordered_map<std::string, std::unique_ptr<World>> m_worlds;
		io::UniverseSaver m_saver;

		core::scene::Scene * m_scene = nullptr;
		logic::event::EventBus * m_bus = nullptr;
	};
}