
#pragma once

namespace physics
{
	template<typename Unit>
	class Scalar
	{
	public:
		constexpr explicit Scalar() noexcept = default;
		constexpr explicit Scalar(const long double & magnitude) noexcept : m_magnitude(magnitude) {}

		constexpr auto & operator=(const Scalar & other) noexcept { m_magnitude = other(); return *this; }
		constexpr auto & operator()() const noexcept { return m_magnitude; }
		auto & operator()() noexcept { return m_magnitude; }

	private:
		long double m_magnitude = 0.0L;
	};

	template<typename Unit>
	class Vector
	{
	public:
		constexpr explicit Vector() noexcept = default;
		constexpr explicit Vector(const Scalar<Unit> & x, const Scalar<Unit> & y, const Scalar<Unit> & z) noexcept : m_x(x()), m_y(y()), m_z(z()) {}
		constexpr explicit Vector(const long double & x, const long double & y, const long double & z) noexcept : m_x(x), m_y(y), m_z(z) {}

		constexpr auto & operator=(const Vector & other) noexcept { m_x = other.m_x; m_y = other.m_y; m_z = other.m_z; return *this; }
		constexpr auto & x() const { return m_x; }
		auto & x() { return m_x; }
		constexpr auto& y() const { return m_y; }
		auto & y() { return m_y; }
		constexpr auto& z() const { return m_z; }
		auto & z() { return m_z; }

	private:
		long double m_x = 0.0L;
		long double m_y = 0.0L;
		long double m_z = 0.0L;
	};
}