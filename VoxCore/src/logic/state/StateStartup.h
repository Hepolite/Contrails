
#pragma once

#include "core/Engine.h"
#include "logic/state/State.h"

#include <iostream>

namespace logic
{
	namespace state
	{
		class StateStartup : public State
		{
		public:
			StateStartup() = delete;
			StateStartup(core::Engine & engine);
			~StateStartup() = default;

			inline virtual void process(const Time & t, const Time & dt) override final {}
		};
	}
}