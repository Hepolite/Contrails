
#include "CppUnitTest.h"

#include "logic/ecs/detail/ComponentData.h"

#include <glm/vec3.hpp>
#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace ecs
	{
		TEST_CLASS(ComponentDataTest)
		{
		public:
			TEST_METHOD(ComponentData_access)
			{
				ComponentData<glm::vec3> data;
				data[2u] = { 3, 1, 4 };
				data[0u] = { 0, 42, 1337 };

				Assert::AreEqual({ 0, 42, 1337 }, data[0u]);
				Assert::AreEqual({ 0, 0, 0 }, data[1u]);
				Assert::AreEqual({ 3, 1, 4 }, data[2u]);
				Assert::AreEqual({ 0, 0, 0 }, data[3u]);
			}
			TEST_METHOD(ComponentData_accessConst)
			{
				ComponentData<glm::vec3> data;
				data[2u] = { 3, 1, 4 };
				data[0u] = { 0, 42, 1337 };
				data[3u] = { 1, 2, 3 };
				const auto & constData = data;

				Assert::AreEqual({ 0, 42, 1337 }, constData[0u]);
				Assert::ExpectException<std::invalid_argument>([&constData]() {constData[1u]; });
				Assert::AreEqual({ 3, 1, 4 }, constData[2u]);
				Assert::AreEqual({ 1, 2, 3 }, constData[3u]);
				Assert::ExpectException<std::invalid_argument>([&constData]() {constData[4u]; });
			}

			TEST_METHOD(ComponentData_has)
			{
				ComponentData<glm::vec3> dataA;
				ComponentData<glm::vec3> dataB;
				dataB[3u] = { 1, 2, 3 };

				Assert::IsFalse(dataA.has(0u));
				Assert::IsFalse(dataB.has(2u));
				Assert::IsTrue(dataB.has(3u));
				Assert::IsFalse(dataB.has(4u));
			}
		};
	}
}