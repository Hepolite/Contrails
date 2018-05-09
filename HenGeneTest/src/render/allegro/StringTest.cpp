
#include "CppUnitTest.h"

#include "asset/AssetRegistry.h"
#include "asset/factory/FactoryFont.h"
#include "asset/builtin/Font.h"
#include "render/allegro/String.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(StringTest)
		{
		public:
			StringTest() { initialize(); }
			~StringTest() { deinitialize(); }

			TEST_METHOD(String_move)
			{
				String strA = build("Foo");
				String strB = build("Bar");
				strB = std::move(strA);

				Assert::AreEqual({ "Foo" }, strB.getString());
			}

			TEST_METHOD(String_getString)
			{
				String str = build("This is a string");
				Assert::AreEqual({ "This is a string" }, str.getString());
			}
			TEST_METHOD(String_getDimensions)
			{
				String str = build("Hello World");
				Assert::AreNotEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, str.getDimensions());
			}

			TEST_METHOD(String_draw)
			{
				const glm::vec2 start{ 3.0f, 4.0f };
				const glm::vec4 bbox{ 0.0f, 0.0f, 200.0f, 1000.0f };

				String str = build("Sometimes life just gives you lemons, but you wanted onions...");
				str.draw(start);
				str.draw(start, bbox);

				// TODO: Check the return values and ensure they are valid
			}

		private:
			void initialize()
			{
				io::File{ "font.ttf" }.writeDangerous(asset::builtin::FONT_DATA, asset::builtin::FONT_SIZE);
				m_registry.add<Font>("font").m_factory = []()
				{
					auto asset = std::make_unique<Font>();
					asset::factory::LoaderFont{}.load(*asset, "font.ttf");
					return asset;
				};
			}
			void deinitialize()
			{
				io::File{ "font.ttf" }.erase();
			}

			String build(const std::string & str, unsigned int size = 12u)
			{
				String string{ str };
				string.setFont(m_registry.get<Font>("font"));
				string.setSize(size);
				return string;
			}

			asset::AssetRegistry m_registry;
			setup::Context m_context;
		};
	}
}