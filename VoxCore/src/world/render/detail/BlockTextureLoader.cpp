
#include "BlockTextureLoader.h"

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
	constexpr const char * NODE_CONNECTION_START = "start";
	constexpr const char * NODE_CONNECTION_END = "end";

	constexpr const char * VALUE_CONNECTION_DEFAULT = "default";
	constexpr const char * VALUE_CONNECTION_RANDOM = "random";

	inline unsigned int calculateHash(const glm::ivec3 & pos, const world::util::Side & side)
	{
		return std::hash<glm::ivec3>()(pos) ^ side.m_id;
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
	const auto difference = end - start;
	const auto handle = m_texture.m_handle + start;

	m_texture.m_lookup = [handle, difference](auto & region, auto & pos, auto & side)
	{
		return data::TextureData{ handle, difference, calculateHash(pos, side) };
	};
}
