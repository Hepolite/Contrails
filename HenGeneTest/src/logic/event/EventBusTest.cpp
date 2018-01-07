
#include "CppUnitTest.h"

#include "logic/event/EventBus.h"

#include <hen/Unittest.h>
#include <memory>
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

				Assert::AreEqual(3, bus.post(0));
			}

			TEST_METHOD(EventBus_postLValue)
			{
				EventBus bus;
				using Event = std::unique_ptr<int>;
				const auto listenerA = bus.add<Event, Priority::EARLY>([](auto & event) { *event += 3; });
				const auto listenerB = bus.add<Event, Priority::LATE>([](auto & event) { *event /= 2; });

				auto event = std::make_unique<int>(-7);
				Assert::AreEqual(-2, *bus.post(event));
			}
			TEST_METHOD(EventBus_postRValue)
			{
				EventBus bus;
				using Event = std::unique_ptr<int>;
				const auto listenerA = bus.add<Event, Priority::EARLY>([](auto & event) { *event += 3; });
				const auto listenerB = bus.add<Event, Priority::LATE>([](auto & event) { *event /= 2; });

				Assert::AreEqual(-2, *bus.post(std::make_unique<int>(-7)));
			}
		};
	}
}