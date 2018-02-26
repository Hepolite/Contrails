
#include "RenderWorld.h"

void render::ecs::RenderWorld::process(const Time & t, const Time & dt)
{
	auto & worlds = getData<::world::ComponentWorld>();

	for (const auto & entity : *this)
		;
}
void render::ecs::RenderWorld::render(const Time & t, const Time & dt, float pt) const
{
}
