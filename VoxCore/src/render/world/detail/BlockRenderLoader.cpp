
#include "BlockRenderLoader.h"

#include "render/world/detail/BlockModelLoader.h"
#include "render/world/detail/BlockTextureLoader.h"
#include "util/Strings.h"

#include <plog/Log.h>

namespace
{
	const std::string MODEL_PATH = "data/universe/models/";
	const std::string TEXTURE_PATH = "data/universe/textures/";

	constexpr const char * NODE_VISUAL = "visual";

	constexpr const char * NODE_DEFAULT = "default";
	constexpr const char * NODE_VARIANT = "variant";
	constexpr const char * NODE_MODEL = "model";
	constexpr const char * NODE_TEXTURE = "texture";
	constexpr const char * NODE_OCCLUDE = "occlude";

	constexpr const char * ATTR_VARIANT_NAME = "name";
	constexpr const char * ATTR_MODEL_PATH = "path";
}


void render::world::BlockRenderLoader::loadBlocks(const io::Folder & folder) const
{
	for (const auto it : folder.getFiles())
		loadBlock(it);
	for (const auto it : folder.getFolders())
		loadBlocks(it);
}
void render::world::BlockRenderLoader::loadBlock(const io::File & file) const
{
	if (m_registry == nullptr || m_blocks == nullptr || m_atlas == nullptr)
	{
		LOG_WARNING << "Attempted to load blocks before block registries and/or texture atlas has been injected";
		return;
	}
	LOG_INFO << "Loading block render from " << file.getPath() << "...";

	pugi::xml_document doc;
	doc.load_file(file.getPath().c_str());

	const auto def = doc.child(NODE_DEFAULT);
	for (auto variant = doc.first_child(); variant; variant = variant.next_sibling())
	{
		if (std::strcmp(NODE_VARIANT, variant.name()) == 0)
		{
			const std::string attrName = variant.attribute(ATTR_VARIANT_NAME).as_string();
			const std::string blockName = file.getName() + (attrName.empty() ? "" : ":" + attrName);

			LOG_INFO << "Loading block render variant " << blockName << "...";

			BlockRenderVariantLoader loader;
			loader.inject(*m_atlas);
			loader.loadVariant(variant.child(NODE_VISUAL));
			(*m_blocks)[(*m_registry)[blockName].m_id] = loader.extractBlock();
		}
	}
}


void render::world::BlockRenderVariantLoader::loadVariant(const pugi::xml_node & variant)
{
	if (const auto node = variant.child(NODE_MODEL))
		loadModel(node);
	if (const auto node = variant.child(NODE_TEXTURE))
		loadTexture(node);
	if (const auto node = variant.child(NODE_OCCLUDE))
		loadOcclusion(node);
}
void render::world::BlockRenderVariantLoader::loadModel(const pugi::xml_node & model)
{
	const auto attrPath = model.attribute(ATTR_MODEL_PATH).as_string();

	const io::File file{ MODEL_PATH + attrPath };
	if (!file.exists())
		return;

	BlockModelLoader loader;
	loader.loadModel(file);
	m_block.m_model = loader.extractModel();
}
void render::world::BlockRenderVariantLoader::loadTexture(const pugi::xml_node & texture)
{
	if (m_atlas == nullptr)
	{
		LOG_WARNING << "Attempted to load blocks before texture atlas has been injected";
		return;
	}

	for (auto attr = texture.first_attribute(); attr; attr = attr.next_attribute())
	{
		const auto attrSide = attr.name();
		const auto attrPath = attr.as_string();

		const io::File file{ TEXTURE_PATH + attrPath };
		if (!file.exists())
			continue;

		BlockTextureLoader loader;
		loader.injectTextureAtlas(*m_atlas);
		loader.loadTexture(file);
		for (const auto & side : ::world::util::fromNameExt(attrSide))
			m_block.m_texture[side.m_id] = loader.extractTexture();
	}
}
void render::world::BlockRenderVariantLoader::loadOcclusion(const pugi::xml_node & occlusion)
{
	for (auto attr = occlusion.first_attribute(); attr; attr = attr.next_attribute())
	for (const auto & side : ::world::util::fromNameExt(attr.name()))
		m_block.m_occlude[side.m_id] = attr.as_bool();
}
