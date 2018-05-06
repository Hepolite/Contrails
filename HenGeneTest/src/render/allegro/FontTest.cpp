
#include "CppUnitTest.h"

#include "asset/builtin/Font.h"
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

			TEST_METHOD(Font_get)
			{
				Font fontA, fontB;
				fontA.load("font.ttf");

				const auto * handleA = fontA.get(12u);
				const auto * handleB = fontA.get(18u);
				Assert::IsNull(fontB.get(12u));

				Assert::IsNotNull(handleA);
				Assert::IsNotNull(handleB);
				Assert::IsTrue(handleA != handleB);
			}

		private:
			void initialize() { io::File{ "font.ttf" }.writeDangerous(asset::builtin::BUILTIN_FONT_DATA, asset::builtin::BUILTIN_FONT_SIZE); }
			void deinitialize() { io::File{ "font.ttf" }.erase(); }

			setup::Context m_context;
		};
	}
}