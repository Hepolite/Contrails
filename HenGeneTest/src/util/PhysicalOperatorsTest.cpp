
#include "CppUnitTest.h"

#include "util/Physics.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace physics
{
	TEST_CLASS(PhysicalOperatorsTest)
	{
	public:
		TEST_METHOD(PhysicalOperators_scalar)
		{
			constexpr Speed speed = 3.5_ms + 2.2_ms;
			constexpr Length length = 7.22_m - 1.5_m;
			constexpr Force force = 20.0_kg * 9.81_ms2;
			constexpr Density density = 481.0_kg / (10.0_m * 10.0_m * 10.0_m);

			constexpr Acceleration acceleration = 0.55_ms2 * 5.0;
		}

		TEST_METHOD(PhysicalOperators_vector)
		{
			constexpr SpeedVec velocity = SpeedVec{ 0.3, 0.7, -0.1 } + SpeedVec{ 1.2, -0.4, -0.2 };
			constexpr ForceVec force = 15.0_kg * AccelerationVec{ 3.0, 0.0, -9.81 };
		}
	};
}