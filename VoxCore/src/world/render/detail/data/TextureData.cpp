
#include "TextureData.h"

namespace
{
	constexpr unsigned int BIT_META = 16u;
	constexpr unsigned int BIT_HASH = 24u;

	constexpr unsigned int BITMASK_TEXTURE = 0x0000FFFF;
	constexpr unsigned int BITMASK_META = 0x00FF0000;
	constexpr unsigned int BITMASK_HASH = 0xFF000000;
}

world::render::data::TextureData::TextureData(unsigned int texture, unsigned int meta, unsigned int hash) noexcept
	: m_data((texture & BITMASK_TEXTURE) | ((meta << BIT_META) & BITMASK_META) | ((hash << BIT_HASH) & BITMASK_HASH))
{}

void world::render::data::TextureData::setTexture(unsigned int texture)
{
	m_data = (m_data & ~BITMASK_TEXTURE) | (texture & BITMASK_TEXTURE);
}
void world::render::data::TextureData::setMeta(unsigned int meta)
{
	m_data = (m_data & ~BITMASK_META) | ((meta << BIT_META) & BITMASK_META);
}
void world::render::data::TextureData::setHash(unsigned int hash)
{
	m_data = (m_data & ~BITMASK_HASH) | ((hash << BIT_HASH) & BITMASK_HASH);
}
unsigned int world::render::data::TextureData::getTexture() const
{
	return m_data & BITMASK_TEXTURE;
}
unsigned int world::render::data::TextureData::getMeta() const
{
	return (m_data & BITMASK_META) >> BIT_META;
}
unsigned int world::render::data::TextureData::getHash() const
{
	return (m_data & BITMASK_HASH) >> BIT_HASH;
}