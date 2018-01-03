
#pragma once

#include "util/Physics.h"
#include "core/Settings.h"
#include "logic/state/State.h"

#include <memory>

namespace asset { class AssetRegistry; }
namespace logic { namespace event { class EventBus; } }
namespace render { class uboRegistry; }

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

		void start(std::unique_ptr<logic::state::State> && state);
		void stop();

		asset::AssetRegistry & extractAssets();
		logic::event::EventBus & extractEventBus();
		render::uboRegistry & extractuboRegistry();

	private:
		void process(const Time & t, const Time & dt);
		void render(const Time & t, const Time & dt) const;

		struct Impl;
		std::unique_ptr<Impl> m_impl = nullptr;
	};
}