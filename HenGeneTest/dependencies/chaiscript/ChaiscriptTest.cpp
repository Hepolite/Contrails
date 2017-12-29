
#include "CppUnitTest.h"

#include <chaiscript/chaiscript.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace integration
{
	TEST_CLASS(ChaiscriptTest)
	{
	public:
		TEST_METHOD(Chaiscript_integration)
		{
			chaiscript::ChaiScript script;

			Assert::AreEqual(8, script.eval<int>("5 + 3"));
		}
	};
}