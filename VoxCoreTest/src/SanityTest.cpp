
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace sanity
{
	TEST_CLASS(SanityTest)
	{
	public:
		TEST_METHOD(Sanity_sanity)
		{
			Assert::IsTrue(true);
		}
	};
}