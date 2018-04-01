
#include "Engine.h"

#include "asset/AssetRegistry.h"
#include "core/MainLoop.h"
#include "core/scene/Scene.h"
#include "core/setup/Initializer.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventQueue.h"
#include "logic/state/StateManager.h"
#include "render/allegro/Allegro.h"
#include "render/core/Pipeline.h"
#include "render/uboRegistry.h"
#include "ui/Display.h"
#include "ui/gui/GuiManager.h"
#include "world/render/UniverseRenderer.h"
#include "world/Universe.h"

#include <allegro5/allegro.h>

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
	logic::state::StateManager m_stateManager;
	render::uboRegistry m_uboRegistry;
	render::core::Pipeline m_pipeline;
	ui::gui::GuiManager m_guiManager;
	world::Universe m_universe;
	world::render::UniverseRenderer m_universeRenderer;
};

core::Engine::Engine()
	: Engine(Settings{})
{}
core::Engine::Engine(const Settings & settings)
{
	m_impl = std::make_unique<Impl>(settings);

	m_impl->m_eventQueue.add(al_get_display_event_source(m_impl->m_display.getHandle()));
	m_impl->m_eventQueue.add(al_get_keyboard_event_source());
	m_impl->m_eventQueue.add(al_get_mouse_event_source());
	m_impl->m_guiManager.inject(m_impl->m_assetRegistry);
	m_impl->m_guiManager.inject(m_impl->m_display);
	m_impl->m_guiManager.inject(m_impl->m_eventBus);
	m_impl->m_pipeline.inject(m_impl->m_guiManager);
	m_impl->m_pipeline.inject(m_impl->m_scene);
	m_impl->m_scene.inject(*this);
	m_impl->m_scene.inject(m_impl->m_display);
	m_impl->m_scene.inject(m_impl->m_uboRegistry);
	m_impl->m_stateManager.inject(*this);
	m_impl->m_universe.inject(m_impl->m_eventBus);
	m_impl->m_universe.inject(m_impl->m_scene);
	m_impl->m_universeRenderer.inject(m_impl->m_eventBus);
	m_impl->m_universeRenderer.inject(m_impl->m_universe);
}
core::Engine::~Engine() = default;

void core::Engine::initialize()
{
	setup::initialize(*this);
}
void core::Engine::start()
{
	m_impl->m_loop.process(
		[this](auto & t, auto & dt) { process(t, dt); },
		[this](auto & t, auto & dt, auto pt) { render(t, dt, pt); }
	);
}
void core::Engine::stop()
{
	m_impl->m_loop.terminate();
}
void core::Engine::process(const Time & t, const Time & dt)
{
	m_impl->m_eventQueue.update(m_impl->m_eventBus);
	m_impl->m_stateManager.process(t, dt);
	m_impl->m_scene.process(t, dt);
	m_impl->m_guiManager.process();
}
void core::Engine::render(const Time & t, const Time & dt, float pt) const
{
	m_impl->m_pipeline.render(t, dt, pt);
}

asset::AssetRegistry & core::Engine::getAssets() { return m_impl->m_assetRegistry; }
core::scene::Scene & core::Engine::getScene() { return m_impl->m_scene; }
logic::event::EventBus & core::Engine::getEventBus() { return m_impl->m_eventBus; }
logic::state::StateManager & core::Engine::getStateManager() { return m_impl->m_stateManager; }
render::uboRegistry & core::Engine::getUboRegistry() { return m_impl->m_uboRegistry; }
ui::gui::GuiManager & core::Engine::getGuiManager() { return m_impl->m_guiManager; }
world::Universe & core::Engine::getUniverse() { return m_impl->m_universe; }
world::render::UniverseRenderer & core::Engine::getUniverseRenderer() { return m_impl->m_universeRenderer; }
