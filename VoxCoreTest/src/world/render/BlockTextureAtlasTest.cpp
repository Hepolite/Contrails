
#include "CppUnitTest.h"

#include "world/render/BlockTextureAtlas.h"
#include "Setup.h"

#include <allegro5/bitmap.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(BlockTextureAtlasTest)
		{
		public:
			BlockTextureAtlasTest() { setup(); }
			~BlockTextureAtlasTest() { cleanup(); }

			TEST_METHOD(BlockTextureAtlas_attach)
			{
				BlockTextureAtlas atlas;
				const auto handleA = atlas.attach(m_bitmapA);
				const auto handleB = atlas.attach(m_bitmapB);
				const auto handleC = atlas.attach(m_bitmapC);

				Assert::AreNotEqual(handleA, handleB);
				Assert::AreEqual(0u, handleC);
			}

			TEST_METHOD(BlockTextureAtlas_build)
			{
				BlockTextureAtlas atlas;
				atlas.attach(m_bitmapA);

				Assert::IsTrue(atlas.build());
				Assert::IsFalse(atlas.build());
				Assert::AreEqual(0u, atlas.attach(m_bitmapB));
			}

		private:
			void setup()
			{
				m_bitmapA = al_create_bitmap(32, 32);
				m_bitmapB = al_create_bitmap(32, 32);
			}
			void cleanup()
			{
				al_destroy_bitmap(m_bitmapA);
				al_destroy_bitmap(m_bitmapB);
			}

			setup::Context m_context;

			ALLEGRO_BITMAP * m_bitmapA = nullptr;
			ALLEGRO_BITMAP * m_bitmapB = nullptr;
			ALLEGRO_BITMAP * m_bitmapC = nullptr;
		};
	}
}