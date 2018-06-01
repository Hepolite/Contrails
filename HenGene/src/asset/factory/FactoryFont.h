
#pragma once

#include "io/File.h"
#include "render/allegro/Font.h"

namespace asset
{
	namespace factory
	{
		class LoaderFont
		{
		public:
			inline void load(render::allegro::Font & asset, const io::File & file) const { asset.load(file); }
		};
	}
}