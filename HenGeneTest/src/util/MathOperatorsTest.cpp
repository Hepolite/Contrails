
#include "CppUnitTest.h"

#include "util/MathOperators.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math
{
	TEST_CLASS(MathOperatorsTest)
	{
	public:
		TEST_METHOD(MathOperatorsSqr)
		{
			Assert::AreEqual(9, sqr(-3));
			Assert::AreEqual(0.25f, sqr(0.5f));
			Assert::AreEqual({ 25.0, 0.0, 4.0 }, sqr(glm::dvec3{ 5.0, 0.0, 2.0 }));
		}

		TEST_METHOD(MathOperatorsSqrt)
		{
			Assert::AreEqual(3, sqrt(9));
			Assert::AreEqual(4.5f, sqrt(20.25f));
			Assert::AreEqual({ 0.5, 9.0 }, sqrt(glm::dvec2{ 0.25, 81.0 }));
		}

		TEST_METHOD(MathOperators_pow)
		{
			Assert::AreEqual(9, pow(-3, 2));
			Assert::AreEqual(6.25f, pow(2.5f, 2));
			Assert::AreEqual(625, pow(5, 4.0));

			Assert::AreEqual({ 8, -27 }, pow(glm::ivec2{ 2, -3 }, 3));
			Assert::AreEqual({ 4.0f, 2.25f, 12.25f }, pow(glm::vec3{ 2.0f, 1.5f, 3.5f }, 2));
			Assert::AreEqual({ 1u, 0u, 256u, 6561u }, pow(glm::uvec4{ 1, 0, 2, 3 }, 8));
		}

		TEST_METHOD(MathOperators_lerp)
		{
			Assert::AreEqual(0.25, lerp(0.0, 1.0, 0.25));
			Assert::AreEqual(3.0f, lerp(0.0f, 4.0f, 0.75f));
			Assert::AreEqual(10, lerp(5, 15, 0.5f));

			Assert::AreEqual({ 0.5f, 1.5f, 3.0f }, lerp(glm::vec3{}, glm::vec3{ 1.0f, 3.0f, 6.0f }, 0.5f));
		}
	};
}