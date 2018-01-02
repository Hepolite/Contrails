
#include "CppUnitTest.h"

#include "util/MathOperators.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math
{
	TEST_CLASS(MathOperatorsTest)
	{
	public:
		TEST_METHOD(MathOperators_pow)
		{
			Assert::AreEqual(9, pow(-3, 2));
			Assert::AreEqual(6.25f, pow(2.5f, 2));
			Assert::AreEqual(625, pow(5, 4.0));

			Assert::AreEqual({ 8, -27 }, pow(glm::ivec2{ 2, -3 }, 3));
			Assert::AreEqual({ 4.0f, 2.25f, 12.25f }, pow(glm::vec3{ 2.0f, 1.5f, 3.5f }, 2));
			Assert::AreEqual({ 1u, 0u, 256u, 6561u }, pow(glm::uvec4{ 1, 0, 2, 3 }, 8));
		}
	};
}