
#pragma once

#include "util/Physics.h"

namespace logic
{
	namespace state
	{
		class State
		{
		public:
			virtual void process(const Time & t, const Time & dt) = 0;
		};
	}
}