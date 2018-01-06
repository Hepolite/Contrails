
#pragma once

#include "util/Physics.h"

namespace render
{
	namespace core
	{
		class Pipeline
		{
		public:
			void render(const Time & t, const Time & dt) const;
		};
	}
}