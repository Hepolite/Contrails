
#include "CppUnitTest.h"

#include "ui/gui/detail/Widgets.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(WidgetsTest)
		{
		public:
			TEST_METHOD(Widgets_create)
			{
				Widgets widgets;
				Widget & widget = widgets.create("widget");
				Widget & child = widgets.create("child", "widget");

				Assert::AreEqual({ "widget" }, widget.m_header.m_name);
				Assert::AreEqual({ "" }, widget.m_family.m_parent);
				Assert::AreEqual(1u, widget.m_family.m_children.size());
				Assert::IsFalse(widget.m_family.m_children.find("child") == widget.m_family.m_children.end());

				Assert::AreEqual({ "child" }, child.m_header.m_name);
				Assert::AreEqual({ "widget" }, child.m_family.m_parent);
				Assert::AreEqual(0u, child.m_family.m_children.size());

				Assert::ExpectException<std::invalid_argument>([&widgets]() {widgets.create("widget"); });
				Assert::ExpectException<std::invalid_argument>([&widgets]() {widgets.create("validname", "invalidparent"); });
			}

			TEST_METHOD(Widgets_has)
			{
				Widgets widgets;
				widgets.create("widgetA");

				Assert::IsTrue(widgets.has("widgetA"));
				Assert::IsFalse(widgets.has("widgetB"));
			}

			TEST_METHOD(Widgets_get)
			{
				Widgets widgets;
				widgets.create("widgetA");
				const Widgets & widgetsConst = widgets;

				widgets.get("widgetA");
				widgetsConst.get("widgetA");
				Assert::ExpectException<std::invalid_argument>([&widgets]() { widgets.get("widgetB"); });
				Assert::ExpectException<std::invalid_argument>([&widgetsConst]() { widgetsConst.get("widgetB"); });
			}
		};
	}
}