
#pragma once

#include "logic/ecs/detail/ComponentMask.h"

namespace logic
{
	namespace ecs
	{
		using EntityID = unsigned int;

		struct Entity
		{
			EntityID m_id;
			ComponentMask m_mask;
		};
	}
}