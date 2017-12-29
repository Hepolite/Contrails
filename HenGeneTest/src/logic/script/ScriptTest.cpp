
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
			TEST_METHOD(Script_getHandle)
			{
				Script script;

				auto& handle = script.getHandle();
			}
		};
	}
}