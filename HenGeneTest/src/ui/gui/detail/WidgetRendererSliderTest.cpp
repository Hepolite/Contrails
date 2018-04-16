
#include "CppUnitTest.h"

#include "ui/gui/detail/WidgetRenderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetRendererSliderTest)
		{
		public:
			TEST_METHOD(RendererSlider_getFrame)
			{
				Widget widgetA, widgetB, widgetC, widgetD;
				widgetB.m_activation.m_hovered = true;
				widgetC.m_activation.m_button = mouse::Button::LEFT;
				widgetD.m_activation.m_locked = true;

				Assert::AreEqual({ "bar_left" }, RendererSlider{ widgetA }.getFrame(RendererSlider::Component::BAR_LEFT));
				Assert::AreEqual({ "bar_middle" }, RendererSlider{ widgetA }.getFrame(RendererSlider::Component::BAR_MIDDLE));
				Assert::AreEqual({ "bar_right" }, RendererSlider{ widgetA }.getFrame(RendererSlider::Component::BAR_RIGHT));
				Assert::AreEqual({ "marker" }, RendererSlider{ widgetA }.getFrame(RendererSlider::Component::MARKER));
				Assert::AreEqual({ "bar_left_hovered" }, RendererSlider{ widgetB }.getFrame(RendererSlider::Component::BAR_LEFT));
				Assert::AreEqual({ "bar_middle_hovered" }, RendererSlider{ widgetB }.getFrame(RendererSlider::Component::BAR_MIDDLE));
				Assert::AreEqual({ "bar_right_hovered" }, RendererSlider{ widgetB }.getFrame(RendererSlider::Component::BAR_RIGHT));
				Assert::AreEqual({ "marker_hovered" }, RendererSlider{ widgetB }.getFrame(RendererSlider::Component::MARKER));
				Assert::AreEqual({ "bar_left_clicked" }, RendererSlider{ widgetC }.getFrame(RendererSlider::Component::BAR_LEFT));
				Assert::AreEqual({ "bar_middle_clicked" }, RendererSlider{ widgetC }.getFrame(RendererSlider::Component::BAR_MIDDLE));
				Assert::AreEqual({ "bar_right_clicked" }, RendererSlider{ widgetC }.getFrame(RendererSlider::Component::BAR_RIGHT));
				Assert::AreEqual({ "marker_clicked" }, RendererSlider{ widgetC }.getFrame(RendererSlider::Component::MARKER));
				Assert::AreEqual({ "bar_left_locked" }, RendererSlider{ widgetD }.getFrame(RendererSlider::Component::BAR_LEFT));
				Assert::AreEqual({ "bar_middle_locked" }, RendererSlider{ widgetD }.getFrame(RendererSlider::Component::BAR_MIDDLE));
				Assert::AreEqual({ "bar_right_locked" }, RendererSlider{ widgetD }.getFrame(RendererSlider::Component::BAR_RIGHT));
				Assert::AreEqual({ "marker_locked" }, RendererSlider{ widgetD }.getFrame(RendererSlider::Component::MARKER));
			}
		};
	}
}