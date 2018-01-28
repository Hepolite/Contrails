
#include "LightPropagation.h"

#include "util/MathGeneric.h"
#include "world/detail/Chunk.h"
#include "world/detail/data/Indexing.h"
#include "world/World.h"

namespace
{
	inline auto reduce(unsigned int in, unsigned int absorbed, unsigned int filtered)
	{
		return in < absorbed ? 0u : math::min(in - absorbed, filtered);
	}
}

void world::data::LightSunPropagator::spread(Chunk & chunk)
{
	LightPropagationNode node;
	while (chunk.pollLightPropagation(node, LIGHT_PROPAGATION_CHANNEL_SUN))
		spreadFrom(chunk, toPos<int>(node.m_index), node.m_light);
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
	LightPropagationNode node;
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
		chunk.pushLightPropagation({ index, oldLight }, LIGHT_PROPAGATION_CHANNEL_SUN);
}
