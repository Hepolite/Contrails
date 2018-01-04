
#pragma once

namespace math
{
	template<typename T> constexpr T PI = T(3.1415926535897932384626433L);

	template<typename T> constexpr T DEG_TO_RAD = PI<T> / T(180);
	template<typename T> constexpr T RAD_TO_DEG = T(180) / PI<T>;
}