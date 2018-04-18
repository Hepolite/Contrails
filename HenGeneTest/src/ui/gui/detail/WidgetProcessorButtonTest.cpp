
#include "CppUnitTest.h"

#include "ui/gui/Gui.h"
#include "ui/gui/detail/WidgetProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetProcessorButtonTest)
		{
		public:
			TEST_METHOD(ProcessorButtonCheckbox_activate)
			{
				auto & widget = m_gui.getWidgets().create("widget");
				widget.m_activation.m_hovered = true;
				ProcessorButtonCheckbox processor{ m_gui.getWidgets(), widget };

				Assert::IsFalse(widget.m_state.m_bool);
				processor.onAction(m_gui.getScript());
				Assert::IsTrue(widget.m_state.m_bool);
				processor.onAction(m_gui.getScript());
				Assert::IsFalse(widget.m_state.m_bool);
			}

			TEST_METHOD(ProcessorButtonRadio_activate)
			{
				auto & widgetA = m_gui.getWidgets().create("widgetA");
				auto & widgetB = m_gui.getWidgets().create("widgetB");
				widgetA.m_activation.m_hovered = true;
				widgetB.m_activation.m_hovered = true;
				widgetA.m_group.m_leader = widgetB.m_group.m_leader = "widgetA";
				widgetA.m_group.m_members = { "widgetA", "widgetB" };
				ProcessorButtonRadio processorA{ m_gui.getWidgets(), widgetA };
				ProcessorButtonRadio processorB{ m_gui.getWidgets(), widgetB };

				Assert::IsFalse(widgetA.m_state.m_bool);
				Assert::IsFalse(widgetB.m_state.m_bool);
				processorA.onAction(m_gui.getScript());
				Assert::IsTrue(widgetA.m_state.m_bool);
				Assert::IsFalse(widgetB.m_state.m_bool);
				processorB.onAction(m_gui.getScript());
				Assert::IsFalse(widgetA.m_state.m_bool);
				Assert::IsTrue(widgetB.m_state.m_bool);
				processorA.onAction(m_gui.getScript());
				Assert::IsTrue(widgetA.m_state.m_bool);
				Assert::IsFalse(widgetB.m_state.m_bool);
			}

		private:
			Gui m_gui;
		};
	}
}