
#include "CppUnitTest.h"

#include "util/StringParsing.h"

#include <glm/Unittest.h>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace string
{
	TEST_CLASS(StringParsingTest)
	{
	public:
		TEST_METHOD(StringParsing_parseBasic)
		{
			Assert::AreEqual(-4, parse<int>("-4"));
			Assert::AreEqual(37u, parse<unsigned int>("37u"));
			Assert::AreEqual(3.14f, parse<float>("3.14"));
			Assert::AreEqual({ "Hello World" }, parse<std::string>("Hello World"));

			Assert::AreEqual(0, parse<int>("not legal"));
			Assert::AreEqual(3, parse<int>("not legal", 3));
		}

		TEST_METHOD(StringParsing_parseVector)
		{
			const std::vector<int> intData = { 0, 1, 3 };
			const std::vector<float> floatData = { 0.5f, 1.5f, 3.14f };
			const std::vector<std::string> stringData = { "Hello", "World!", "Foobar" };

			const auto intParsed = string::parseVector<int>("0 1 3");
			const auto floatParsed = string::parseVector<float>("0.5 1.5 3.14");
			const auto stringParsed = string::parseVector<std::string>("Hello World! Foobar");

			for (unsigned int i = 0u; i < 3u; ++i)
			{
				Assert::AreEqual(intData[i], intParsed[i]);
				Assert::AreEqual(floatData[i], floatParsed[i]);
				Assert::AreEqual(stringData[i], stringParsed[i]);
			}
		}

		TEST_METHOD(StringParsing_parseVec)
		{
			Assert::AreEqual({ -1, 3 }, parse<glm::ivec2>("-1 3"));
			Assert::AreEqual({ 5u, 7u, 2u }, parse<glm::uvec3>("5 7 2"));
			Assert::AreEqual({ 3.14f, 6.67f, 9.0f, -5.1f }, parse<glm::vec4>("3.14 6.67 9 -5.1"));

			Assert::AreEqual({ 3, 2 }, parse<glm::ivec2>("", { 3, 2 }));
			Assert::AreEqual({ 1, 2, 3 }, parse<glm::ivec3>("3 7", { 1, 2, 3 }));
			Assert::AreEqual({ -3.14f, 2.5f, 3.14f, 0.0f }, parse<glm::vec4>("0 0 0 0 0", { -3.14f, 2.5f, 3.14f, 0.0f }));
		}
	};
}