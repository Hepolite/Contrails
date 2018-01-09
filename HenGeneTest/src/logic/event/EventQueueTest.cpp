
#include "CppUnitTest.h"

#include "logic/event/EventQueue.h"
#include "Setup.h"
#include "ui/Display.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace event
	{
		TEST_CLASS(EventQueueTest)
		{
		public:
			TEST_METHOD(EventQueue_add)
			{
				EventQueue queue;

				const auto source = al_get_display_event_source(m_context.m_display->getHandle());
				Assert::IsTrue(queue.add(source));
				Assert::IsFalse(queue.add(source));
				Assert::IsFalse(queue.add(nullptr));
			}
			TEST_METHOD(EventQueue_remove)
			{
				EventQueue queue;

				const auto source = al_get_display_event_source(m_context.m_display->getHandle());
				queue.add(source);

				Assert::IsTrue(queue.remove(source));
				Assert::IsFalse(queue.remove(source));
				Assert::IsFalse(queue.remove(nullptr));
			}

			TEST_METHOD(EventQueue_update)
			{
				EventBus bus;
				EventQueue queue;

				queue.update(bus);
			}

		private:
			setup::Context m_context;
		};
	}
}