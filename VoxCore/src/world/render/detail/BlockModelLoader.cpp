
#include "BlockModelLoader.h"

#include "util/Strings.h"

namespace
{
	constexpr const char * NODE_GEOMETRY = "geometry";
	constexpr const char * NODE_VERTICES = "vertices";
	constexpr const char * NODE_INDICES = "indices";

	constexpr const char * VALUE_VERTEX_POSITION = "position";
	constexpr const char * VALUE_VERTEX_NORMAL = "normal";
	constexpr const char * VALUE_VERTEX_UV = "uv";
	constexpr const char * VALUE_VERTEX_COLOR = "color";
}

world::render::BlockModelLoader::BlockModelLoader(const glm::vec3 & offset, const glm::vec3 & rotation, const glm::vec3 & scale)
	: m_offset(offset), m_rotation(rotation), m_scale(scale)
{}

void world::render::BlockModelLoader::loadModel(const io::File & file)
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	loadGeometry(doc.child(NODE_GEOMETRY));
}
void world::render::BlockModelLoader::loadGeometry(const pugi::xml_node & node)
{
	for (auto side = node.first_child(); side; side = side.next_sibling())
		loadSide(side, ::world::util::fromName(side.name()));
}
void world::render::BlockModelLoader::loadSide(const pugi::xml_node & node, const util::Side & side)
{
	loadVertices(node.child(NODE_VERTICES), side);
	loadIndices(node.child(NODE_INDICES), side);
}
void world::render::BlockModelLoader::loadVertices(const pugi::xml_node & node, const util::Side & side)
{
	m_model.m_vertices[side.m_id].clear();

	for (auto vertex = node.first_child(); vertex; vertex = vertex.next_sibling())
	{
		const auto attrPosition = string::parse<glm::vec3>(vertex.attribute(VALUE_VERTEX_POSITION).as_string());
		const auto attrNormal = string::parse<glm::vec3>(vertex.attribute(VALUE_VERTEX_NORMAL).as_string());
		const auto attrUv = string::parse<glm::vec3>(vertex.attribute(VALUE_VERTEX_UV).as_string());
		const auto attrColor = string::parse<glm::vec3>(vertex.attribute(VALUE_VERTEX_COLOR).as_string());

		m_model.m_vertices[side.m_id].push_back({ attrPosition, attrNormal, attrUv, attrColor });
	}
}
void world::render::BlockModelLoader::loadIndices(const pugi::xml_node & node, const util::Side & side)
{
	m_model.m_indices[side.m_id] = string::parseVector<unsigned int>(node.child_value());
}
