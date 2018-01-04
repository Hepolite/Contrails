
#pragma once

#include "util/Physics.h"

namespace core { class Engine; }

namespace logic
{
	namespace state
	{
		class State
		{
		public:
			virtual void initialize(core::Engine & engine) = 0;
			virtual void deinitialize(core::Engine & engine) = 0;
			virtual void process(const Time & t, const Time & dt) = 0;
		};
	}
}