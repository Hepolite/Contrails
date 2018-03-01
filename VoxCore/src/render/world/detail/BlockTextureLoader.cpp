
#include "BlockTextureLoader.h"

#include <plog/Log.h>
#include <string>

namespace
{
	constexpr const char * NODE_TEXTURE = "texture";
	constexpr const char * NODE_CONNECTION = "connection";

	constexpr const char * ATTR_TEXTURE_PATH = "path";
	constexpr const char * ATTR_CONNECTION_TYPE = "type";

	constexpr const char * VALUE_CONNECTION_DEFAULT = "default";
}

void render::world::BlockTextureLoader::loadTexture(const io::File & file)
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	loadTexture(doc.child(NODE_TEXTURE));
	loadConnection(doc.child(NODE_CONNECTION));
}
void render::world::BlockTextureLoader::loadTexture(const pugi::xml_node & texture)
{
	const auto attrPath = texture.attribute(ATTR_TEXTURE_PATH).as_string();

	if (m_atlas == nullptr)
		LOG_WARNING << "Texture atlas was used before being injected";
	else
		m_texture.m_handle = m_atlas->attach(attrPath);
}
void render::world::BlockTextureLoader::loadConnection(const pugi::xml_node & connection)
{
	const std::string attrType = connection.attribute(ATTR_CONNECTION_TYPE).as_string();
	if (attrType == VALUE_CONNECTION_DEFAULT)
		loadDefaultConnection(connection);
	else
	{
		loadDefaultConnection(connection);
		LOG_WARNING << "Unknown texture connection " << attrType;
	}
}
void render::world::BlockTextureLoader::loadDefaultConnection(const pugi::xml_node & node)
{
	m_texture.m_lookup = [handle = m_texture.m_handle](auto & region, auto & pos, auto & side)
	{
		return handle;
	};
}
