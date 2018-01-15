
#pragma once

#include "util/Physics.h"
#include "core/Settings.h"

#include <memory>

namespace asset { class AssetRegistry; }
namespace core { namespace scene { class Scene; } }
namespace logic { namespace event { class EventBus; } }
namespace logic { namespace state { class StateManager; } }
namespace render { namespace scene { class Scene; } }
namespace render { class uboRegistry; }
namespace ui { namespace gui { class GuiManager; } }
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
		void start();
		void stop();

		asset::AssetRegistry & getAssets();
		core::scene::Scene & getScene();
		logic::event::EventBus & getEventBus();
		logic::state::StateManager & getStateManager();
		render::uboRegistry & getUboRegistry();
		ui::gui::GuiManager & getGuiManager();
		world::Universe & getUniverse();

	private:
		void process(const Time & t, const Time & dt);
		void render(const Time & t, const Time & dt, float pt) const;

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}