
#include "Engine.h"

#include "asset/AssetRegistry.h"
#include "core/scene/Scene.h"
#include "core/setup/Initializer.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventQueue.h"
#include "logic/MainLoop.h"
#include "logic/state/State.h"
#include "render/allegro/Allegro.h"
#include "render/core/Pipeline.h"
#include "render/uboRegistry.h"
#include "render/world/UniverseRenderer.h"
#include "ui/Display.h"
#include "ui/gui/GuiManager.h"
#include "world/Universe.h"

struct core::Engine::Impl
{
	Impl() = delete;
	Impl(const Settings & settings) :
		m_allegro(),
		m_display(settings.m_display.m_size, settings.m_display.m_fullscreen),
		m_loop(settings.m_loop.m_fps, settings.m_loop.m_ups)
	{}
	~Impl() = default;

	render::allegro::Allegro m_allegro;
	ui::Display m_display;
	logic::MainLoop m_loop;

	asset::AssetRegistry m_assetRegistry;
	scene::Scene m_scene;
	logic::event::EventBus m_eventBus;
	logic::event::EventQueue m_eventQueue;
	render::uboRegistry m_uboRegistry;
	render::core::Pipeline m_pipeline;
	ui::gui::GuiManager m_guiManager;

	std::unique_ptr<logic::state::State> m_state;
	world::Universe m_universe;
	render::world::UniverseRenderer m_universeRenderer;
};

core::Engine::Engine()
	: Engine(Settings{})
{}
core::Engine::Engine(const Settings & settings)
{
	m_impl = std::make_unique<Impl>(settings);

	m_impl->m_eventQueue.add(al_get_display_event_source(m_impl->m_display.getHandle()));
	m_impl->m_pipeline.inject(m_impl->m_scene);
	m_impl->m_universe.inject(m_impl->m_scene);
	m_impl->m_universe.inject(m_impl->m_eventBus);
	m_impl->m_universeRenderer.inject(m_impl->m_universe);
	m_impl->m_universeRenderer.inject(m_impl->m_eventBus);
}
core::Engine::~Engine() = default;

void core::Engine::setState(std::unique_ptr<logic::state::State> && state)
{
	if (m_impl->m_state != nullptr)
		m_impl->m_state->deinitialize(*this);
	m_impl->m_state = std::move(state);
	if (m_impl->m_state != nullptr)
		m_impl->m_state->initialize(*this);
}
void core::Engine::initialize()
{
	setup::initialize(*this);
}
void core::Engine::start()
{
	m_impl->m_loop.process(
		[this](auto & t, auto & dt) { process(t, dt); },
		[this](auto & t, auto & dt) { render(t, dt); }
	);
	setState(nullptr);
}
void core::Engine::stop()
{
	m_impl->m_loop.terminate();
}
void core::Engine::process(const Time & t, const Time & dt)
{
	m_impl->m_eventQueue.update(m_impl->m_eventBus);
	m_impl->m_state->process(t, dt);
	m_impl->m_scene.process(t, dt);
}
void core::Engine::render(const Time & t, const Time & dt) const
{
	m_impl->m_pipeline.render(t, dt);
}

asset::AssetRegistry & core::Engine::getAssets() { return m_impl->m_assetRegistry; }
core::scene::Scene & core::Engine::getScene() { return m_impl->m_scene; }
logic::event::EventBus & core::Engine::getEventBus() { return m_impl->m_eventBus; }
render::uboRegistry & core::Engine::getUboRegistry() { return m_impl->m_uboRegistry; }
ui::gui::GuiManager & core::Engine::getGuiManager() { return m_impl->m_guiManager; }
world::Universe & core::Engine::getUniverse() { return m_impl->m_universe; }
