
#include "Light.h"

#include "util/Maths.h"

#include <glm/vec4.hpp>

namespace
{

}

world::data::LightPropagator::LightPropagator(World & world, const glm::ivec3 & cpos) noexcept
	: m_world(&world), m_cpos(cpos)
{}

void world::data::LightPropagator::propagate() const
{
	auto chunk = m_world->getChunkAt(m_cpos);
	if (chunk == nullptr)
		return;

	Index index;
	auto & data = chunk->getBloatedData();
	while (data.pollLightPropagation(index))
	{
		BlockData block;
		ColorData color;
		data.read(index, block, color);

		const auto pos = toPos<int>(index);
		auto light = glm::uvec4{ color.getColor(), block.getLight() };
		for (auto i = 0u; i < 4u; ++i)
		{
			if (light[i] > 0u)
				--light[i];
		}

		const auto offsets = {
			glm::ivec3{ 1, 0, 0 },
			glm::ivec3{ -1, 0, 0 },
			glm::ivec3{ 0, 1, 0 },
			glm::ivec3{ 0, -1, 0 },
			glm::ivec3{ 0, 0, 1 },
			glm::ivec3{ 0, 0, -1 },
		};
		for (const auto offset : offsets)
		{
			const auto i = toIndex(pos + offset);
			data.read(i, block, color);
			if (light.r <= color.getColor().r && light.g <= color.getColor().g && light.b <= color.getColor().b && light.a <= block.getLight())
				continue;
			block.setLight(math::max(block.getLight(), light.a));
			color.setColor(math::max(color.getColor(), glm::uvec3{ light }));
			data.write(i, block, color);
		}
	}
}
