
#pragma once

#include "logic/state/State.h"

namespace logic
{
	namespace state
	{
		class StateEditorWorld : public State<StateEditorWorld>
		{
		public:
			virtual void initialize(core::Engine & engine) override final;
			virtual void deinitialize(core::Engine & engine) override final;
			virtual void process(const Time & t, const Time & dt) override final;
		};
	}
}