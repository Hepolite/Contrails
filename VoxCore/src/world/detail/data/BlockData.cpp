
#include "BlockData.h"

namespace
{
	constexpr unsigned int BIT_BLOCK_ID = 5u;
	constexpr unsigned int BIT_COLOR_RED = 10u;
	constexpr unsigned int BIT_COLOR_GREEN = 5u;

	constexpr unsigned int BITMASK_BLOCK_ID = 0xFFFFFFE0u;
	constexpr unsigned int BITMASK_LIGHT = 0x0000001Fu;
}

world::data::BlockData::BlockData(unsigned int id, unsigned int light) noexcept
	: m_data((id << BIT_BLOCK_ID) | (light & BITMASK_LIGHT))
{}

void world::data::BlockData::setId(unsigned int id)
{
	m_data = (m_data & BITMASK_LIGHT) | (id << BIT_BLOCK_ID);
}
void world::data::BlockData::setLight(unsigned int light)
{
	m_data = (m_data & BITMASK_BLOCK_ID) | (light & BITMASK_LIGHT);
}
unsigned int world::data::BlockData::getId() const
{
	return m_data >> BIT_BLOCK_ID;
}
unsigned int world::data::BlockData::getLight() const
{
	return m_data & BITMASK_LIGHT;
}


world::data::ColorData::ColorData(const glm::uvec3 & color) noexcept
{
	setColor(color);
}

void world::data::ColorData::setColor(const glm::uvec3 & color)
{
	m_data = (
		(color.r & BITMASK_LIGHT) << BIT_COLOR_RED) |
		((color.g & BITMASK_LIGHT) << BIT_COLOR_GREEN) |
		(color.b & BITMASK_LIGHT
	);
}
glm::uvec3 world::data::ColorData::getColor() const
{
	return glm::uvec3{ m_data >> BIT_COLOR_RED, m_data >> BIT_COLOR_GREEN, m_data } & BITMASK_LIGHT;
}
