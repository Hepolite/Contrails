
#include "CppUnitTest.h"

#include "editor/util/Cursor.h"
#include "logic/event/Events.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(CursorTest)
		{
		public:
			TEST_METHOD(Cursor_setPos)
			{
				Cursor cursor;
				cursor.setPos({ 3.14f, 42.0f, -0.6f });

				Assert::AreEqual({ 3.14f, 42.0f, -0.6f }, cursor.getActualPos());
			}
			TEST_METHOD(Cursor_getPos)
			{
				logic::event::EventBus bus;
				Cursor cursor;
				cursor.inject(bus);

				cursor.lockAxisX(true);
				cursor.setPos({ 1.0f, 0.5f, 3.0f });
				bus.post<logic::event::MousePress>({ ui::mouse::Button::LEFT, 0.0f, {}, {} });
				bus.post<logic::event::MouseMove>({ { 5.0f, 42.0f }, {}, {}, {} });
				cursor.setPos({ 2.0f, 3.0f, 4.0f });

				Assert::AreEqual({ 1.0f, 3.0f, 4.0f }, cursor.getPos());
				Assert::AreEqual({ 2.0f, 3.0f, 4.0f }, cursor.getActualPos());
				Assert::AreEqual({ 1.0f, 0.5f, 3.0f }, cursor.getClickedPos());
				Assert::AreEqual({ 5.0f, 42.0f }, cursor.getMousePos());
			}

			TEST_METHOD(Cursor_lockAxis)
			{
				Cursor cursor;

				Assert::IsFalse(cursor.isAxisXLocked());
				cursor.lockAxisX(true);
				Assert::IsTrue(cursor.isAxisXLocked());

				Assert::IsFalse(cursor.isAxisYLocked());
				cursor.lockAxisY(true);
				Assert::IsTrue(cursor.isAxisYLocked());

				Assert::IsFalse(cursor.isAxisZLocked());
				cursor.lockAxisZ(true);
				Assert::IsTrue(cursor.isAxisZLocked());
			}
		};
	}
}