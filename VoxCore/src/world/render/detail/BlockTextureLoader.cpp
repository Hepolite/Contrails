
#include "BlockTextureLoader.h"

#include "util/StringParsing.h"

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/hash.hpp>
#include <glm/vec4.hpp>
#include <plog/Log.h>
#include <string>

namespace
{
	constexpr const char * NODE_TEXTURE = "texture";
	constexpr const char * NODE_CONNECTION = "connection";

	constexpr const char * ATTR_TEXTURE_PATH = "path";
	constexpr const char * ATTR_CONNECTION_TYPE = "type";
	constexpr const char * NODE_CONNECTION_BLOCKS = "blocks";
	constexpr const char * NODE_CONNECTION_DIRECTION = "direction";
	constexpr const char * NODE_CONNECTION_START = "start";
	constexpr const char * NODE_CONNECTION_END = "end";

	constexpr const char * VALUE_CONNECTION_DEFAULT = "default";
	constexpr const char * VALUE_CONNECTION_RANDOM = "random";
	constexpr const char * VALUE_CONNECTION_CONNECTED = "connected";
	constexpr const char * VALUE_DIRECTION_ALL = "all";
	constexpr const char * VALUE_DIRECTION_HORIZONTAL = "horizontal";
	constexpr const char * VALUE_DIRECTION_VERTICAL = "vertical";

	inline unsigned int calculateHash(const glm::ivec3 & pos, const world::util::Side & side)
	{
		return std::hash<glm::ivec3>()(pos) ^ side.m_id;
	}

	inline unsigned int mapAll(const world::data::BlockRegion & region, const glm::ivec3 & pos, const world::util::Side & side, const std::vector<bool> & keys)
	{
		static const unsigned int mappings[] = {
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
			0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0
		};

		return mappings[
			keys[region.readBlock(pos - side.m_tangentH + side.m_tangentV).getId()] << 0 |
			keys[region.readBlock(pos + side.m_tangentV).getId()] << 1 |
			keys[region.readBlock(pos + side.m_tangentH + side.m_tangentV).getId()] << 2 |
			keys[region.readBlock(pos + side.m_tangentH).getId()] << 3 |
			keys[region.readBlock(pos + side.m_tangentH - side.m_tangentV).getId()] << 4 |
			keys[region.readBlock(pos - side.m_tangentV).getId()] << 5 |
			keys[region.readBlock(pos - side.m_tangentH - side.m_tangentV).getId()] << 6 |
			keys[region.readBlock(pos - side.m_tangentH).getId()] << 7
		];
	}
	inline unsigned int mapHorizontal(const world::data::BlockRegion & region, const glm::ivec3 & pos, const world::util::Side & side, const std::vector<bool> & keys)
	{
		static const unsigned int mappings[] = { 0, 3, 1, 2 };

		return mappings[
			keys[region.readBlock(pos - side.m_tangentH).getId()] << 0 |
			keys[region.readBlock(pos + side.m_tangentH).getId()] << 1
		];
	}
	inline unsigned int mapVertical(const world::data::BlockRegion & region, const glm::ivec3 & pos, const world::util::Side & side, const std::vector<bool> & keys)
	{
		static const unsigned int mappings[] = { 0, 3, 1, 2 };

		return mappings[
			keys[region.readBlock(pos + side.m_tangentV).getId()] << 0 |
			keys[region.readBlock(pos - side.m_tangentV).getId()] << 1
		];
	}
}

void world::render::BlockTextureLoader::loadTexture(const io::File & file)
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	loadTexture(doc.child(NODE_TEXTURE));
	loadConnection(doc.child(NODE_CONNECTION));
}
void world::render::BlockTextureLoader::loadTexture(const pugi::xml_node & texture)
{
	const auto attrPath = texture.attribute(ATTR_TEXTURE_PATH).as_string();

	if (m_atlas == nullptr)
		LOG_WARNING << "Texture atlas was used before being injected";
	else
		m_texture.m_handle = m_atlas->attach(attrPath);
}

void world::render::BlockTextureLoader::loadConnection(const pugi::xml_node & connection)
{
	const std::string attrType = connection.attribute(ATTR_CONNECTION_TYPE).as_string();
	if (attrType == VALUE_CONNECTION_DEFAULT)
		loadDefaultConnection(connection);
	else if (attrType == VALUE_CONNECTION_RANDOM)
		loadRandomConnection(connection);
	else if (attrType == VALUE_CONNECTION_CONNECTED)
		loadConnectedConnection(connection);
	else
	{
		m_texture.m_lookup = [](auto & region, auto & pos, auto & side) { return data::TextureData{}; };
		LOG_WARNING << "Unknown texture connection " << attrType;
	}
}
void world::render::BlockTextureLoader::loadDefaultConnection(const pugi::xml_node & node)
{
	const auto handle = m_texture.m_handle;

	m_texture.m_lookup = [handle](auto & region, auto & pos, auto & side)
	{
		return data::TextureData{ handle };
	};
}
void world::render::BlockTextureLoader::loadRandomConnection(const pugi::xml_node & node)
{
	const auto start = node.attribute(NODE_CONNECTION_START).as_uint();
	const auto end = node.attribute(NODE_CONNECTION_END).as_uint();
	const auto meta = end - start;
	const auto handle = m_texture.m_handle + start;

	m_texture.m_lookup = [handle, meta](auto & region, auto & pos, auto & side)
	{
		return data::TextureData{ handle, meta, calculateHash(pos, side) };
	};
}
void world::render::BlockTextureLoader::loadConnectedConnection(const pugi::xml_node & node)
{
	const std::string direction = node.attribute(NODE_CONNECTION_DIRECTION).as_string();
	const auto blocks = string::parseVector<std::string>(node.attribute(NODE_CONNECTION_BLOCKS).as_string());
	const auto start = string::parseVec4<unsigned int>(node.attribute(NODE_CONNECTION_START).as_string());
	const auto end = string::parseVec4<unsigned int>(node.attribute(NODE_CONNECTION_END).as_string());

	const auto meta = end - start;
	const auto handle = m_texture.m_handle + start;

	std::vector<bool> keys;
	keys.resize(m_registry->size());
	for (auto & block : blocks)
		keys[(*m_registry)[block].m_id] = true;

	if (direction == VALUE_DIRECTION_ALL)
		;
	else if (direction == VALUE_DIRECTION_HORIZONTAL)
	{
		m_texture.m_lookup = [handle, meta, keys](auto & region, auto & pos, auto & side)
		{
			const auto mapped = mapHorizontal(region, pos, side, keys);
			return data::TextureData{ handle[mapped], meta[mapped], calculateHash(pos, side) };
		};
	}
	else if (direction == VALUE_DIRECTION_VERTICAL)
	{
		m_texture.m_lookup = [handle, meta, keys](auto & region, auto & pos, auto & side)
		{
			const auto mapped = mapVertical(region, pos, side, keys);
			return data::TextureData{ handle[mapped], meta[mapped], calculateHash(pos, side) };
		};
	}
	else
	{
		loadDefaultConnection(node);
		LOG_WARNING << "Unknown connection direction " << direction;
	}
}
