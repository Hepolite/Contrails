
#include "SetupAssets.h"

#include "asset/AssetUtil.h"
#include "asset/factory/FactoryFont.h"
#include "asset/factory/FactoryShaderProgram.h"
#include "asset/factory/FactorySprite.h"

void core::setup::setupAssets(Engine & engine)
{
	auto & assets = engine.getAssets();
	assets.clear();

	detail::setupFonts(assets);
	detail::setupShaderPrograms(assets, engine.getUboRegistry());
	detail::setupSprites(assets);
}

void core::setup::detail::setupFonts(asset::AssetRegistry & assetRegistry)
{
	asset::util::setupLoaderFactory<render::allegro::Font, asset::factory::LoaderFont>(
		assetRegistry, "data/fonts", "ttf", "data/fonts/"
	);
}
void core::setup::detail::setupShaderPrograms(asset::AssetRegistry & assetRegistry, render::uboRegistry & uboRegistry)
{
	asset::util::setupLoaderFactory<render::opengl::Program, asset::factory::LoaderShaderProgram>(
		assetRegistry, "data/shaders", "xml", "data/shaders/", uboRegistry
	);
}
void core::setup::detail::setupSprites(asset::AssetRegistry & assetRegistry)
{
	asset::util::setupLoaderFactory<render::allegro::Sprite, asset::factory::LoaderSprite>(
		assetRegistry, "data/sprites", "xml", "data/sprites/"
	);
}
