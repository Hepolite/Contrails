
#include "Engine.h"

#include "asset/AssetRegistry.h"
#include "core/allegro/Allegro.h"
#include "logic/event/EventBus.h"
#include "logic/event/EventQueue.h"
#include "logic/MainLoop.h"
#include "render/core/Pipeline.h"
#include "render/scene/Scene.h"
#include "render/uboRegistry.h"
#include "ui/Display.h"

struct core::Engine::Impl
{
	Impl() = delete;
	Impl(const Settings & settings) :
		m_allegro(),
		m_display(settings.m_display.m_size, settings.m_display.m_fullscreen),
		m_assetRegistry(),
		m_eventBus(),
		m_eventQueue(),
		m_loop(settings.m_loop.m_fps, settings.m_loop.m_ups),
		m_pipeline(),
		m_scene(),
		m_uboRegistry()
	{}
	~Impl() = default;

	allegro::Allegro m_allegro;
	ui::Display m_display;

	asset::AssetRegistry m_assetRegistry;
	logic::event::EventBus m_eventBus;
	logic::event::EventQueue m_eventQueue;
	logic::MainLoop m_loop;
	render::core::Pipeline m_pipeline;
	render::scene::Scene m_scene;
	render::uboRegistry m_uboRegistry;

	std::unique_ptr<logic::state::State> m_state = nullptr;
};

core::Engine::Engine()
	: Engine(Settings{})
{}
core::Engine::Engine(const Settings & settings)
{
	m_impl = std::make_unique<Impl>(settings);

	m_impl->m_eventQueue.add(al_get_display_event_source(m_impl->m_display.getHandle()));
	m_impl->m_pipeline.inject(m_impl->m_scene);
}
core::Engine::~Engine() = default;

void core::Engine::start(std::unique_ptr<logic::state::State> && state)
{
	m_impl->m_state = std::move(state);
	m_impl->m_loop.process(
		[this](auto & t, auto & dt) { process(t, dt); },
		[this](auto & t, auto & dt) { render(t, dt); }
	);
}
void core::Engine::stop()
{
	m_impl->m_loop.terminate();
}
void core::Engine::process(const Time & t, const Time & dt)
{
	m_impl->m_eventQueue.update(m_impl->m_eventBus);
	m_impl->m_state->process(t, dt);
}
void core::Engine::render(const Time & t, const Time & dt) const
{
	m_impl->m_pipeline.render(t, dt);
}

asset::AssetRegistry & core::Engine::extractAssets() { return m_impl->m_assetRegistry; }
logic::event::EventBus & core::Engine::extractEventBus() { return m_impl->m_eventBus; }
render::uboRegistry & core::Engine::extractuboRegistry() { return m_impl->m_uboRegistry; }

