
#pragma once

#include "asset/AssetRegistry.h"
#include "core/Engine.h"
#include "render/uboRegistry.h"

namespace core
{
	namespace setup
	{
		void setupAssets(Engine & engine);

		namespace detail
		{
			void setupShaderPrograms(asset::AssetRegistry & assetRegistry, render::uboRegistry & uboRegistry);
			void setupSprites(asset::AssetRegistry & assetRegistry);
		}
	}
}