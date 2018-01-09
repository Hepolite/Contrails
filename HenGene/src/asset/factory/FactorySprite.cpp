
#include "FactorySprite.h"

#include "util/StringParsing.h"

#include <pugixml/pugixml.hpp>

namespace
{
	constexpr const char * NODE_FILE = "file";
	constexpr const char * NODE_FRAMES = "frames";

	constexpr const char * ATTR_NAME = "name";
	constexpr const char * ATTR_POS = "pos";
	constexpr const char * ATTR_SIZE = "size";
	constexpr const char * ATTR_TINT = "tint";
	constexpr const char * ATTR_FLIP = "flip";
}

void asset::util::LoaderSprite::load(render::allegro::Sprite & asset, const io::File & file) const
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	if (const auto node = doc.child(NODE_FILE))
		asset.load(node.child_value());
	for (auto node = doc.child(NODE_FRAMES).first_child(); node; node = node.next_sibling())
	{
		const auto attrName = node.attribute(ATTR_NAME).as_string();
		const auto attrPos = string::parse<glm::ivec2>(node.attribute(ATTR_POS).as_string());
		const auto attrSize = string::parse<glm::ivec2>(node.attribute(ATTR_SIZE).as_string());
		const auto attrTint = string::parse<glm::vec4>(node.attribute(ATTR_TINT).as_string("1 1 1 1"));
		const auto attrFlip = string::parse<glm::bvec2>(node.attribute(ATTR_FLIP).as_string());

		render::allegro::SpriteFrame frame{ asset.getHandle(), attrPos, attrSize };
		frame.tint(attrTint);
		frame.flip(attrFlip.x, attrFlip.y);
		asset.add(attrName, std::move(frame));
	}
}

void asset::util::BuilderSprite::build(render::allegro::Sprite & asset, unsigned int width, unsigned int height) const
{
	asset.create(width, height);
}
