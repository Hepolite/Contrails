
#include "CppUnitTest.h"

#include "ui/Display.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	TEST_CLASS(DisplayTest)
	{
	public:
		TEST_METHOD(Display_check)
		{
			Assert::IsNotNull(m_context.m_display->getHandle());
			Assert::AreEqual({ 640, 480 }, m_context.m_display->getSize());
			Assert::AreEqual(false, m_context.m_display->isFullscreen());
		}

	private:
		setup::Context m_context;
	};
}