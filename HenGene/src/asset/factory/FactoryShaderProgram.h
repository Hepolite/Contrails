
#pragma once

#include "io/File.h"
#include "render/opengl/Program.h"
#include "render/uboRegistry.h"

namespace asset
{
	namespace util
	{
		class LoaderShaderProgram
		{
		public:
			void load(render::opengl::Program & asset, const io::File & file, const render::uboRegistry & registry) const;

		private:
			void bindPorts(render::opengl::Program & asset, const render::uboRegistry & registry) const;
		};
	}
}