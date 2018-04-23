
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
			void setupGui(Engine & engine);
			void setupIO(Engine & engine);
			void setupLogging(Engine & engine);
			void setupMath(Engine & engine);
			void setupStates(Engine & engine);
			void setupUI();
			void setupUniverse(Engine & engine);
		}
	}
}