
#include "Light.h"

#include "util/Maths.h"
#include "world/detail/Chunk.h"
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
}

world::data::LightPropagator::LightPropagator(World & world, const glm::ivec3 & cpos) noexcept
	: m_world(&world), m_cpos(cpos)
{}

void world::data::LightPropagator::propagate() const
{
	auto * chunk = m_world->getChunkAt(m_cpos);
	if (chunk == nullptr)
		return;

	Index index;
	while (chunk->pollLightPropagation(index))
	{
		const auto pos = toPos<unsigned int>(index);
		const auto light = glm::uvec4{
			chunk->readColor(index).getColor(),
			chunk->readBlock(index).getLight()
		};
		propagateFrom(*chunk, pos, light);
	}
}
void world::data::LightPropagator::propagateFrom(Chunk & chunk, const glm::uvec3 & source, glm::uvec4 light) const
{
	for (const auto & side : util::SIDES_AXIS)
	{
		if (source[side.m_dimensions.x] == CHUNK_SIZE_BITS<int>)
		{
			auto * neighbor = m_world->getChunkAt(m_cpos + side.m_normal);
			if (neighbor != nullptr)
			{
				propagateTo(*neighbor, (glm::ivec3{ source } + side.m_normal) & CHUNK_SIZE_BITS<int>, light);
				m_world->markLightingChange(m_cpos + side.m_normal);
			}
		}
		else
			propagateTo(chunk, glm::ivec3{ source } + side.m_normal, light);

		if (source[side.m_dimensions.x] == 0)
		{
			auto * neighbor = m_world->getChunkAt(m_cpos - side.m_normal);
			if (neighbor != nullptr)
			{
				propagateTo(*neighbor, (glm::ivec3{ source } - side.m_normal) & CHUNK_SIZE_BITS<int>, light);
				m_world->markLightingChange(m_cpos - side.m_normal);
			}
		}
		else
			propagateTo(chunk, glm::ivec3{ source } - side.m_normal, light);
	}
}
void world::data::LightPropagator::propagateTo(Chunk & chunk, const glm::uvec3 & target, glm::uvec4 light) const
{
	const auto index = toIndex(target);
	auto block = chunk.readBlock(index);
	auto color = chunk.readColor(index);
	//const auto & actualBlock = m_world->getBlockRegistry()[block.getId()];

	const auto current = glm::uvec4{ color.getColor(), block.getLight() };
	light = reduce(light, glm::uvec4{ 1u }, glm::uvec4{ MAX_BLOCK_LIGHT });
	// light = reduce(light, actualBlock.m_absorbed, actualBlock.m_filtered);
	if (light.r <= current.r && light.g <= current.g && light.b <= current.b && light.a <= current.a)
		return;
	light = math::max(current, light);

	block.setLight(math::max(block.getLight(), light.a));
	color.setColor(math::max(color.getColor(), glm::uvec3{ light }));
	chunk.setFastUnsafe(index, block, color);
	chunk.pushLightPropagation(index);
}

// ...

world::data::LightRemover::LightRemover(World & world, const glm::ivec3 & cpos) noexcept
	: m_world(&world), m_cpos(cpos)
{}

void world::data::LightRemover::propagate() const
{
}
void world::data::LightRemover::propagateFrom(Chunk & chunk, const glm::uvec3 & source, glm::uvec4 light) const
{
}
void world::data::LightRemover::propagateTo(Chunk & chunk, const glm::uvec3 & target, glm::uvec4 light) const
{
	const auto index = toIndex(target);
	auto block = chunk.readBlock(index);
	auto color = chunk.readColor(index);

	auto current = glm::uvec4{ color.getColor(), block.getLight() };
	if (current.r + current.g + current.b + current.a == 0u)
		return;

	for (unsigned int i = 0u; i < 4u; ++i)
	{
		if (current[i] <= light[i])
		{
			light[i] = current[i];
			current[i] = 0u;
		}
		else
			light[i] = 0u;
	}

	block.setLight(current.a);
	color.setColor(current);
	chunk.setFastUnsafe(index, block, color);
	if (light.r + light.g + light.b + light.a != 0u)
		chunk.pushLightRemoval(index);
	if (current.r + current.g + current.b + current.a != 0u)
		chunk.pushLightPropagation(index);
}
