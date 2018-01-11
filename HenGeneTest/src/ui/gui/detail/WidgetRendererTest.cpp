
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
				Widget activeA, activeB, activeC, activeD;
				activeA.m_state.m_bool = activeB.m_state.m_bool = activeC.m_state.m_bool = activeD.m_state.m_bool = true;
				activeB.m_activation.m_hovered = true;;
				activeC.m_activation.m_button = mouse::Button::LEFT;
				activeD.m_activation.m_locked = true;

				Widget inactiveA, inactiveB, inactiveC, inactiveD;
				inactiveB.m_activation.m_hovered = true;;
				inactiveC.m_activation.m_button = mouse::Button::LEFT;
				inactiveD.m_activation.m_locked = true;

				Assert::AreEqual({ "active" }, RendererButton{ activeA }.getFrame());
				Assert::AreEqual({ "active_hovered" }, RendererButton{ activeB }.getFrame());
				Assert::AreEqual({ "active_clicked" }, RendererButton{ activeC }.getFrame());
				Assert::AreEqual({ "active_locked" }, RendererButton{ activeD }.getFrame());
				Assert::AreEqual({ "inactive" }, RendererButton{ inactiveA }.getFrame());
				Assert::AreEqual({ "inactive_hovered" }, RendererButton{ inactiveB }.getFrame());
				Assert::AreEqual({ "inactive_clicked" }, RendererButton{ inactiveC }.getFrame());
				Assert::AreEqual({ "inactive_locked" }, RendererButton{ inactiveD }.getFrame());
			}
		};
	}
}