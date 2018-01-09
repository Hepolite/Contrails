
#include "CppUnitTest.h"

#include "asset/factory/FactorySprite.h"
#include "render/allegro/Allegro.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	namespace factory
	{
		TEST_CLASS(LoaderSpriteTest)
		{
		public:
			LoaderSpriteTest() { initialize(); }
			~LoaderSpriteTest() { deinitialize(); }

			TEST_METHOD(LoaderSprite_load)
			{
				render::allegro::Sprite sprite;
				LoaderSprite{}.load(sprite, "sprite.xml");

				Assert::IsTrue(sprite.has("frameA"));
				Assert::IsTrue(sprite.has("frameB"));
				auto & frameA = sprite.get("frameA");
				auto & frameB = sprite.get("frameB");

				Assert::AreEqual({ 0, 12 }, frameA.getPos());
				Assert::AreEqual({ 32, 8 }, frameA.getSize());
				Assert::AreEqual({ 0.0f, 0.25f, 0.5f, 1.0f }, frameA.getTint());
				Assert::AreEqual(0, frameA.getFlags());

				Assert::AreEqual({ 16, 10 }, frameB.getPos());
				Assert::AreEqual({ 16, 24 }, frameB.getSize());
				Assert::AreEqual({ 1.0f, 1.0f, 1.0f, 1.0f }, frameB.getTint());
				Assert::AreEqual(2, frameB.getFlags());
			}

		private:
			void initialize() const
			{
				io::File{ "sprite.xml" }.write(R"(
					<file>path/to/sprite.png</file>
					<frames>
						<single name="frameA" pos="0 12" size="32 8" tint="0 0.25 0.5 1" />
						<single name="frameB" pos="16 10" size="16 24" flip="0 1" />
					</frames>
					)");
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