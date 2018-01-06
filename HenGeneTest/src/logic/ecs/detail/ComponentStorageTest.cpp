
#include "CppUnitTest.h"

#include "logic/ecs/detail/ComponentStorage.h"

#include <glm/vec3.hpp>
#include <string>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace ecs
	{
		TEST_CLASS(ComponentStorageTest)
		{
		public:
			TEST_METHOD(ComponentStorage_add)
			{
				ComponentStorage storage;
				storage.add<int>();

				Assert::IsTrue(storage.has<int>());
				Assert::IsFalse(storage.has<float>());
				Assert::ExpectException<std::invalid_argument>([&storage]() { storage.add<int>(); });
			}
			TEST_METHOD(ComponentStorage_has)
			{
				ComponentStorage storage;
				auto & dataA = storage.getData<glm::ivec3>();
				auto & dataB = storage.getData<std::string>();

				Assert::IsFalse(storage.has<std::vector<double>>());
				Assert::IsTrue(storage.has<glm::ivec3>());
				Assert::IsTrue(storage.has<std::string>());
			}

			TEST_METHOD(ComponentStorage_getId)
			{
				ComponentStorage storage;
				storage.add<int, float, glm::ivec3, std::string>();

				Assert::AreEqual(0u, storage.getId<int>());
				Assert::AreEqual(1u, storage.getId<float>());
				Assert::AreEqual(2u, storage.getId<glm::ivec3>());
				Assert::AreEqual(3u, storage.getId<std::string>());
				Assert::ExpectException<std::invalid_argument>([&storage]() { storage.getId<double>(); });
			}

			TEST_METHOD(ComponentStorage_get)
			{
				ComponentStorage storage;
				auto & dataC = storage.getData<std::vector<double>>();
				auto & dataA = storage.getData<glm::ivec3>();
				auto & dataB = storage.getData<std::string>();

				Assert::IsTrue(&dataA == &storage.getData<glm::ivec3>());
				Assert::IsTrue(&dataB == &storage.getData<std::string>());
				Assert::IsTrue(&dataC == &storage.getData<std::vector<double>>());
			}
			TEST_METHOD(ComponentStorage_getConst)
			{
				ComponentStorage storage;
				auto & dataA = storage.getData<glm::ivec3>();
				auto & dataB = storage.getData<std::string>();
				const auto & constStorage = storage;

				Assert::IsTrue(&dataA == &storage.getData<glm::ivec3>());
				Assert::IsTrue(&dataB == &storage.getData<std::string>());
				Assert::ExpectException<std::invalid_argument>([&constStorage]() { constStorage.getData<int>(); });
			}

			TEST_METHOD(ComponentStorage_getMask)
			{
				ComponentStorage storage;
				storage.add<int, double, glm::ivec3, std::string>();

				const auto idInt = storage.getId<int>();
				const auto idDouble = storage.getId<double>();
				const auto idVec3 = storage.getId<glm::ivec3>();
				const auto idString = storage.getId<std::string>();

				const auto componentsA = storage.getMask<int, glm::ivec3>();
				const auto componentsB = storage.getMask<std::string, glm::ivec3, int>();

				Assert::IsTrue(componentsA[idInt]);
				Assert::IsFalse(componentsA[idDouble]);
				Assert::IsTrue(componentsA[idVec3]);
				Assert::IsFalse(componentsA[idString]);

				Assert::IsTrue(componentsB[idInt]);
				Assert::IsFalse(componentsB[idDouble]);
				Assert::IsTrue(componentsB[idVec3]);
				Assert::IsTrue(componentsB[idString]);
			}
		};
	}
}