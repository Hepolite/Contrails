
#pragma once

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

namespace math
{
	template<typename T> constexpr T sqr(const T & v)
	{
		return v * v;
	}

	template<typename T> constexpr T sqrt(const T & v)
	{
		return static_cast<T>(std::sqrt(v));
	}
	template<typename T> constexpr glm::tvec2<T> sqrt(const glm::tvec2<T> & v)
	{
		return { sqrt(v.x), sqrt(v.y) };
	}
	template<typename T> constexpr glm::tvec3<T> sqrt(const glm::tvec3<T> & v)
	{
		return { sqrt(v.x), sqrt(v.y), sqrt(v.z) };
	}
	template<typename T> constexpr glm::tvec4<T> sqrt(const glm::tvec4<T> & v)
	{
		return { sqrt(v.x), sqrt(v.y), sqrt(v.z), sqrt(v.w) };
	}

	template<typename T, typename P> constexpr T pow(const T & base, const P & exp)
	{
		return static_cast<T>(std::pow(base, exp));
	}
	template<typename T, typename P> constexpr glm::tvec2<T> pow(const glm::tvec2<T> & base, const P & exp)
	{
		return { pow(base.x, exp), pow(base.y, exp) };
	}
	template<typename T, typename P> constexpr glm::tvec3<T> pow(const glm::tvec3<T> & base, const P & exp)
	{
		return { pow(base.x, exp), pow(base.y, exp), pow(base.z, exp) };
	}
	template<typename T, typename P> constexpr glm::tvec4<T> pow(const glm::tvec4<T> & base, const P & exp)
	{
		return { pow(base.x, exp), pow(base.y, exp), pow(base.z, exp), pow(base.w, exp) };
	}

	template<typename T, typename P> constexpr T lerp(const T & v1, const T & v2, const P & dt)
	{
		return static_cast<T>(v1 * (P{ 1 } - dt) + v2 * dt);
	}
}