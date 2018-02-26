
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"
#include "logic/event/EventListener.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace event
	{
		TEST_CLASS(EventListenerTest)
		{
		public:
			TEST_METHOD(EventListener_ctor)
			{
				EventBus bus;
				Listener listener = bus.add<bool, Priority::MIDDLE>([](auto & event) { event = true; });

				Assert::IsTrue(bus.post(false));
			}
			TEST_METHOD(EventListener_dtor)
			{
				EventBus bus;
				{ Listener listener = bus.add<bool, Priority::MIDDLE>([](auto & event) { event = true; }); }

				Assert::IsFalse(bus.post(false));
			}

			TEST_METHOD(EventListener_assign)
			{
				EventBus bus;
				Listener listener;
				listener = bus.add<bool, Priority::MIDDLE>([](auto & event) { event = true; });
				
				Assert::IsTrue(bus.post(false));
			}
			TEST_METHOD(EventListener_move)
			{
				EventBus bus;
				Listener listenerA, listenerB;
				listenerA = bus.add<int, Priority::LATE>([](auto & event) { event = 1; });
				listenerB = bus.add<int, Priority::LAST>([](auto & event) { event = 2; });

				listenerB = std::move(listenerA);
				Assert::AreEqual(1, bus.post(0));
			}
		};
	}
}