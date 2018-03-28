
#include "NaiveGreedyMesher.h"

using namespace render::world;
using namespace ::world::data;

namespace
{
	inline auto getIndex(const glm::uvec2 & pos)
	{
		return pos.y * CHUNK_SIZE<unsigned int> + pos.x;
	}
}

// ...

void LayerData::set(const BlockData & block, const ColorData & color, const TextureData & texture)
{
	m_data =
		(static_cast<uint64_t>(block.getData())) |
		(static_cast<uint64_t>(color.getData()) << 16u) |
		(static_cast<uint64_t>(texture.getData()) << 32u)
	;
}
BlockData LayerData::getBlock() const
{
	return BlockData{ m_data & 0xFFFFu };
}
ColorData LayerData::getColor() const
{
	return ColorData{ (m_data >> 16u) & 0xFFFFu };
}
TextureData LayerData::getTexture() const
{
	return TextureData{ (m_data >> 32u) & 0xFFFFFFFFu };
}

// ...

void LayerMask::put(const glm::uvec2 & pos, const LayerData & data)
{
	m_data[getIndex(pos)] = data;
}
LayerData LayerMask::get(const glm::uvec2 & pos) const
{
	return m_data[getIndex(pos)];
}

void render::world::LayerMask::erase(const glm::uvec2 & start, const glm::uvec2 & end)
{
	glm::uvec2 pos;
	for (pos.x = start.x; pos.x < end.x; ++pos.x)
	for (pos.y = start.y; pos.y < end.y; ++pos.y)
		m_data[getIndex(pos)].erase();
}

bool render::world::LayerMask::findExtractionPos()
{
	for (; m_pos.y < CHUNK_SIZE<unsigned int>; ++m_pos.y, m_pos.x = 0u)
	for (; m_pos.x < CHUNK_SIZE<unsigned int>; ++m_pos.x)
		if (!get(m_pos).empty())
			return true;
	return false;
}
glm::uvec2 render::world::LayerMask::getExtractionSize() const
{
	const auto current = get(m_pos);
	glm::uvec2 pos = m_pos;

	for (; pos.x < CHUNK_SIZE<unsigned int> && current == get(pos); ++pos.x)
		;

	for (; pos.y < CHUNK_SIZE<unsigned int>; ++pos.y)
	for (unsigned int k = m_pos.x; k < pos.x; ++k)
		if (current != get({ k, pos.y }))
			return pos - m_pos;

	return pos - m_pos;
}
bool LayerMask::extract(MeshFace & face)
{
	if (!findExtractionPos())
		return false;
	const auto current = get(m_pos);
	const auto size = getExtractionSize();
	erase(m_pos, m_pos + size);

	face.m_pos = m_pos;
	face.m_size = size;
	face.m_block = current.getBlock();
	face.m_color = current.getColor();
	face.m_texture = current.getTexture();
	return true;
}

// ...

void render::world::NaiveGreedyMesher::build()
{
	for (const auto & side : ::world::util::SIDES)
	for (unsigned int i = 0u; i < CHUNK_SIZE<unsigned int>; ++i)
		buildLayer(i, getLayerMask(i, side), side);
}
void render::world::NaiveGreedyMesher::buildLayer(unsigned int layer, LayerMask && mask, const Side & side)
{
	MeshFace face;
	while (mask.extract(face))
	{
		glm::ivec3 pos;
		pos[side.m_dimensions.x] = layer;
		pos[side.m_dimensions.y] = face.m_pos.x;
		pos[side.m_dimensions.z] = face.m_pos.y;

		buildFace(pos, face, side);
	}
}
void render::world::NaiveGreedyMesher::buildFace(const glm::ivec3 & pos, const MeshFace & face, const Side & side)
{
	const auto & render = (*m_renders)[face.m_block.getId()];
	const auto & indices = render.m_model.m_indices[side.m_id];
	const auto & vertices = render.m_model.m_vertices[side.m_id];
	if (indices.empty() || vertices.empty())
		return;
	const auto layer = 1u;
	auto & mesh = (*m_mesh)[layer];

	for (const auto & vertex : vertices)
	{
		// TODO: This needs to be fixed
		mesh.getVertexData().push_back({
			vertex.m_position,
			vertex.m_normal,
			vertex.m_uv,
			glm::vec4{ vertex.m_color, 1.0f }
		});
	}
	for (const auto & index : indices)
		mesh.getIndiceData().push_back(index + m_offsetIndex[layer]);
	m_offsetIndex[layer] += vertices.size();
}

LayerMask render::world::NaiveGreedyMesher::getLayerMask(unsigned int layer, const Side & side) const
{
	LayerMask mask;

	glm::ivec3 pos;
	pos[side.m_dimensions.x] = layer;
	for (pos[side.m_dimensions.y] = 0; pos[side.m_dimensions.y] < CHUNK_SIZE<int>; ++pos[side.m_dimensions.y])
	for (pos[side.m_dimensions.z] = 0; pos[side.m_dimensions.z] < CHUNK_SIZE<int>; ++pos[side.m_dimensions.z])
		mask.put({ pos[side.m_dimensions.y], pos[side.m_dimensions.z] }, getLayerData(pos, side));

	return mask;
}
LayerData NaiveGreedyMesher::getLayerData(const glm::ivec3 & pos, const Side & side) const
{
	const auto current = m_data->readBlock(pos);
	const auto currentId = current.getId();
	const auto upper = m_data->readBlock(pos + side.m_normal);
	const auto upperId = upper.getId();

	LayerData data;
	if (currentId != upperId && !(*m_renders)[upperId].m_occlude[side.m_opposite])
		data.set(
			{ currentId, upper.getLight() },
			m_data->readColor(pos + side.m_normal),
			(*m_renders)[currentId].m_texture->m_lookup(*m_data, pos, side)
		);
	return data;
}
