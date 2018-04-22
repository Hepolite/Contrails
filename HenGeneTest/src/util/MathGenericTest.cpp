
#include "CppUnitTest.h"

#include "util/MathGeneric.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace math
{
	TEST_CLASS(MathGenericTest)
	{
	public:
		TEST_METHOD(MathGeneric_minNumeric)
		{
			Assert::AreEqual(4, min(4, 7));
			Assert::AreEqual(-2.5f, min({ 4.1f, -2.5f, -1.0f, 5.25f }));
		}
		TEST_METHOD(MathGeneric_maxNumeric)
		{
			Assert::AreEqual(7, max(4, 7));
			Assert::AreEqual(5.25f, max({ 4.1f, -2.5f, -1.0f, 5.25f }));
		}
		TEST_METHOD(MathGeneric_minVector)
		{
			Assert::AreEqual({ -2, 0 }, min<int>({ 3, 0 }, { -2, 5 }));
			Assert::AreEqual(-1, min<int>({ 3, -1 }));
			Assert::AreEqual({ 2.5f, 0.125f, 6.0f }, min<float>({ 3.7f, 2.0f, 6.0f }, { 2.5f, 0.125f, 12.0f }));
			Assert::AreEqual(-42.0, min<double>({ 3.14, 1337.0, -42.0 }));
			Assert::AreEqual({ -1, 4, 2, 0 }, min<int>({ -1, 8, 2, 0 }, { 4, 4, 4, 4 }));
			Assert::AreEqual(0, min<int>({ 6, 1, 8, 0 }));
		}
		TEST_METHOD(MathGeneric_maxVector)
		{
			Assert::AreEqual({ 3, 5 }, max<int>({ 3, 0 }, { -2, 5 }));
			Assert::AreEqual(3, max<int>({ 3, -1 }));
			Assert::AreEqual({ 3.7f, 2.0f, 12.0f }, max<float>({ 3.7f, 2.0f, 6.0f }, { 2.5f, 0.125f, 12.0f }));
			Assert::AreEqual(1337.0, max<double>({ 3.14, 1337.0, -42.0 }));
			Assert::AreEqual({ 4, 8, 4, 4 }, max<int>({ -1, 8, 2, 0 }, { 4, 4, 4, 4 }));
			Assert::AreEqual(8, max<int>({ 6, 1, 8, 0 }));
		}

		TEST_METHOD(MathGeneric_abs)
		{
			Assert::AreEqual(4, abs(4));
			Assert::AreEqual(0, abs(0));
			Assert::AreEqual(2, abs(-2));

			Assert::AreEqual({ 5.44f, 5.44f }, abs<float>({ 5.44f, -5.44f }));
			Assert::AreEqual({ 0.0f, 2.1f, 1.5f }, abs<float>({ 0.0f, -2.1f, 1.5f }));
			Assert::AreEqual({ 0.0f, 0.1f, 3.5f, 42.0f }, abs<float>({ 0.0f, 0.1f, 3.5f, -42.0f }));
		}
		TEST_METHOD(MathGeneric_sign)
		{
			Assert::AreEqual(1, sign(4));
			Assert::AreEqual(0, sign(0));
			Assert::AreEqual(-1, sign(-2));

			Assert::AreEqual({ 1, -1 }, sign<float>({ 5.44f, -5.44f }));
			Assert::AreEqual({ 0, -1, 1 }, sign<float>({ 0.0f, -2.1f, 1.5f}));
			Assert::AreEqual({ 0, 1, 1, -1 }, sign<float>({ 0.0f, 0.1f, 3.5f, -42.0f }));
		}
		TEST_METHOD(MathGeneric_signp)
		{
			Assert::AreEqual(1, signp(3));
			Assert::AreEqual(1, signp(0));
			Assert::AreEqual(-1, signp(-1));

			Assert::AreEqual({ 1, -1 }, signp<float>({ 5.44f, -5.44f }));
			Assert::AreEqual({ 1, -1, 1 }, signp<float>({ 0.0f, -2.1f, 1.5f }));
			Assert::AreEqual({ 1, 1, 1, -1 }, signp<float>({ 0.0f, 0.1f, 3.5f, -42.0f }));
		}

		TEST_METHOD(MathGeneric_rouding)
		{
			Assert::AreEqual(5, floor(5.9f));
			Assert::AreEqual(-4, floor(-3.1f));

			Assert::AreEqual(2, round(1.5f));
			Assert::AreEqual(2, round(2.49f));
			Assert::AreEqual(-5, round(-5.3f));
			Assert::AreEqual(-5, round(-4.5f));

			Assert::AreEqual(3, ceil(2.1f));
			Assert::AreEqual(-4, ceil(-4.9f));
		}

		TEST_METHOD(MathGeneric_intbound)
		{
			Assert::IsTrue(equal(0.0f, intbound(5, 1)));
			Assert::IsTrue(equal(3.0f, intbound(2.1f, 0.3f)));
			Assert::IsTrue(equal(2.5f, intbound(0.5, 0.2)));
		}

	private:
		template<typename T> bool equal(const T & v1, const T & v2)
		{
			return abs(v1 - v2) <= static_cast<T>(0.0001);
		}
	};
}