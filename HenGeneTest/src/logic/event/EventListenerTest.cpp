
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
			TEST_METHOD(EventListener_dtor)
			{
				bool received = false;
				EventBus bus;

				{ Listener listener = bus.add<bool>([&received](auto &) { received = true; }); }

				bus.post(false);
				Assert::IsFalse(received);
			}
		};
	}
}