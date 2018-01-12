
#pragma once

#include "util/Physics.h"

#include <typeindex>

namespace core { class Engine; }

namespace logic
{
	namespace state
	{
		class StateBase
		{
		public:
			StateBase() = default;
			virtual ~StateBase() = default;

			virtual std::type_index type() const = 0;

			virtual void initialize(core::Engine & engine) = 0;
			virtual void deinitialize(core::Engine & engine) = 0;
			virtual void process(const Time & t, const Time & dt) = 0;
		};

		template<class Type>
		class State : public StateBase
		{
		public:
			virtual std::type_index type() const override final { return typeid(Type); }
		};
	}
}