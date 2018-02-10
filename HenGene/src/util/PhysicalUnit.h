
#pragma once

namespace physics
{
	template<int M, int L, int T, int I, int Θ>
	struct Unit
	{
		enum { kilogram = M, metre = L, second = T, ampere = I, kelvin = Θ };
	};

	using UnitAcceleration		= Unit<0, 1, -2, 0, 0>;
	using UnitArea				= Unit<0, 2, 0, 0, 0>;
	using UnitDensity			= Unit<1, -3, 0, 0, 0>;
	using UnitDimensionless		= Unit<0, 0, 0, 0, 0>;
	using UnitEnergy			= Unit<1, 2, -2, 0, 0>;
	using UnitForce				= Unit<1, 1, -2, 0, 0>;
	using UnitFrequency			= Unit<0, 0, -1, 0, 0>;
	using UnitLength			= Unit<0, 1, 0, 0, 0>;
	using UnitMass				= Unit<1, 0, 0, 0, 0>;
	using UnitMomentum			= Unit<1, 1, -1, 0, 0>;
	using UnitPressure			= Unit<1, -1, -2, 0, 0>;
	using UnitSpeed				= Unit<0, 1, -1, 0, 0>;
	using UnitTemperature		= Unit<0, 0, 0, 0, 1>;
	using UnitTime				= Unit<0, 0, 1, 0, 0>;
	using UnitVolue				= Unit<0, 0, 3, 0, 0>;

	//using Unit_ = Unit<0, 0, 0, 0, 0>;
}