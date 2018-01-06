
#include "CppUnitTest.h"

#include "logic/ecs/detail/ComponentStorage.h"
#include "logic/ecs/System.h"

#include <glm/vec3.hpp>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace ecs
	{
		class SystemMockA : public System<int, double>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final {}
		};

		class SystemMockB : public System<glm::ivec3, std::string>
		{
		public:
			virtual void process(const Time & t, const Time & dt) const override final {}
		};

		TEST_CLASS(SystemBaseTest)
		{
		public:
			TEST_METHOD(SystemBase_has)
			{
				ComponentStorage storage;
				storage.add<int, double>();
				const auto entityA = createEntity<int, double>(storage);
				const auto entityB = createEntity<int, double>(storage);

				SystemMockA system;
				system.assignMask(storage);
				system.add(entityA);

				Assert::IsTrue(system.has(entityA));
				Assert::IsFalse(system.has(entityB));
			}

			TEST_METHOD(SystemBase_add)
			{
				ComponentStorage storage;
				storage.add<int, float, double>();
				const auto entityA = createEntity<int>(storage);
				const auto entityB = createEntity<int, double>(storage);
				const auto entityC = createEntity<int, float, double>(storage);

				SystemMockA system;
				system.assignMask(storage);

				Assert::IsFalse(system.add(entityA));
				Assert::IsTrue(system.add(entityC));
				Assert::IsFalse(system.add(entityC));
				Assert::IsTrue(system.add(entityB));
				Assert::IsFalse(system.add(entityB));
			}
			TEST_METHOD(SystemBase_remove)
			{
				ComponentStorage storage;
				storage.add<int, double>();
				const auto entityA = createEntity<int, double>(storage);
				const auto entityB = createEntity<int, double>(storage);

				SystemMockA system;
				system.assignMask(storage);
				system.add(entityA);

				Assert::IsTrue(system.remove(entityA));
				Assert::IsFalse(system.remove(entityA));
				Assert::IsFalse(system.remove(entityB));
			}

		private:
			template<typename ...Components>
			inline Entity createEntity(ComponentStorage & storage)
			{
				return { m_uniqueId++, storage.getMask<Components...>() };
			}

			unsigned int m_uniqueId = 0u;
		};

		TEST_CLASS(SystemTest)
		{
		public:
			TEST_METHOD(System_getComponents)
			{
				ComponentStorage storage;
				storage.add<int, double, glm::ivec3, std::string>();
				const auto maskA = storage.getMask<int, double>();
				const auto maskB = storage.getMask<glm::ivec3, std::string>();

				SystemMockA systemA;
				SystemMockB systemB;
				systemA.assignMask(storage);
				systemB.assignMask(storage);

				Assert::IsTrue(maskA == systemA.getMask());
				Assert::IsTrue(maskB == systemB.getMask());
			}
		};
	}
}