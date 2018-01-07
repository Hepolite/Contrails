
#pragma once

#include <bitset>

namespace render
{
	namespace scene
	{
		enum class CameraType
		{
			NORMAL,
			MIRROR
		};

		constexpr unsigned int MAX_CAMERA_COUNT = 2u;

		using CameraMask = std::bitset<MAX_CAMERA_COUNT>;
	}
}