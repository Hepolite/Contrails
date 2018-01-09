
#pragma once

#include "render/allegro/Sprite.h"

namespace asset
{
	namespace factory
	{
		class LoaderSprite
		{
		public:
			void load(render::allegro::Sprite & asset, const io::File & file) const;
		};

		class BuilderSprite
		{
		public:
			void build(render::allegro::Sprite & asset, unsigned int width, unsigned int height) const;
		};
	}
}