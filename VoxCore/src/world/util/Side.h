
#pragma once

#include <glm/vec3.hpp>
#include <string>

namespace world
{
	namespace util
	{
		struct Side
		{
			unsigned int m_id;
			unsigned int m_opposite;
			std::string m_name;

			glm::ivec3 m_normal;
			glm::ivec3 m_tangentH;
			glm::ivec3 m_tangentV;
			glm::ivec3 m_dimensions;
		};

		const Side SIDE_UNKNOWN	{ 0, 0, "unknown",	{ 0, 0, 0 },	{ 0, 0, 0 },	{ 0, 0, 0 },	{ 0, 1, 2 } };
		const Side SIDE_FRONT	{ 1, 2, "front",	{ 1, 0, 0 },	{ 0, 1, 0 },	{ 0, 0, 1 },	{ 0, 1, 2 } };
		const Side SIDE_BACK	{ 2, 1, "back",		{ -1, 0, 0 },	{ 0, -1, 0 },	{ 0, 0, 1 },	{ 0, 1, 2 } };
		const Side SIDE_LEFT	{ 3, 4, "left",		{ 0, 1, 0 },	{ -1, 0, 0 },	{ 0, 0, 1 },	{ 1, 0, 2 } };
		const Side SIDE_RIGHT	{ 4, 3, "right",	{ 0, -1, 0 },	{ 1, 0, 0 },	{ 0, 0, 1 },	{ 1, 0, 2 } };
		const Side SIDE_TOP		{ 5, 6, "top",		{ 0, 0, 1 },	{ 0, 1, 0 },	{ -1, 0, 0 },	{ 2, 0, 1 } };
		const Side SIDE_BOTTOM	{ 6, 5, "bottom",	{ 0, 0, -1 },	{ 0, -1, 0 },	{ 1, 0, 0 },	{ 2, 0, 1 } };

		const Side SIDES[] = {
			SIDE_FRONT,
			SIDE_BACK,
			SIDE_LEFT,
			SIDE_RIGHT,
			SIDE_TOP,
			SIDE_BOTTOM
		};
		const Side SIDES_AXIS[] = {
			SIDE_FRONT,
			SIDE_LEFT,
			SIDE_TOP
		};
	}
}