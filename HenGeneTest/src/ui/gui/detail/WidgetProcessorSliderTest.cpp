
#include "CppUnitTest.h"

#include "ui/gui/Gui.h"
#include "ui/gui/detail/WidgetProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetProcessorSliderTest)
		{
		public:
			TEST_METHOD(ProcessorSlider_slide)
			{
				auto & widget = m_gui.getWidgets().create("widget");
				widget.m_size.m_minSize.x = 40.0f;
				widget.m_activation.m_mousePosition.x = 10.0f;
				widget.m_activation.m_button = mouse::Button::LEFT;
				ProcessorSlider processor{ m_gui.getWidgets(), widget };

				Assert::AreEqual(0.0f, widget.m_state.m_float);
				processor.onProcess({ 0.0f, 0.0f });
				Assert::AreEqual(0.25f, widget.m_state.m_float);
			}

		private:
			Gui m_gui;
		};
	}
}