
#pragma once

#include "asset/AssetRegistry.h"
#include "logic/event/EventBus.h"
#include "render/uboRegistry.h"
#include "world/render/WorldRenderer.h"
#include "world/Universe.h"

#include <memory>
#include <string>
#include <unordered_map>

namespace world
{
	namespace render
	{
		class UniverseRenderer
		{
		public:
			UniverseRenderer() = default;
			UniverseRenderer(const UniverseRenderer &) = delete;
			UniverseRenderer(UniverseRenderer &&) = delete;
			~UniverseRenderer() = default;

			UniverseRenderer & operator=(const UniverseRenderer &) = delete;
			UniverseRenderer & operator=(UniverseRenderer &&) = delete;

			void inject(const Universe & universe);
			void inject(asset::AssetRegistry & assets);
			void inject(logic::event::EventBus & bus);
			void inject(::render::uboRegistry & ubos);

			void createWorld(const std::string & name);
			void destroyWorld(const std::string & name);
			bool hasWorld(const std::string & name) const;
			WorldRenderer * getWorld(const std::string & name);

		private:
			std::unordered_map<std::string, std::unique_ptr<WorldRenderer>> m_worlds;

			logic::event::Listener m_worldCreate;
			logic::event::Listener m_worldDestroy;

			const Universe * m_universe = nullptr;
			asset::AssetRegistry * m_assets = nullptr;
			logic::event::EventBus * m_bus = nullptr;
			::render::uboRegistry * m_ubos = nullptr;
		};
	}
}