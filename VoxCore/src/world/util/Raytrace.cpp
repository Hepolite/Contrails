
#include "Raytrace.h"

#include "world/World.h"
#include "util/MathGeneric.h"

#include <glm/geometric.hpp>

world::util::Raytrace::Raytrace(const World & world, const glm::ivec3 & start, const glm::ivec3 & end)
	: Raytrace(world, glm::vec3{ start } + 0.5f, glm::vec3{ end } + 0.5f)
{}
world::util::Raytrace::Raytrace(const World & world, const glm::vec3 & start, const glm::vec3 & end)
	: Raytrace(world, start, end - start, glm::length(end - start))
{}
world::util::Raytrace::Raytrace(const World & world, const glm::vec3 & start, const glm::vec3 & dir, float length)
	: m_world(world), m_pos(start), m_oldPos(start)
{
	m_dir = length * glm::normalize(dir);
	m_step = math::sign(m_dir);
	m_tMax = math::intbound(start, m_dir);
	m_tDelta = m_step / m_dir;
}

bool world::util::Raytrace::isValid() const
{
	return m_tMax.x < 1.0f || m_tMax.y < 1.0f || m_tMax.z < 1.0f;
}

void world::util::Raytrace::next()
{
	m_oldPos = m_pos;
	if (m_tMax.x < m_tMax.y && m_tMax.x < m_tMax.z)
	{
		m_pos.x += m_step.x;
		m_tMax.x += m_tDelta.x;
	}
	else if (m_tMax.y < m_tMax.z)
	{
		m_pos.y += m_step.y;
		m_tMax.y += m_tDelta.y;
	}
	else
	{
		m_pos.z += m_step.z;
		m_tMax.z += m_tDelta.z;
	}
}

unsigned int world::util::Raytrace::getBlock() const
{
	return m_world.readBlock(getBlockPos()).getId();
}
unsigned int world::util::Raytrace::getOldBlock() const
{
	return m_world.readBlock(getOldBlockPos()).getId();
}
glm::vec3 world::util::Raytrace::getPos() const
{
	return m_pos;
}
glm::vec3 world::util::Raytrace::getOldPos() const
{
	return m_oldPos;
}
glm::ivec3 world::util::Raytrace::getBlockPos() const
{
	return math::floor(m_pos);
}
glm::ivec3 world::util::Raytrace::getOldBlockPos() const
{
	return math::floor(m_oldPos);
}

// ...


world::util::RaytraceBresenham::RaytraceBresenham(const World & world, const glm::ivec3 & start, const glm::ivec3 & end)
	: m_world(world), m_pos(start), m_oldPos(start)
{
	m_step = math::sign(end - start);
	m_delta = math::abs(end - start);
	m_totalSteps = (m_delta.x > m_delta.y && m_delta.x > m_delta.z) ? m_delta.x : (m_delta.y > m_delta.z) ? m_delta.y : m_delta.z;
}
world::util::RaytraceBresenham::RaytraceBresenham(const World & world, const glm::vec3 & start, const glm::vec3 & end)
	: RaytraceBresenham(world, math::floor(start), math::floor(start))
{}
world::util::RaytraceBresenham::RaytraceBresenham(const World & world, const glm::vec3 & start, const glm::vec3 & dir, float length)
	: RaytraceBresenham(world, start, start + dir * length)
{}

bool world::util::RaytraceBresenham::isValid() const
{
	return m_currentStep < m_totalSteps;
}

void world::util::RaytraceBresenham::next()
{
	m_oldPos = m_pos;
	m_currentStep++;
	m_error += m_delta;
	for (unsigned int i = 0u; i < 3u; ++i)
	{
		if (2 * m_error[i] >= m_totalSteps)
		{
			m_pos[i] += m_step[i];
			m_error[i] -= m_totalSteps;
		}
	}
}

unsigned int world::util::RaytraceBresenham::getBlock() const
{
	return m_world.readBlock(getPos()).getId();
}
unsigned int world::util::RaytraceBresenham::getOldBlock() const
{
	return m_world.readBlock(getOldPos()).getId();
}
glm::vec3 world::util::RaytraceBresenham::getPos() const
{
	return m_pos;
}
glm::vec3 world::util::RaytraceBresenham::getOldPos() const
{
	return m_oldPos;
}
