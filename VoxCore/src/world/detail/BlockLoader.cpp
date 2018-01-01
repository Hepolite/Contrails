
#include "BlockLoader.h"

#include "util/Strings.h"

namespace
{
	constexpr const char * NODE_DEFAULT = "default";

	constexpr const char * NODE_VARIANT = "variant";
	constexpr const char * VALUE_VARIANT_NAME = "name";

	constexpr const char * NODE_LIGHT = "light";
	constexpr const char * VALUE_LIGHT_EMIT = "emit";
	constexpr const char * VALUE_LIGHT_ABSORB = "absorb";
	constexpr const char * VALUE_LIGHT_FILTER = "filter";
}

void world::BlockLoader::loadBlocks(const io::Folder & folder) const
{
	for (const auto it : folder.getFiles())
		loadBlock(it);
	for (const auto it : folder.getFolders())
		loadBlocks(it);
}
void world::BlockLoader::loadBlock(const io::File & file) const
{
	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	const auto def = doc.child(NODE_DEFAULT);
	for (auto variant = doc.first_child(); variant; variant = variant.next_sibling())
	{
		if (std::strcmp(NODE_VARIANT, variant.name()) == 0)
		{
			const std::string attrName = variant.attribute(VALUE_VARIANT_NAME).as_string();
			const std::string blockName = file.getName() + (attrName.empty() ? "" : ":" + attrName);

			if (m_registry != nullptr)
				BlockVariantLoader{}.loadVariant(m_registry->add(blockName), variant, def);
		}
	}
}

void world::BlockVariantLoader::loadVariant(Block & block, const pugi::xml_node & variant, const pugi::xml_node & def) const
{
	loadLight(block, variant.child(NODE_LIGHT), def.child(NODE_LIGHT));
}
void world::BlockVariantLoader::loadLight(Block & block, const pugi::xml_node & light, const pugi::xml_node & def) const
{
	const auto defEmit = def.attribute(VALUE_LIGHT_EMIT).as_string("0 0 0 0");
	const auto defAbsorb = def.attribute(VALUE_LIGHT_ABSORB).as_string("1 1 1 1");
	const auto defFilter = def.attribute(VALUE_LIGHT_FILTER).as_string("0 0 0 0");

	const auto attrEmit = light.attribute(VALUE_LIGHT_EMIT).as_string(defEmit);
	const auto attrAbsorb = light.attribute(VALUE_LIGHT_ABSORB).as_string(defAbsorb);
	const auto attrFilter = light.attribute(VALUE_LIGHT_FILTER).as_string(defFilter);

	block.m_lightEmitted = string::parse<glm::uvec4>(attrEmit);
	block.m_lightAbsorbed = string::parse<glm::uvec4>(attrAbsorb);
	block.m_lightFiltered = string::parse<glm::uvec4>(attrFilter);
}
