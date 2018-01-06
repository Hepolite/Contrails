
#pragma once

#include <bitset>

namespace logic
{
	namespace ecs
	{
		constexpr unsigned int MAX_COMPONENTS = 64;

		using ComponentMask = std::bitset<MAX_COMPONENTS>;
	}
}