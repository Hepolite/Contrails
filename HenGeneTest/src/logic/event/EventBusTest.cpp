
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"

#include <hen/Unittest.h>
#include <std/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace event
	{
		TEST_CLASS(EventBusTest)
		{
		public:
			TEST_METHOD(EventBus_add)
			{
				EventBus bus;

				const auto listenerA = bus.add<float, Priority::EARLY>([](auto& event) {});
				const auto listenerB = bus.add<int>([](auto& event) {});

				Assert::AreEqual({ typeid(float) }, listenerA.m_identifier);
				Assert::AreEqual(Priority::EARLY, listenerA.m_priority);
				Assert::AreEqual(0u, listenerA.m_id);

				Assert::AreEqual({ typeid(int) }, listenerB.m_identifier);
				Assert::AreEqual(Priority::MONITOR, listenerB.m_priority);
				Assert::AreEqual(1u, listenerB.m_id);
			}
			TEST_METHOD(EventBus_remove)
			{
				EventBus bus;
				const auto listenerA = bus.add<int, Priority::EARLY>([](auto& event) { event = 3; });
				const auto listenerB = bus.add<int, Priority::LATE>([](auto& event) { event = 7; });

				bus.remove(listenerB);

				int event = 0;
				bus.post(event);

				Assert::AreEqual(3, event);
			}

			TEST_METHOD(EventBus_post)
			{
				EventBus bus;
				bus.add<int, Priority::EARLY>([](auto& event) { event += 3; });
				bus.add<int, Priority::LATE>([](auto& event) { event /= 2; });

				int event = -7;
				bus.post(event);

				Assert::AreEqual(-2, event);
			}
		};
	}
}