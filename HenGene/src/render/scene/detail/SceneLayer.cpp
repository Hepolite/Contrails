
#include "SceneLayer.h"

#include <utility>

unsigned int render::scene::SceneLayer::add(const SceneRender & render)
{
	if (render == nullptr)
		throw std::invalid_argument("Render cannot be empty");

	m_nodes.push_back({ m_uniqueId, m_layer, render });
	return m_uniqueId++;
}
bool render::scene::SceneLayer::remove(unsigned int id)
{
	for (unsigned int i = 0u; i < m_nodes.size(); ++i)
	{
		if (m_nodes[i].m_id == id)
		{
			std::swap(m_nodes[i], m_nodes.back());
			m_nodes.pop_back();
			return true;
		}
	}
	return false;
}

void render::scene::SceneLayer::render(const Time & t, const Time & dt) const
{
	for (const auto & it : m_nodes)
		it.m_render(t, dt);
}
