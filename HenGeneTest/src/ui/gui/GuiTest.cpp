
#include "CppUnitTest.h"

#include "ui/gui/Gui.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(GuiTest)
		{
		public:
			TEST_METHOD(Gui_mouseHoverWidget)
			{
				Gui gui;
				auto & widgetA = create(gui, "widgetA", { 0.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetB = create(gui, "widgetB", { 10.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetC = create(gui, "widgetC", { 20.0f, 0.0f }, { 10.0f, 10.0f });
				widgetB.m_render.m_visible = false;
				widgetC.m_activation.m_locked = true;

				Assert::IsFalse(simulateMouseMove(gui, { 35.0f, 27.0f }));

				Assert::IsTrue(simulateMouseMove(gui, { 5.0f, 7.0f }));
				Assert::IsTrue(widgetA.m_activation.m_hovered);
				Assert::IsFalse(simulateMouseMove(gui, { 15.0f, 3.0f }));
				Assert::IsFalse(widgetB.m_activation.m_hovered);
				Assert::IsTrue(simulateMouseMove(gui, { 25.0f, 4.0f }));
				Assert::IsTrue(widgetC.m_activation.m_hovered);
			}
			TEST_METHOD(Gui_mouseHoverWidgetOverlap)
			{
				Gui gui;
				auto & widgetA = create(gui, "widgetA", { 0.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetB = create(gui, "widgetB", "widgetA", { 0.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetC = create(gui, "widgetC", { 10.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetD = create(gui, "widgetD", "widgetC", { 0.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetE = create(gui, "widgetE", { 15.0f, 0.0f }, { 10.0f, 10.0f });
				widgetC.m_render.m_visible = false;

				simulateMouseMove(gui, { 5.0f, 7.0f });
				Assert::IsFalse(widgetA.m_activation.m_hovered);
				Assert::IsTrue(widgetB.m_activation.m_hovered);

				simulateMouseMove(gui, { 17.0f, 6.0f });
				Assert::IsFalse(widgetC.m_activation.m_hovered);
				Assert::IsFalse(widgetD.m_activation.m_hovered);
				Assert::IsTrue(widgetE.m_activation.m_hovered);
			}

			TEST_METHOD(Gui_mousePressWidget)
			{
				Gui gui;
				auto & widgetA = create(gui, "widgetA", { 0.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetB = create(gui, "widgetB", { 10.0f, 0.0f }, { 10.0f, 10.0f });
				auto & widgetC = create(gui, "widgetC", { 20.0f, 0.0f }, { 10.0f, 10.0f });
				widgetB.m_render.m_visible = false;
				widgetC.m_activation.m_locked = true;

				simulateMouseMove(gui, { 35.0f, 27.0f });
				Assert::IsFalse(simulateMousePress(gui, ui::mouse::Button::LEFT));

				simulateMouseMove(gui, { 5.0f, 7.0f });
				Assert::IsTrue(simulateMousePress(gui, ui::mouse::Button::LEFT));
				Assert::IsTrue(widgetA.m_activation.m_button == ui::mouse::Button::LEFT);
				
				simulateMouseMove(gui, { 15.0f, 3.0f });
				Assert::IsFalse(simulateMousePress(gui, ui::mouse::Button::LEFT));
				Assert::IsTrue(widgetB.m_activation.m_button == ui::mouse::Button::NONE);
				
				simulateMouseMove(gui, { 25.0f, 4.0f });
				Assert::IsTrue(simulateMousePress(gui, ui::mouse::Button::LEFT));
				Assert::IsTrue(widgetC.m_activation.m_button == ui::mouse::Button::NONE);
			}
			TEST_METHOD(Gui_mouseReleaseWidget)
			{
				Gui gui;
				bool A = false, B = false, C = false;
				auto & widgetA = create(gui, "widgetA", { 0.0f, 0.0f }, { 10.0f, 10.0f }, [&A](auto &) { A = true; });
				auto & widgetB = create(gui, "widgetB", { 10.0f, 0.0f }, { 10.0f, 10.0f }, [&B](auto &) { B = true; });
				auto & widgetC = create(gui, "widgetC", { 20.0f, 0.0f }, { 10.0f, 10.0f }, [&C](auto &) { C = true; });
				widgetB.m_render.m_visible = false;
				widgetC.m_activation.m_locked = true;

				simulateMouseMove(gui, { 5.0f, 7.0f });
				simulateMousePress(gui, ui::mouse::Button::LEFT);
				simulateMouseRelease(gui, ui::mouse::Button::LEFT);
				Assert::IsTrue(A);

				simulateMouseMove(gui, { 15.0f, 3.0f });
				simulateMousePress(gui, ui::mouse::Button::LEFT);
				simulateMouseRelease(gui, ui::mouse::Button::LEFT);
				Assert::IsFalse(B);

				simulateMouseMove(gui, { 25.0f, 4.0f });
				simulateMousePress(gui, ui::mouse::Button::LEFT);
				simulateMouseRelease(gui, ui::mouse::Button::LEFT);
				Assert::IsFalse(C);
			}

		private:
			Widget & create(
				Gui & gui,
				const std::string & name,
				const glm::vec2 & pos,
				const glm::vec2 & size,
				const std::function<void(const logic::script::Script &)> & action = [](auto &) {}
			) {
				return create(gui, name, "", pos, size, action);
			}
			Widget & create(
				Gui & gui,
				const std::string & name,
				const std::string & parent,
				const glm::vec2 & pos,
				const glm::vec2 & size,
				const std::function<void(const logic::script::Script &)> & action = [](auto &) {}
			) {
				auto & widget = gui.getWidgets().create(name, parent);
				widget.m_position.m_pos = pos;
				widget.m_size.m_size = size;
				widget.m_logic.m_action = action;
				return widget;
			}

			bool simulateMouseMove(Gui & gui, const glm::vec2 & pos)
			{
				m_mousepos = pos;
				return gui.onEvent(logic::event::MouseMove{ m_mousepos, {}, {}, {} });
			}
			bool simulateMousePress(Gui & gui, ui::mouse::Button button)
			{
				return gui.onEvent(logic::event::MousePress{ button, 0.0f, m_mousepos, {} });
			}
			void simulateMouseRelease(Gui & gui, ui::mouse::Button button)
			{
				return gui.onEvent(logic::event::MouseRelease{ button, 0.0f, m_mousepos, {} });
			}

			glm::vec2 m_mousepos{};
		};
	}
}