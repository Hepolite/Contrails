
#include "Engine.h"

#include "core/allegro/Allegro.h"
#include "logic/MainLoop.h"
#include "render/core/Pipeline.h"
#include "render/scene/Scene.h"
#include "ui/Display.h"

struct core::Engine::Impl
{
	Impl() = delete;
	Impl(const Settings & settings) :
		m_allegro(),
		m_display(settings.m_display.m_size, settings.m_display.m_fullscreen),
		m_loop(settings.m_loop.m_fps, settings.m_loop.m_ups),
		m_pipeline(),
		m_scene()
	{}

	allegro::Allegro m_allegro;
	ui::Display m_display;

	logic::MainLoop m_loop;
	render::core::Pipeline m_pipeline;
	render::scene::Scene m_scene;
};

core::Engine::Engine()
	: Engine(Settings{})
{}
core::Engine::Engine(const Settings & settings)
{
	m_impl = std::make_unique<Impl>(settings);

	m_impl->m_pipeline.inject(m_impl->m_scene);
}
core::Engine::~Engine() = default;

void core::Engine::start()
{
	m_impl->m_loop.process(
		[this](auto & t, auto & dt) { /* TODO: Process stuff */ },
		[this](auto & t, auto & dt) { m_impl->m_pipeline.render(t, dt); }
	);
}
void core::Engine::stop()
{
	m_impl->m_loop.terminate();
}

