
#include "BlockLoader.h"

#include "util/Strings.h"

#include <plog/Log.h>

namespace
{
	constexpr const char * NODE_LOGIC = "logic";
	constexpr const char * NODE_VARIANT = "variant";


	constexpr const char * NODE_PHASE = "phase";
	constexpr const char * NODE_LIGHT = "light";

	constexpr const char * ATTR_VARIANT_NAME = "name";
	constexpr const char * ATTR_PHASE_TYPE = "type";
	constexpr const char * ATTR_LIGHT_EMIT = "emit";
	constexpr const char * ATTR_LIGHT_ABSORB = "absorb";
	constexpr const char * ATTR_LIGHT_FILTER = "filter";

	constexpr const char * VALUE_PHASE_SOLID = "solid";
	constexpr const char * VALUE_PHASE_LIQUID = "liquid";
	constexpr const char * VALUE_PHASE_GAS = "gas";
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
	if (m_registry == nullptr)
	{
		LOG_WARNING << "Attempted to load blocks before block registry has been injected";
		return;
	}

	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	for (auto variant = doc.first_child(); variant; variant = variant.next_sibling())
	{
		if (std::strcmp(NODE_VARIANT, variant.name()) == 0)
		{
			const std::string attrName = variant.attribute(ATTR_VARIANT_NAME).as_string();
			const std::string blockName = file.getName() + (attrName.empty() ? "" : ":" + attrName);

			BlockVariantLoader{}.loadVariant(m_registry->add(blockName), variant.child(NODE_LOGIC));
		}
	}
}

void world::BlockVariantLoader::loadVariant(Block & block, const pugi::xml_node & variant) const
{
	loadPhase(block, variant.child(NODE_PHASE));
	loadLight(block, variant.child(NODE_LIGHT));
}
void world::BlockVariantLoader::loadPhase(Block & block, const pugi::xml_node & phase) const
{
	const std::string attrPhase = phase.attribute(ATTR_PHASE_TYPE).as_string(VALUE_PHASE_SOLID);

	if (attrPhase == VALUE_PHASE_GAS)
		block.m_phase = BlockPhase::GAS;
	else if (attrPhase == VALUE_PHASE_LIQUID)
		block.m_phase = BlockPhase::LIQUID;
	else if (attrPhase == VALUE_PHASE_SOLID)
		block.m_phase = BlockPhase::SOLID;
	else
		LOG_WARNING << "Unknown block phase " << attrPhase;
}
void world::BlockVariantLoader::loadLight(Block & block, const pugi::xml_node & light) const
{
	const auto attrEmit = light.attribute(ATTR_LIGHT_EMIT).as_string("0 0 0 0");
	const auto attrAbsorb = light.attribute(ATTR_LIGHT_ABSORB).as_string("1 1 1 1");
	const auto attrFilter = light.attribute(ATTR_LIGHT_FILTER).as_string("0 0 0 0");

	block.m_lightEmitted = string::parse<glm::uvec4>(attrEmit);
	block.m_lightAbsorbed = string::parse<glm::uvec4>(attrAbsorb);
	block.m_lightFiltered = string::parse<glm::uvec4>(attrFilter);
}
