
#pragma once

#include "core/Engine.h"

namespace core
{
	namespace setup
	{
		void initialize(Engine & engine);

		namespace detail
		{
			void setupEvents(Engine & engine);
		}
	}
}