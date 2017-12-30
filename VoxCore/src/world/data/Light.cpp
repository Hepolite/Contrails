
#include "Light.h"

#include "util/Maths.h"
#include "world/Chunk.h"
#include "world/util/Side.h"
#include "world/World.h"

#include <glm/vec4.hpp>

namespace
{
	inline glm::uvec4 reduce(const glm::uvec4 & in, const glm::uvec4 & absorbed, const glm::uvec4 & filtered)
	{
		glm::uvec4 out;
		for (unsigned int i = 0u; i < 4u; ++i)
			out[i] = in[i] < absorbed[i] ? 0u : math::min(in[i] - absorbed[i], filtered[i]);
		return out;
	}
	inline glm::uvec4 limit(const glm::uvec4 & in, const glm::uvec4 & limit)
	{
		glm::uvec4 out;
		for (unsigned int i = 0u; i < 4u; ++i)
			out[i] = in[i] < limit[i] ? 0u : math::max(in[i], limit[i]);
		return out;
	}
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
	while (chunk->pollLightPropagation(index))
	{
		BlockData block;
		ColorData color;
		chunk->read(index, block, color);

		const auto pos = toPos<int>(index);
		const auto light = glm::uvec4{ color.getColor(), block.getLight() };
		propagateFrom(*chunk, pos, light);
	}
}
void world::data::LightPropagator::propagateFrom(Chunk & chunk, const glm::uvec3 & source, glm::uvec4 light) const
{
	for (const auto & side : util::SIDES_AXIS)
	{
		if (source[side.m_dimensions.x] == CHUNK_SIZE_BITS<int>)
		{
			auto neighbor = m_world->getChunkAt(m_cpos + side.m_normal);
			if (neighbor != nullptr)
			{
				propagateTo(*neighbor, (glm::ivec3{ source } + side.m_normal) & CHUNK_SIZE_BITS<int>, light);
				m_world->markForLighting(m_cpos + side.m_normal);
			}
		}
		else
			propagateTo(chunk, glm::ivec3{ source } + side.m_normal, light);

		if (source[side.m_dimensions.x] == 0)
		{
			auto neighbor = m_world->getChunkAt(m_cpos - side.m_normal);
			if (neighbor != nullptr)
			{
				propagateTo(*neighbor, (glm::ivec3{ source } - side.m_normal) & CHUNK_SIZE_BITS<int>, light);
				m_world->markForLighting(m_cpos - side.m_normal);
			}
		}
		else
			propagateTo(chunk, glm::ivec3{ source } - side.m_normal, light);
	}
}
void world::data::LightPropagator::propagateTo(Chunk & chunk, const glm::uvec3 & target, glm::uvec4 light) const
{
	BlockData block;
	ColorData color;
	chunk.read(target, block, color);

	light = reduce(light, glm::uvec4{ 1u }, glm::uvec4{ MAX_BLOCK_LIGHT });
	light = limit(light, { color.getColor(), block.getLight() });
	if (light.x + light.y + light.z + light.a == 0u)
		return;

	block.setLight(light.a);
	color.setColor(light);
	chunk.write(target, block, color);
}
