
#include "BlockRenderLoader.h"

namespace
{
	constexpr const char * NODE_DEFAULT = "default";

	constexpr const char * NODE_VARIANT = "variant";
	constexpr const char * VALUE_VARIANT_NAME = "name";

	constexpr const char * NODE_MODEL = "model";
	constexpr const char * NODE_TEXTURE = "texture";
	constexpr const char * NODE_OCCLUDE = "occlude";
}

void render::world::BlockRenderVariantLoader::loadVariant(data::BlockRender & block, const pugi::xml_node & variant, const pugi::xml_node & def) const
{
	loadModel(block, variant.child(NODE_MODEL), def.child(NODE_MODEL));
	loadTexture(block, variant.child(NODE_TEXTURE), def.child(NODE_TEXTURE));
	loadOcclusion(block, variant.child(NODE_OCCLUDE), def.child(NODE_OCCLUDE));
}
void render::world::BlockRenderVariantLoader::loadModel(data::BlockRender & block, const pugi::xml_node & model, const pugi::xml_node & def) const
{
}
void render::world::BlockRenderVariantLoader::loadTexture(data::BlockRender & block, const pugi::xml_node & texture, const pugi::xml_node & def) const
{
}
void render::world::BlockRenderVariantLoader::loadOcclusion(data::BlockRender & block, const pugi::xml_node & occlusion, const pugi::xml_node & def) const
{
	for (auto attr = def.first_attribute(); attr; attr = attr.next_attribute())
	for (const auto & side : ::world::util::fromNameExt(attr.name()))
		block.m_occlude[side.m_id] = attr.as_bool();

	for (auto attr = occlusion.first_attribute(); attr; attr = attr.next_attribute())
	for (const auto & side : ::world::util::fromNameExt(attr.name()))
		block.m_occlude[side.m_id] = attr.as_bool();
}
