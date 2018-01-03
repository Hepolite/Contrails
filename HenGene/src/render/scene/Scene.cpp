
#include "Scene.h"

render::scene::SceneRef render::scene::Scene::add(const SceneRender & render, RenderLayer layer)
{
	return std::make_pair(layer, m_layers[layer].add(render));
}
bool render::scene::Scene::remove(const SceneRef & ref)
{
	return m_layers[ref.first].remove(ref.second);
}

void render::scene::Scene::render(const Time & t, const Time & dt) const
{
	render(t, dt, RenderLayer::BACKGROUND);
	render(t, dt, RenderLayer::SOLID);
	render(t, dt, RenderLayer::CUTOFF);
	render(t, dt, RenderLayer::TRANSPARENT);
}
void render::scene::Scene::render(const Time & t, const Time & dt, RenderLayer layer) const
{
	const auto it = m_layers.find(layer);
	if (it != m_layers.end())
		it->second.render(t, dt);
}
