
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
			TEST_METHOD(WidgetRenderer_getFrame)
			{
				Widget activeA, activeB, activeC;
				activeA.m_state.m_bool = activeB.m_state.m_bool = activeC.m_state.m_bool = true;
				activeB.m_activation.m_button = mouse::Button::LEFT;
				activeC.m_activation.m_locked = true;

				Widget inactiveA, inactiveB, inactiveC;
				inactiveB.m_activation.m_button = mouse::Button::LEFT;
				inactiveC.m_activation.m_locked = true;

				Assert::AreEqual({ "active" }, RendererButton{ activeA }.getFrame());
				Assert::AreEqual({ "active_clicked" }, RendererButton{ activeB }.getFrame());
				Assert::AreEqual({ "active_locked" }, RendererButton{ activeC }.getFrame());
				Assert::AreEqual({ "inactive" }, RendererButton{ inactiveA }.getFrame());
				Assert::AreEqual({ "inactive_clicked" }, RendererButton{ inactiveB }.getFrame());
				Assert::AreEqual({ "inactive_locked" }, RendererButton{ inactiveC }.getFrame());
			}
		};
	}
}