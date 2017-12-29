
#pragma once

#include "PhysicalUnit.h"
#include "PhysicalValue.h"
#include "PhysicalOperators.h"

using Acceleration = physics::Scalar<physics::UnitAcceleration>;
using AccelerationVec = physics::Vector<physics::UnitAcceleration>;
using Area = physics::Scalar<physics::UnitArea>;
using Density = physics::Scalar<physics::UnitDensity>;
using Dimensionless = physics::Scalar<physics::UnitDimensionless>;
using Energy = physics::Scalar<physics::UnitEnergy>;
using Force = physics::Scalar<physics::UnitForce>;
using ForceVec = physics::Vector<physics::UnitForce>;
using Frequency = physics::Scalar<physics::UnitFrequency>;
using Length = physics::Scalar<physics::UnitLength>;
using LengthVec = physics::Vector<physics::UnitLength>;
using Mass = physics::Scalar<physics::UnitMass>;
using Momentum = physics::Scalar<physics::UnitMomentum>;
using MomentumVec = physics::Vector<physics::UnitMomentum>;
using Pressure = physics::Scalar<physics::UnitPressure>;
using Speed = physics::Scalar<physics::UnitSpeed>;
using SpeedVec = physics::Vector<physics::UnitSpeed>;
using Temperature = physics::Scalar<physics::UnitTemperature>;
using Time = physics::Scalar<physics::UnitTime>;
using Volume = physics::Scalar<physics::UnitVolue>;

constexpr Acceleration	operator"" _ms2(long double magnitude) { return Acceleration{ magnitude }; }
constexpr Force			operator"" _N(long double magnitude) { return Force{ magnitude }; }
constexpr Length		operator"" _m(long double magnitude) { return Length{ magnitude }; }
constexpr Mass			operator"" _kg(long double magnitude) { return Mass{ magnitude }; }
constexpr Speed			operator"" _ms(long double magnitude) { return Speed{ magnitude }; }
constexpr Time			operator"" _s(long double magnitude) { return Time{ magnitude }; }