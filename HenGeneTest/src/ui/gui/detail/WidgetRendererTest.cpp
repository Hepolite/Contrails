
#include "CppUnitTest.h"

#include "ui/gui/detail/WidgetRenderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetRendererTest)
		{
		public:
			TEST_METHOD(Renderer_getFrame)
			{
				Widget widgetA, widgetB, widgetC, widgetD;
				widgetB.m_activation.m_hovered = true;
				widgetC.m_activation.m_button = mouse::Button::LEFT;
				widgetD.m_activation.m_locked = true;

				Assert::AreEqual({ "name" }, Renderer{ widgetA }.getFrame("name"));
				Assert::AreEqual({ "name_hovered" }, Renderer{ widgetB }.getFrame("name"));
				Assert::AreEqual({ "name_clicked" }, Renderer{ widgetC }.getFrame("name"));
				Assert::AreEqual({ "name_locked" }, Renderer{ widgetD }.getFrame("name"));
			}
		};
	}
}