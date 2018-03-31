
#include "CppUnitTest.h"

#include "logic/ecs/SystemRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace core
{
	class Engine {};
}

namespace logic
{
	namespace ecs
	{
		bool initializedA = false;
		int processedA = 0;
		int processedB = 0;

		class SystemMockA : public System<int, double>
		{
		public:
			virtual void initialize(core::Engine & engine) override final { initializedA = true; }
			virtual void process(const Time & t, const Time & dt) override final
			{
				processedA = 0;
				for (const auto & entity : *this)
					++processedA;
			}
		};
		class SystemMockB : public System<float>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override final
			{
				processedB = 0;
				for (const auto & entity : *this)
					++processedB;
			}
		};

		TEST_CLASS(SystemRegistryTest)
		{
		public:
			TEST_METHOD(SystemRegistry_addSystem)
			{
				core::Engine engine;
				SystemRegistry registry;
				registry.inject(engine);
				registry.addSystem<SystemMockA, SystemMockB>();

				Assert::IsTrue(initializedA);
			}

			TEST_METHOD(SystemRegistry_process)
			{
				SystemRegistry registry;
				registry.addSystem<SystemMockA, SystemMockB>();
				registry.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
				Assert::AreEqual(0, processedB);
			}

			TEST_METHOD(SystemRegistry_addEntity)
			{
				ComponentStorage storage;
				SystemRegistry registry;
				registry.inject(storage);
				registry.addSystem<SystemMockA, SystemMockB>();
				registry.addEntity(createEntity<int>(storage));
				registry.addEntity(createEntity<int, double>(storage));
				registry.addEntity(createEntity<int, float, double>(storage));
				registry.process(0.0_s, 0.05_s);

				Assert::AreEqual(2, processedA);
				Assert::AreEqual(1, processedB);
			}
			TEST_METHOD(SystemRegistry_removeEntity)
			{
				ComponentStorage storage;
				SystemRegistry registry;
				registry.inject(storage);
				registry.addSystem<SystemMockA, SystemMockB>();
				const auto entity = createEntity<float>(storage);
				registry.addEntity(entity);
				registry.removeEntity(entity);
				registry.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
				Assert::AreEqual(0, processedB);
			}

		private:
			template<typename ...Components>
			inline Entity createEntity(const ComponentStorage & storage)
			{
				return { m_uniqueId++, storage.getMask<Components...>() };
			}

			unsigned int m_uniqueId = 0u;
		};
	}
}