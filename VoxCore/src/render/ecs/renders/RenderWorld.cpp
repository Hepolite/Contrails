
#include "RenderWorld.h"

#include "io/File.h"
#include "render/opengl/Program.h"
#include "render/opengl/Shader.h"

#include "render/opengl/OpenGL.h"

void render::ecs::RenderWorld::process(const Time & t, const Time & dt)
{
	auto & worlds = getData<::world::ComponentWorld>();

	for (const auto & entity : *this)
		m_renderer->process(worlds[entity].m_name);
}
void render::ecs::RenderWorld::render(const Time & t, const Time & dt, float pt) const
{
	auto & worlds = getData<::world::ComponentWorld>();

	for (const auto & entity : *this)
		m_renderer->render(worlds[entity].m_name, getRenderPass());
}
