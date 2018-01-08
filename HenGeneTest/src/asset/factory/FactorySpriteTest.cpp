
#include "CppUnitTest.h"

#include "asset/factory/FactorySprite.h"
#include "render/allegro/Allegro.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	namespace util
	{
		TEST_CLASS(LoaderSpriteTest)
		{
		public:
			TEST_METHOD(LoaderSprite_load)
			{
				render::allegro::Sprite sprite;
				LoaderSprite{}.load(sprite, "sprite.xml");


			}

		private:
			void initialize() const
			{
				io::File{ "sprite.xml" }.write("");
			}
			void deinitialize() const
			{
				io::File{ "sprite.xml" }.erase();
			}
			
			render::allegro::Allegro m_allegro;
		};

		TEST_CLASS(BuilderSpriteTest)
		{
		public:
			TEST_METHOD(BuilderSprite_build)
			{
				render::allegro::Sprite sprite;
				BuilderSprite{}.build(sprite, 32u, 32u);

				Assert::IsNotNull(sprite.getHandle());
			}

		private:
			render::allegro::Allegro m_allegro;
		};
	}
}