
#include "CppUnitTest.h"

#include "ui/gui/detail/GuiLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(GuiLoaderTest)
		{
		public:
			GuiLoaderTest() { initialize(); }

			TEST_METHOD(GuiLoader_loadScript)
			{
				Gui gui;
				GuiLoader{ gui }.loadScript(m_doc.child("script"));

				Assert::IsTrue(gui.getScript().execute("foo()"));
				Assert::IsFalse(gui.getScript().execute("bar()"));
			}
			TEST_METHOD(GuiLoader_loadLayout)
			{
				Gui gui;
				GuiLoader{ gui }.loadLayout(m_doc.child("layout"));

				Assert::IsTrue(gui.getWidgets().has("widgetA"));
				Assert::IsTrue(gui.getWidgets().has("widgetB"));
				Assert::IsTrue(gui.getWidgets().has("widgetC"));
			}

		private:
			void initialize()
			{
				auto script = m_doc.append_child("script");
				script.append_child(pugi::node_pcdata).set_value("def foo() { return 3 + 5; }");
				
				auto layout = m_doc.append_child("layout");
				layout.append_child("widget").append_attribute("name").set_value("widgetA");
				layout.append_child("widget").append_attribute("name").set_value("widgetB");
				layout.append_child("widget").append_attribute("name").set_value("widgetC");
			}

			pugi::xml_document m_doc;
		};
	}
}