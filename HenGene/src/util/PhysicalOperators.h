
#pragma once

#include "PhysicalUnit.h"
#include "PhysicalValue.h"

#define PHYSICAL_TEMPLATE template<int M, int L, int T, int I, int Θ>
#define PHYSICAL_TEMPLATE_EXT template<int M, int L, int T, int I, int Θ, int M2, int L2, int T2, int I2, int Θ2>

#define PHYSICAL_SCALAR physics::Scalar<physics::Unit<M, L, T, I, Θ>>
#define PHYSICAL_VECTOR physics::Vector<physics::Unit<M, L, T, I, Θ>>
#define PHYSICAL_SCALAR_EXT physics::Scalar<physics::Unit<M2, L2, T2, I2, Θ2>>
#define PHYSICAL_VECTOR_EXT physics::Vector<physics::Unit<M2, L2, T2, I2, Θ2>>
#define PHYSICAL_SCALAR_ADD physics::Scalar<physics::Unit<M + M2, L + L2, T + T2, I + I2, Θ + Θ2>>
#define PHYSICAL_VECTOR_ADD physics::Vector<physics::Unit<M + M2, L + L2, T + T2, I + I2, Θ + Θ2>>
#define PHYSICAL_SCALAR_SUB physics::Scalar<physics::Unit<M - M2, L - L2, T - T2, I - I2, Θ - Θ2>>
#define PHYSICAL_VECTOR_SUB physics::Vector<physics::Unit<M - M2, L - L2, T - T2, I - I2, Θ - Θ2>>

namespace physics
{
	PHYSICAL_TEMPLATE constexpr bool operator<(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return lhs() < rhs(); }
	PHYSICAL_TEMPLATE constexpr bool operator<(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return lhs() < rhs; }
	PHYSICAL_TEMPLATE constexpr bool operator<(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return lhs < rhs(); }
	PHYSICAL_TEMPLATE constexpr bool operator>(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return rhs < lhs; }
	PHYSICAL_TEMPLATE constexpr bool operator>(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return rhs < lhs; }
	PHYSICAL_TEMPLATE constexpr bool operator>(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return rhs < lhs; }
	PHYSICAL_TEMPLATE constexpr bool operator<=(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return !(rhs < lhs); }
	PHYSICAL_TEMPLATE constexpr bool operator<=(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return !(rhs < lhs); }
	PHYSICAL_TEMPLATE constexpr bool operator<=(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return !(rhs < lhs); }
	PHYSICAL_TEMPLATE constexpr bool operator>=(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return !(lhs < rhs); }
	PHYSICAL_TEMPLATE constexpr bool operator>=(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return !(lhs < rhs); }
	PHYSICAL_TEMPLATE constexpr bool operator>=(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return !(lhs < rhs); }

	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator+(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return PHYSICAL_SCALAR{ lhs() + rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR & operator+=(PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { lhs() += rhs(); return lhs; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator-(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return PHYSICAL_SCALAR{ lhs() - rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator-(const PHYSICAL_SCALAR & lhs) noexcept { return PHYSICAL_SCALAR{ -lhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR & operator-=(PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR & rhs) noexcept { lhs() -= rhs(); return lhs; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_SCALAR_ADD operator*(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR_EXT & rhs) noexcept { return PHYSICAL_SCALAR_ADD{ lhs() * rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator*(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return PHYSICAL_SCALAR{ lhs() * rhs }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator*(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return PHYSICAL_SCALAR{ lhs * rhs() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_SCALAR_SUB operator/(const PHYSICAL_SCALAR & lhs, const PHYSICAL_SCALAR_EXT & rhs) noexcept { return PHYSICAL_SCALAR_SUB{ lhs() / rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator/(const PHYSICAL_SCALAR & lhs, const long double & rhs) noexcept { return PHYSICAL_SCALAR{ lhs() / rhs }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_SCALAR operator/(const long double & lhs, const PHYSICAL_SCALAR & rhs) noexcept { return PHYSICAL_SCALAR{ lhs / rhs() }; }

	// ...

	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator+(const PHYSICAL_VECTOR & lhs, const PHYSICAL_VECTOR & rhs) noexcept { return PHYSICAL_VECTOR{ lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator-(const PHYSICAL_VECTOR & lhs, const PHYSICAL_VECTOR & rhs) noexcept { return PHYSICAL_VECTOR{ lhs.x() - rhs.x(), lhs.y() - rhs.y(), lhs.z() - rhs.z() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator-(const PHYSICAL_VECTOR & lhs) noexcept { return PHYSICAL_VECTOR{ -lhs.x(), -lhs.y(), -lhs.z() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_ADD operator*(const PHYSICAL_VECTOR & lhs, const PHYSICAL_VECTOR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_ADD{ lhs.x() * rhs.x(), lhs.y() * rhs.y(), lhs.z() * rhs.z() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_ADD operator*(const PHYSICAL_SCALAR & lhs, const PHYSICAL_VECTOR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_ADD{ lhs() * rhs.x(), lhs() * rhs.y(), lhs() * rhs.z() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_ADD operator*(const PHYSICAL_VECTOR & lhs, const PHYSICAL_SCALAR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_ADD{ lhs.x() * rhs(), lhs.y() * rhs(), lhs.z() * rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator*(const long double & lhs, const PHYSICAL_VECTOR & rhs) noexcept { return PHYSICAL_VECTOR{ lhs * rhs.x(), lhs * rhs.y(), lhs * rhs.z() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator*(const PHYSICAL_VECTOR & lhs, const long double & rhs) noexcept { return PHYSICAL_VECTOR{ lhs.x() * rhs, lhs.y() * rhs, lhs.z() * rhs }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_SUB operator/(const PHYSICAL_VECTOR & lhs, const PHYSICAL_VECTOR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_SUB{ lhs.x() / rhs.x(), lhs.y() / rhs.y(), lhs.z() / rhs.z() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_SUB operator/(const PHYSICAL_SCALAR & lhs, const PHYSICAL_VECTOR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_SUB{ lhs() / rhs.x(), lhs() / rhs.y(), lhs() / rhs.z() }; }
	PHYSICAL_TEMPLATE_EXT constexpr PHYSICAL_VECTOR_SUB operator/(const PHYSICAL_VECTOR & lhs, const PHYSICAL_SCALAR_EXT & rhs) noexcept { return PHYSICAL_VECTOR_SUB{ lhs.x() / rhs(), lhs.y() / rhs(), lhs.z() / rhs() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator/(const long double & lhs, const PHYSICAL_VECTOR & rhs) noexcept { return PHYSICAL_VECTOR{ lhs / rhs.x(), lhs / rhs.y(), lhs / rhs.z() }; }
	PHYSICAL_TEMPLATE constexpr PHYSICAL_VECTOR operator/(const PHYSICAL_VECTOR & lhs, const long double & rhs) noexcept { return PHYSICAL_VECTOR{ lhs.x() / rhs, lhs.y() / rhs, lhs.z() / rhs }; }
}