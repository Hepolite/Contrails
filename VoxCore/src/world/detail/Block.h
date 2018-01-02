
#pragma once

#include "world/detail/Limits.h"

#include <glm/vec4.hpp>
#include <string>

namespace world
{
	enum class BlockPhase
	{
		SOLID,
		LIQUID,
		GAS
	};

	struct Block
	{
		unsigned int m_id = 0u;
		std::string m_name = "air";

		BlockPhase m_phase = BlockPhase::GAS;

		glm::uvec4 m_lightEmitted{ 0u };
		glm::uvec4 m_lightAbsorbed{ 1u };
		glm::uvec4 m_lightFiltered{ data::MAX_BLOCK_LIGHT };
	};
}