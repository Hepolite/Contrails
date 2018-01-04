
#include "SetupAssets.h"

#include "asset/AssetUtil.h"
#include "asset/factory/LoaderShaderProgram.h"

void core::setup::setupAssets(Engine & engine)
{
	auto & assets = engine.getAssets();
	assets.clear();

	detail::setupShaderPrograms(assets, engine.getUboRegistry());
}

void core::setup::detail::setupShaderPrograms(asset::AssetRegistry & assetRegistry, render::uboRegistry & uboRegistry)
{
	asset::util::setupLoaderFactory<render::opengl::Program, asset::util::LoaderShaderProgram>(
		assetRegistry, "data/shaders", "xml", "data/shaders", uboRegistry
	);
}
