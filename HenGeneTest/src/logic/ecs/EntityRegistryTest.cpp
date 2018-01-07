
#include "CppUnitTest.h"

#include "logic/ecs/EntityRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace ecs
	{
		TEST_CLASS(EntityRegistryTest)
		{
		public:
			TEST_METHOD(EntityRegistry_has)
			{
				EntityRegistry registry;
				registry.createEntity();

				Assert::IsTrue(registry.hasEntity(0u));
				Assert::IsFalse(registry.hasEntity(1u));
			}

			TEST_METHOD(EntityRegistry_createEntity)
			{
				EntityRegistry registry;

				Assert::AreEqual(0u, registry.createEntity());
				Assert::AreEqual(1u, registry.createEntity());
				Assert::AreEqual(2u, registry.createEntity());
			}
			TEST_METHOD(EntityRegistry_createAfterDelete)
			{
				EntityRegistry registry;
				for (unsigned int i = 0u; i < 10u; ++i)
					registry.createEntity();
				registry.deleteEntity(2u);
				registry.deleteEntity(7u);
				registry.deleteEntity(5u);
				registry.deleteEntity(3u);

				Assert::AreEqual(2u, registry.createEntity());
				Assert::AreEqual(3u, registry.createEntity());
				Assert::AreEqual(5u, registry.createEntity());
				Assert::AreEqual(7u, registry.createEntity());
				Assert::AreEqual(10u, registry.createEntity());

				unsigned int index = 0u;
				for (const auto & entity : registry.getEntities())
					Assert::AreEqual(index++, entity.m_id);
			}

			TEST_METHOD(EntityRegistry_deleteEntity)
			{
				EntityRegistry registry;
				for (unsigned int i = 0u; i < 10u; ++i)
					registry.createEntity();

				Assert::IsTrue(registry.deleteEntity(4u));
				Assert::IsFalse(registry.deleteEntity(4u));
				Assert::IsTrue(registry.deleteEntity(5u));
				Assert::IsFalse(registry.deleteEntity(5u));
				Assert::IsTrue(registry.deleteEntity(3u));
				Assert::IsFalse(registry.deleteEntity(3u));
			}

			TEST_METHOD(EntityRegistry_clear)
			{
				EntityRegistry registry;
				for (unsigned int i = 0u; i < 10u; ++i)
					registry.createEntity();
				registry.clear();

				for (unsigned int i = 0u; i < 10u; ++i)
					Assert::IsFalse(registry.hasEntity(i));
				Assert::AreEqual(0u, registry.createEntity());
			}

			TEST_METHOD(EntityRegistry_attachComponent)
			{
				ComponentStorage storage;
				storage.add<int, float>();

				EntityRegistry registry;
				registry.inject(storage);
				registry.createEntity();
				registry.attachComponent<int, float>(0u);

				Assert::IsTrue(storage.getMask<int, float>() == registry.getEntity(0u).m_mask);
				Assert::IsTrue(storage.getData<int>().has(0u));
				Assert::IsTrue(storage.getData<float>().has(0u));
			}
			TEST_METHOD(EntityRegistry_detachComponent)
			{
				ComponentStorage storage;
				storage.add<int, float>();

				EntityRegistry registry;
				registry.inject(storage);
				registry.createEntity();
				registry.attachComponent<int, float>(0u);
				registry.detachComponent<int>(0u);

				Assert::IsTrue(storage.getMask<float>() == registry.getEntity(0u).m_mask);
				Assert::IsFalse(storage.getData<int>().has(0u));
				Assert::IsTrue(storage.getData<float>().has(0u));
			}
		};
	}
}