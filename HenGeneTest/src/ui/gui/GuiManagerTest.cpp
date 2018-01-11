
#include "CppUnitTest.h"

#include "ui/gui/GuiManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	namespace gui
	{
		TEST_CLASS(GuiManagerTest)
		{
		public:
			GuiManagerTest() { initialize(); }
			~GuiManagerTest() { deinitialize(); }

			TEST_METHOD(GuiManager_open)
			{
				GuiManager manager;

				Assert::IsTrue(manager.open("gui.xml"));
				Assert::IsFalse(manager.open("gui.xml"));
				Assert::IsFalse(manager.open("invalid.xml"));
			}
			TEST_METHOD(GuiManager_close)
			{
				GuiManager manager;
				manager.open("gui.xml");

				Assert::IsTrue(manager.close("gui.xml"));
				Assert::IsFalse(manager.close("gui.xml"));
				Assert::IsFalse(manager.close("invalid.xml"));
			}

		private:
			void initialize()
			{
				io::File{ "gui.xml" }.write("");
			}
			void deinitialize()
			{
				io::File{ "gui.xml" }.erase();
			}
		};
	}
}