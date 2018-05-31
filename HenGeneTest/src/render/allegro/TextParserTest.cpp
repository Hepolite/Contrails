
#include "CppUnitTest.h"

#include "render/allegro/TextParser.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(TextParserTest)
		{
		public:
			TEST_METHOD(TextParser_parsePlainText)
			{
				TextParser parser{ m_registry };
				parser.parse({ "Hello World!" });

				Assert::IsFalse(parser.empty());
				Assert::AreEqual(1u, parser.size());
			}
			TEST_METHOD(TextParser_parseSize)
			{
				TextParser parser{ m_registry };
				parser.parse({ "{size 17}Text" });

				Assert::AreEqual(1u, parser.size());
				Assert::AreEqual(17u, parser.getSize());
			}
			TEST_METHOD(TextParser_parseFont)
			{
				TextParser parser{ m_registry };
				parser.parse({ "{font chickenscratch}Text" });

				Assert::AreEqual(1u, parser.size());
				Assert::AreEqual({ "chickenscratch" }, parser.getFont());
			}
			TEST_METHOD(TextParser_parseColor)
			{
				TextParser parser{ m_registry };
				parser.parse({ "{color 0.2 0.57 0.375 1}Text" });

				Assert::AreEqual(1u, parser.size());
				Assert::AreEqual(0.2f, parser.getColor().r, 0.001f);
				Assert::AreEqual(0.57f, parser.getColor().g, 0.001f);
				Assert::AreEqual(0.375f, parser.getColor().b, 0.001f);
				Assert::AreEqual(1.0f, parser.getColor().a, 0.001f);
			}

			TEST_METHOD(TextParser_parseDefaultWithChange)
			{
				TextParser parser{ m_registry };
				parser.parse({ "Hello{size 17}World!" });

				Assert::AreEqual(2u, parser.size());
				Assert::AreEqual(17u, parser.getSize());
			}
			TEST_METHOD(TextParser_parseComplexText)
			{
				TextParser parser{ m_registry };
				parser.parse({ "Hello{size 17}{color 0.5 0.2 0.8 0.15}World!{size 15}Test{font foo}" });

				Assert::AreEqual(3u, parser.size());
				Assert::AreEqual(15u, parser.getSize());
				Assert::AreEqual({ "foo" }, parser.getFont());
				Assert::AreEqual(0.5f, parser.getColor().r, 0.001f);
				Assert::AreEqual(0.2f, parser.getColor().g, 0.001f);
				Assert::AreEqual(0.8f, parser.getColor().b, 0.001f);
				Assert::AreEqual(0.15f, parser.getColor().a, 0.001f);
			}

		private:
			asset::AssetRegistry m_registry;
		};
	}
}