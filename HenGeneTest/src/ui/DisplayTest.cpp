
#include "CppUnitTest.h"

#include "core/allegro/Allegro.h"
#include "ui/Display.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ui
{
	TEST_CLASS(DisplayTest)
	{
	public:
		TEST_METHOD(Display_ctor)
		{
			Display display{ { 640, 480 }, false };

			Assert::IsNotNull(display.getHandle());
			Assert::AreEqual({ 640, 480 }, display.getSize());
			Assert::AreEqual(false, display.isFullscreen());
		}

	private:
		core::allegro::Allegro m_allegro;
	};
}