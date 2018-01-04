
#include "CppUnitTest.h"

#include "logic/script/Script.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace script
	{
		TEST_CLASS(ScriptTest)
		{
		public:
			TEST_METHOD(Script_execute)
			{
				Script script;

				Assert::IsTrue(script.execute("var foo = 3;"));
				Assert::IsTrue(script.execute([]() {}));
				Assert::IsFalse(script.execute("malformed code"));
				Assert::IsFalse(script.execute([]() { throw std::exception(""); }));
			}
		};
	}
}