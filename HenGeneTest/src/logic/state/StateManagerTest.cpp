
#include "CppUnitTest.h"

#include "logic/state/StateManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace core
{
	class Engine {};
}

namespace logic
{
	namespace state
	{
		bool initialized = false;
		bool deinitialized = false;
		bool processed = false;

		class StateMockA : public State<StateMockA>
		{
		public:
			virtual void initialize(core::Engine & engine) override final { initialized = true; }
			virtual void deinitialize(core::Engine & engine) override final { deinitialized = true; }
			virtual void process(const Time & t, const Time & dt) override final { processed = true; }
		};
		class StateMockB : public State<StateMockB>
		{
		public:
			virtual void initialize(core::Engine & engine) override final {}
			virtual void deinitialize(core::Engine & engine) override final {}
			virtual void process(const Time & t, const Time & dt) override final {}
		};

		TEST_CLASS(StateManagerTest)
		{
		public:
			TEST_METHOD(StateManager_set)
			{
				StateManager manager;
				const auto handle = manager.set(std::make_shared<StateMockA>());

				Assert::IsTrue(manager.has(handle));
				Assert::ExpectException<std::invalid_argument>([&manager]() { manager.set(nullptr); });
			}
			TEST_METHOD(StateManager_add)
			{
				StateManager manager;
				const auto handleA = manager.add(std::make_shared<StateMockA>());
				const auto handleB = manager.add(std::make_shared<StateMockB>());

				Assert::IsTrue(manager.has(handleA));
				Assert::IsTrue(manager.has(handleB));
				Assert::ExpectException<std::invalid_argument>([&manager]() { manager.add(nullptr); });
				Assert::ExpectException<std::invalid_argument>([&manager]() { manager.add(std::make_shared<StateMockA>()); });
			}
			TEST_METHOD(StateManager_remove)
			{
				StateManager manager;
				const auto handleA = manager.add(std::make_shared<StateMockA>());
				const auto handleB = manager.add(std::make_shared<StateMockB>());

				Assert::IsTrue(manager.remove(handleA));
				Assert::IsFalse(manager.remove(handleA));
				Assert::IsFalse(manager.has(handleA));
				Assert::IsTrue(manager.has(handleB));
			}
			TEST_METHOD(StateManager_clear)
			{
				StateManager manager;
				const auto handleA = manager.add(std::make_shared<StateMockA>());
				const auto handleB = manager.add(std::make_shared<StateMockB>());
				manager.clear();

				Assert::IsFalse(manager.has(handleA));
				Assert::IsFalse(manager.has(handleB));
			}

			TEST_METHOD(StateManager_initialize)
			{
				core::Engine engine;
				StateManager manager;
				manager.inject(engine);

				manager.add(std::make_shared<StateMockA>());
				manager.process(0.0_s, 0.05_s);

				Assert::IsTrue(initialized);
			}
			TEST_METHOD(StateManager_deinitialize)
			{
				core::Engine engine;
				StateManager manager;
				manager.inject(engine);

				manager.remove(manager.add(std::make_shared<StateMockA>()));
				manager.process(0.0_s, 0.05_s);

				Assert::IsTrue(deinitialized);
			}
			TEST_METHOD(StateManager_process)
			{
				core::Engine engine;
				StateManager manager;
				manager.inject(engine);

				manager.add(std::make_shared<StateMockA>());
				manager.process(0.0_s, 0.05_s);

				Assert::IsTrue(processed);
			}
		};
	}
}