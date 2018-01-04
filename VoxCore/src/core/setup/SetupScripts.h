
#pragma once

#include "core/Engine.h"

namespace core
{
	namespace setup
	{
		void setupScripts(Engine & engine);

		namespace detail
		{
			void setupEngine(Engine & engine);
			void setupUniverse(Engine & engine);
		}
	}
}