
#pragma once

#include "logic/state/State.h"

namespace logic
{
	namespace state
	{
		class StateMainMenu : public State
		{
		public:
			virtual void process(const Time & t, const Time & dt) override final;

		private:

		};
	}
}