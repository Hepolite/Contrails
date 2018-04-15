
#include "LightPropagation.h"

#include "util/MathGeneric.h"
#include "world/detail/Chunk.h"
#include "world/detail/data/Indexing.h"
#include "world/World.h"

namespace
{
	const unsigned int USE_CHUNK_LIGHT = std::numeric_limits<unsigned int>::max();

	inline auto reduce(unsigned int in, unsigned int absorbed, unsigned int filtered)
	{
		return in < absorbed ? 0u : math::min(in - absorbed, filtered);
	}
	inline glm::uvec3 reduce(const glm::uvec3 & in, const glm::uvec3 & absorbed, const glm::uvec3 & filtered)
	{
		return { reduce(in.x, absorbed.x, filtered.x), reduce(in.y, absorbed.y, filtered.y), reduce(in.z, absorbed.z, filtered.z) };
	}
}

void world::data::LightSunPropagator::spread(Chunk & chunk)
{
	LightPropagationNode node;
	while (chunk.pollLightPropagation(node, LIGHT_PROPAGATION_CHANNEL_SUN))
	{
		if (node.m_light == USE_CHUNK_LIGHT)
			node.m_light = chunk.readBlock(node.m_index).getLight();
		spreadFrom(chunk, toPos<int>(node.m_index), node.m_light);
	}
}
void world::data::LightSunPropagator::spreadFrom(Chunk & chunk, const glm::ivec3 & source, unsigned int light)
{
	if (source.z == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BOTTOM.m_normal))
		{
			spreadDown(*neighbor, { source.x, source.y, CHUNK_SIZE_BITS<int> }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_BOTTOM.m_normal);
		}
	}
	else
		spreadDown(chunk, source + util::SIDE_BOTTOM.m_normal, light);

	if (source.z == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_TOP.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, 0 }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_TOP.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_TOP.m_normal, light);

	if (source.y == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_RIGHT.m_normal))
		{
			spreadSide(*neighbor, { source.x, CHUNK_SIZE_BITS<int>, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_RIGHT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_RIGHT.m_normal, light);

	if (source.y == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_LEFT.m_normal))
		{
			spreadSide(*neighbor, { source.x, 0, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_LEFT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_LEFT.m_normal, light);

	if (source.x == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BACK.m_normal))
		{
			spreadSide(*neighbor, { CHUNK_SIZE_BITS<int>, source.y, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_BACK.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BACK.m_normal, light);

	if (source.x == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_FRONT.m_normal))
		{
			spreadSide(*neighbor, { 0, source.y, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_FRONT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_FRONT.m_normal, light);
}
void world::data::LightSunPropagator::spreadDown(Chunk & chunk, const glm::ivec3 & target, unsigned int light)
{
	spreadSide(chunk, target, light + 1u);
}
void world::data::LightSunPropagator::spreadSide(Chunk & chunk, const glm::ivec3 & target, unsigned int light)
{
	const auto index = toIndex(target);
	auto data = chunk.readBlock(index);
	auto & block = m_world->getBlockRegistry()[data.getId()];

	light = reduce(light, block.m_lightAbsorbed.a, block.m_lightFiltered.a);
	if (light <= data.getLight())
		return;

	data.setLight(light);
	chunk.setFastUnsafe(index, data);
	chunk.pushLightPropagation({ index, light }, LIGHT_PROPAGATION_CHANNEL_SUN);
}

// ...

void world::data::LightSunRemover::spread(Chunk & chunk)
{
	LightPropagationNode node{};
	while (chunk.pollLightRemoval(node, LIGHT_PROPAGATION_CHANNEL_SUN))
		spreadFrom(chunk, toPos<int>(node.m_index), node.m_light);
}
void world::data::LightSunRemover::spreadFrom(Chunk & chunk, const glm::ivec3 & source, unsigned int light)
{
	if (source.z == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BOTTOM.m_normal))
		{
			spreadDown(*neighbor, { source.x, source.y, CHUNK_SIZE_BITS<int> }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_BOTTOM.m_normal);
		}
	}
	else
		spreadDown(chunk, source + util::SIDE_BOTTOM.m_normal, light);

	if (source.z == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_TOP.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, 0 }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_TOP.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_TOP.m_normal, light);

	if (source.y == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_RIGHT.m_normal))
		{
			spreadSide(*neighbor, { source.x, CHUNK_SIZE_BITS<int>, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_RIGHT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_RIGHT.m_normal, light);

	if (source.y == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_LEFT.m_normal))
		{
			spreadSide(*neighbor, { source.x, 0, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_LEFT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_LEFT.m_normal, light);

	if (source.x == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BACK.m_normal))
		{
			spreadSide(*neighbor, { CHUNK_SIZE_BITS<int>, source.y, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_BACK.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BACK.m_normal, light);

	if (source.x == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_FRONT.m_normal))
		{
			spreadSide(*neighbor, { 0, source.y, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_FRONT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_FRONT.m_normal, light);
}
void world::data::LightSunRemover::spreadDown(Chunk & chunk, const glm::ivec3 & target, unsigned int light)
{
	spreadSide(chunk, target, std::numeric_limits<unsigned int>::max());
}
void world::data::LightSunRemover::spreadSide(Chunk & chunk, const glm::ivec3 & target, unsigned int light)
{
	const auto index = toIndex(target);
	auto data = chunk.readBlock(index);

	const auto oldLight = data.getLight();
	if (oldLight == 0u)
		return;

	if (oldLight < light)
	{
		data.setLight(0u);
		chunk.setFastUnsafe(index, data);
		chunk.pushLightRemoval({ index, oldLight }, LIGHT_PROPAGATION_CHANNEL_SUN);
	}
	else
		chunk.pushLightPropagation({ index, USE_CHUNK_LIGHT }, LIGHT_PROPAGATION_CHANNEL_SUN);
}

// ...

void world::data::LightColorPropagator::spread(Chunk & chunk)
{
	LightPropagationNode node;
	while (chunk.pollLightPropagation(node, LIGHT_PROPAGATION_CHANNEL_COLOR))
		spreadFrom(chunk, toPos<int>(node.m_index), glm::uvec3{ node.m_light >> 16u, node.m_light >> 8u, node.m_light } & 0xFFu);
}
void world::data::LightColorPropagator::spreadFrom(Chunk & chunk, const glm::ivec3 & source, const glm::uvec3 & light)
{
	if (source.z == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BOTTOM.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, CHUNK_SIZE_BITS<int> }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_BOTTOM.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BOTTOM.m_normal, light);

	if (source.z == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_TOP.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, 0 }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_TOP.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_TOP.m_normal, light);

	if (source.y == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_RIGHT.m_normal))
		{
			spreadSide(*neighbor, { source.x, CHUNK_SIZE_BITS<int>, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_RIGHT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_RIGHT.m_normal, light);

	if (source.y == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_LEFT.m_normal))
		{
			spreadSide(*neighbor, { source.x, 0, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_LEFT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_LEFT.m_normal, light);

	if (source.x == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BACK.m_normal))
		{
			spreadSide(*neighbor, { CHUNK_SIZE_BITS<int>, source.y, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_BACK.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BACK.m_normal, light);

	if (source.x == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_FRONT.m_normal))
		{
			spreadSide(*neighbor, { 0, source.y, source.z }, light);
			m_world->markLightPropagation(m_pos + util::SIDE_FRONT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_FRONT.m_normal, light);
}
void world::data::LightColorPropagator::spreadSide(Chunk & chunk, const glm::ivec3 & target, glm::uvec3 light)
{
	const auto index = toIndex(target);
	auto color = chunk.readColor(index);
	auto & block = m_world->getBlockRegistry()[chunk.readBlock(index).getId()];

	const auto oldLight = color.getColor();
	light = math::max(oldLight, reduce(light, block.m_lightAbsorbed, block.m_lightFiltered));
	if (light.r > oldLight.r || light.g > oldLight.g || light.b > oldLight.b)
	{
		color.setColor(light);
		chunk.setFastUnsafe(index, color);
		chunk.pushLightPropagation({ index, (light.r << 16u) | (light.g << 8u) | light.b }, LIGHT_PROPAGATION_CHANNEL_COLOR);
	}
}

// ...

void world::data::LightColorRemover::spread(Chunk & chunk)
{
	LightPropagationNode node;
	while (chunk.pollLightRemoval(node, LIGHT_PROPAGATION_CHANNEL_COLOR))
		spreadFrom(chunk, toPos<int>(node.m_index), glm::uvec3{ node.m_light >> 16u, node.m_light >> 8u, node.m_light } & 0xFFu);
}
void world::data::LightColorRemover::spreadFrom(Chunk & chunk, const glm::ivec3 & source, const glm::uvec3 & light)
{
	if (source.z == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BOTTOM.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, CHUNK_SIZE_BITS<int> }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_BOTTOM.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BOTTOM.m_normal, light);

	if (source.z == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_TOP.m_normal))
		{
			spreadSide(*neighbor, { source.x, source.y, 0 }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_TOP.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_TOP.m_normal, light);

	if (source.y == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_RIGHT.m_normal))
		{
			spreadSide(*neighbor, { source.x, CHUNK_SIZE_BITS<int>, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_RIGHT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_RIGHT.m_normal, light);

	if (source.y == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_LEFT.m_normal))
		{
			spreadSide(*neighbor, { source.x, 0, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_LEFT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_LEFT.m_normal, light);

	if (source.x == 0)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_BACK.m_normal))
		{
			spreadSide(*neighbor, { CHUNK_SIZE_BITS<int>, source.y, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_BACK.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_BACK.m_normal, light);

	if (source.x == CHUNK_SIZE_BITS<int>)
	{
		if (auto * neighbor = m_world->getChunkAt(m_pos + util::SIDE_FRONT.m_normal))
		{
			spreadSide(*neighbor, { 0, source.y, source.z }, light);
			m_world->markLightRemoval(m_pos + util::SIDE_FRONT.m_normal);
		}
	}
	else
		spreadSide(chunk, source + util::SIDE_FRONT.m_normal, light);
}
void world::data::LightColorRemover::spreadSide(Chunk & chunk, const glm::ivec3 & target, glm::uvec3 light)
{
	const auto index = toIndex(target);
	auto color = chunk.readColor(index);

	auto current = color.getColor();
	for (unsigned int i = 0u; i < 3u; ++i)
	{
		if (current[i] < light[i])
		{
			light[i] = current[i];
			current[i] = 0u;
		}
		else if (light[i] <= current[i])
			light[i] = 0u;
	}

	color.setColor(current);
	chunk.setFastUnsafe(index, color);
	if (light.r + light.g + light.b != 0u)
		chunk.pushLightRemoval({ index, (light.r << 16u) | (light.g << 8u) | light.b }, LIGHT_PROPAGATION_CHANNEL_COLOR);
	if (current.r + current.g + current.b != 0u)
		chunk.pushLightPropagation({ index, (current.r << 16u) | (current.g << 8u) | current.b }, LIGHT_PROPAGATION_CHANNEL_COLOR);
}
