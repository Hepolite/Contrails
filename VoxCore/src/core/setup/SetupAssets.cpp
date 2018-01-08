
#include "SetupAssets.h"

#include "asset/AssetUtil.h"
#include "asset/factory/FactoryShaderProgram.h"
#include "asset/factory/FactorySprite.h"

void core::setup::setupAssets(Engine & engine)
{
	auto & assets = engine.getAssets();
	assets.clear();

	detail::setupShaderPrograms(assets, engine.getUboRegistry());
	detail::setupSprites(assets);
}

void core::setup::detail::setupShaderPrograms(asset::AssetRegistry & assetRegistry, render::uboRegistry & uboRegistry)
{
	asset::util::setupLoaderFactory<render::opengl::Program, asset::util::LoaderShaderProgram>(
		assetRegistry, "data/shaders", "xml", "data/shaders", uboRegistry
	);
}
void core::setup::detail::setupSprites(asset::AssetRegistry & assetRegistry)
{
	asset::util::setupLoaderFactory<render::allegro::Sprite, asset::util::LoaderSprite>(
		assetRegistry, "data/sprites", "xml", "data/sprites"
	);
}
