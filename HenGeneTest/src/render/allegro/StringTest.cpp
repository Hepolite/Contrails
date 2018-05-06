
#include "CppUnitTest.h"

#include "render/allegro/String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(StringTest)
		{
		public:
			TEST_METHOD(String_ctor)
			{
				String stringA{ "Hello World" };
				String stringB{ String{ "Existed already" } };
				String stringC{ std::move(String{ "More testing" }) };

				Assert::AreEqual("Hello World", stringA.c_str());
				Assert::AreEqual("Existed already", stringB.c_str());
				Assert::AreEqual("More testing", stringC.c_str());
			}
			TEST_METHOD(String_assign)
			{
				const String tmp{ "Copied" };
				String stringA = tmp;
				String stringB = std::move(String{ "Moved" });
				String stringC = "Foo";

				Assert::AreEqual("Copied", stringA.c_str());
				Assert::AreEqual("Moved", stringB.c_str());
				Assert::AreEqual("Foo", stringC.c_str());
			}

			TEST_METHOD(String_empty)
			{
				String stringA;
				String stringB{ "Foo" };

				Assert::IsTrue(stringA.empty());
				Assert::IsFalse(stringB.empty());
			}
			TEST_METHOD(String_size)
			{
				String stringA;
				String stringB{ "Wololoo" };

				Assert::AreEqual(0u, stringA.size());
				Assert::AreEqual(7u, stringB.size());
			}

			TEST_METHOD(String_add)
			{
				String stringA = "Hello";
				String stringB = "World";

				stringA += " ";
				Assert::AreEqual("Hello World", (stringA + stringB).c_str());
			}
			TEST_METHOD(String_compare)
			{
				String stringA = "Same";
				String stringB = "Same";
				String stringC = "Different";

				Assert::IsTrue(stringA == stringB);
				Assert::IsTrue(stringA != stringC);
				Assert::IsFalse(stringB == stringC);
				Assert::IsFalse(stringC != stringC);
			}
		};
	}
}