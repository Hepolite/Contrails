
#include "CppUnitTest.h"

#include "render/allegro/Font.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(FontTest)
		{
		public:
			FontTest() { initialize(); }
			~FontTest() { deinitialize(); }

			TEST_METHOD(Font_load)
			{
				Font fontA, fontB;
				Assert::IsTrue(fontA.load("font.ttf"));
				Assert::IsFalse(fontB.load("not_present.ttf"));
			}

		private:
			void initialize() { io::File{ "font.ttf" }.create(); }
			void deinitialize() { io::File{ "font.ttf" }.erase(); }

			setup::Context m_context;
		};
	}
}