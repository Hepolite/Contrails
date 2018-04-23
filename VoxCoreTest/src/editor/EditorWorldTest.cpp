
#include "CppUnitTest.h"

#include "editor/EditorWorld.h"

#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	TEST_CLASS(EditorWorldTest)
	{
	public:
		TEST_METHOD(EditorWorld_init)
		{
			ui::gui::Gui gui;
			EditorWorld editor;
			editor.inject(gui);
			Assert::IsTrue(gui.getScript().execute("GET_EDITOR_WORLD()"));
		}

	private:
		setup::Context m_context;
	};
}