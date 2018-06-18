
#pragma once

#include "io/Folder.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"
#include "world/io/WorldSaver.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace world
{
	class World;

	namespace io
	{
		class UniverseSaver
		{
		public:
			UniverseSaver() = delete;
			UniverseSaver(const ::io::Folder & root) : m_root(root) {}
			UniverseSaver(const UniverseSaver &) = delete;
			UniverseSaver(UniverseSaver &&) = delete;
			~UniverseSaver() = default;

			UniverseSaver & operator=(const UniverseSaver &) = delete;
			UniverseSaver & operator=(UniverseSaver &&) = delete;

			void inject(logic::event::EventBus & bus);

			// ...

			bool open(const World & world);
			bool close(const World & world);

		private:
			logic::event::Listener m_chunkChange;

			std::unordered_map<std::string, std::unique_ptr<WorldSaver>> m_savers;
			::io::Folder m_root;
		};
	}
}