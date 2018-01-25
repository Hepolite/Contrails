
#include "Scene.h"

core::scene::Scene::Scene()
{
	m_systems.inject(m_components);
	m_entities.inject(m_components);
}

void core::scene::Scene::process(const Time & t, const Time & dt)
{
	m_systems.process(t, dt);
	m_cameras.process();
}
void core::scene::Scene::render(const Time & t, const Time & dt, float pt) const
{
	auto & camera = m_cameras.getCamera(render::scene::CameraType::NORMAL);
	camera.upload(pt);

	m_renderers.render(t, dt, pt, render::RenderPass::BACKGROUND);
	m_renderers.render(t, dt, pt, render::RenderPass::SOLID);
	m_renderers.render(t, dt, pt, render::RenderPass::CUTOFF);
	m_renderers.render(t, dt, pt, render::RenderPass::TRANSPARENT);
}

void core::scene::Scene::clearSystems()
{
	m_systems.clearSystems();
}
void core::scene::Scene::clearRenderers()
{
	m_renderers.clear();
}

void core::scene::Scene::deleteEntity(logic::ecs::EntityID entity)
{
	m_systems.removeEntity(m_entities.getEntity(entity));
	m_entities.deleteEntity(entity);
}
void core::scene::Scene::clearEntities()
{
	m_components.clearData();
	m_systems.clearEntities();
	m_entities.clear();
}
