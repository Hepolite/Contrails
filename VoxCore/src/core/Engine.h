
#pragma once

#include "util/Physics.h"
#include "core/Settings.h"
#include "logic/state/State.h"

#include <memory>

namespace asset { class AssetRegistry; }
namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }
namespace render { namespace scene { class Scene; } }
namespace render { class uboRegistry; }
namespace world { class Universe; }

namespace core
{
	class Engine
	{
	public:
		Engine();
		Engine(const Settings & settings);
		Engine(const Engine &) = delete;
		Engine(Engine &&) = delete;
		~Engine();

		Engine & operator=(const Engine &) = delete;
		Engine & operator=(Engine &&) = delete;

		void initialize();
		void setState(std::unique_ptr<logic::state::State> && state);
		void start();
		void stop();

		asset::AssetRegistry & getAssets();
		core::scene::Scene & getScene();
		logic::event::EventBus & getEventBus();
		render::uboRegistry & getUboRegistry();
		world::Universe & getUniverse();

	private:
		void process(const Time & t, const Time & dt);
		void render(const Time & t, const Time & dt) const;

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}