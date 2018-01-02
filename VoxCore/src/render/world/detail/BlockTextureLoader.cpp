
#include "BlockTextureLoader.h"

namespace
{
	constexpr const char * NODE_TEXTURE = "texture";
}

void render::world::BlockTextureLoader::loadTexture(const io::File & file)
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	loadTexture(doc.child(NODE_TEXTURE));
}
void render::world::BlockTextureLoader::loadTexture(const pugi::xml_node & node)
{
}
void render::world::BlockTextureLoader::loadDefaultConnection(const pugi::xml_node & node)
{
}
