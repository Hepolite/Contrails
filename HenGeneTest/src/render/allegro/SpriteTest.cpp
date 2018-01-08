
#include "CppUnitTest.h"

#include "render/allegro/Allegro.h"
#include "render/allegro/Sprite.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(SpriteTest)
		{
		public:
			TEST_METHOD(Sprite_create)
			{
				Sprite sprite;
				sprite.create(32u, 32u);

				Assert::IsNotNull(sprite.getHandle());
			}
			TEST_METHOD(Sprite_release)
			{
				Sprite sprite;
				sprite.create(32u, 32u);
				sprite.release();

				Assert::IsNull(sprite.getHandle());
			}

		private:
			Allegro m_allegro;
		};
	}
}