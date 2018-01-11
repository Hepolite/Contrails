
#include "CppUnitTest.h"

#include "util/StringGeneric.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace string
{
	TEST_CLASS(StringGenericTest)
	{
	public:
		TEST_METHOD(StringGeneric_split)
		{
			const auto dataA = split("Hello World! Foobar", ' ');
			const auto dataB = split("Hello World! Foobar", 'o');

			Assert::AreEqual(3u, dataA.size());
			Assert::AreEqual({ "Hello" }, dataA[0u]);
			Assert::AreEqual({ "World!" }, dataA[1u]);
			Assert::AreEqual({ "Foobar" }, dataA[2u]);

			Assert::AreEqual(5u, dataB.size());
			Assert::AreEqual({ "Hell" }, dataB[0u]);
			Assert::AreEqual({ " W" }, dataB[1u]);
			Assert::AreEqual({ "rld! F" }, dataB[2u]);
			Assert::AreEqual({ "" }, dataB[3u]);
			Assert::AreEqual({ "bar" }, dataB[4u]);
		}

		TEST_METHOD(StringGeneric_replace)
		{
			Assert::AreEqual({ "That is a string" }, replace("This is a string", "is", "at"));
			Assert::AreEqual({ "HeFoolo World!" }, replace("Hello World!", "l", "Foo"));
			Assert::AreEqual({ "Value: 42/%d" }, replace("Value: %d/%d", "%d", std::to_string(42)));
			Assert::AreEqual({ "data/sprites/sprite_name" }, replace("data/sprites/sprite_name.xml", ".xml", ""));
		}
		TEST_METHOD(StringGeneric_replaceAll)
		{
			Assert::AreEqual({ "String" }, replaceAll("String", "", "foo"));
			Assert::AreEqual({ "HeFooFooo WorFood!" }, replaceAll("Hello World!", "l", "Foo"));
			Assert::AreEqual({ "Value: 42/42" }, replaceAll("Value: %d/%d", "%d", std::to_string(42)));
		}
	};
}