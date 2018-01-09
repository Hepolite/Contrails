
#include "CppUnitTest.h"

#include "render/allegro/Sprite.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(SpriteFrameTest)
		{
		public:
			TEST_METHOD(SpriteFrame_ctor)
			{
				Sprite sprite;
				sprite.create(64, 64);
				SpriteFrame frame{ sprite.getHandle(), { 32, 16 }, { 24, 30 } };

				Assert::IsNotNull(frame.getHandle());
				Assert::AreEqual({ 32, 16 }, frame.getPos());
				Assert::AreEqual({ 24, 30 }, frame.getSize());
			}

			TEST_METHOD(SpriteFrame_tint)
			{
				SpriteFrame frame{ nullptr, {}, {} };
				frame.tint({ 0.25f, 0.5f, 0.75f, 1.0f });

				Assert::AreEqual({ 0.25f, 0.5f, 0.75f, 1.0f }, frame.getTint());
			}

		private:
			setup::Context m_context;
		};

		TEST_CLASS(SpriteTest)
		{
		public:
			TEST_METHOD(Sprite_create)
			{
				Sprite sprite;

				Assert::IsTrue(sprite.create(32u, 32u));
				Assert::IsFalse(sprite.create(32u, 32u));
				Assert::IsNotNull(sprite.getHandle());
			}

			TEST_METHOD(Sprite_add)
			{
				Sprite sprite;

				Assert::IsTrue(sprite.add("frameA", { nullptr, { 0, 8 }, { 16, 16 } }));
				Assert::IsFalse(sprite.add("frameA", { nullptr, { 16, 8 }, { 16, 16 } }));
			}
			TEST_METHOD(Sprite_has)
			{
				Sprite sprite;
				sprite.add("frameA", { nullptr, { 0, 8 }, { 16, 16 } });

				Assert::IsTrue(sprite.has("frameA"));
				Assert::IsFalse(sprite.has("frameB"));
			}
			TEST_METHOD(Sprite_get)
			{
				Sprite sprite;
				sprite.create(32, 32);
				sprite.add("frameA", { sprite.getHandle(), { 0, 8 }, { 16, 16 } });

				auto & frame = sprite.get("frameA");
				Assert::IsNotNull(frame.getHandle());
				Assert::AreEqual({ 0, 8 }, frame.getPos());
				Assert::AreEqual({ 16, 16 }, frame.getSize());
				Assert::ExpectException<std::invalid_argument>([&sprite]() {sprite.get("frameB"); });
			}

		private:
			setup::Context m_context;
		};
	}
}