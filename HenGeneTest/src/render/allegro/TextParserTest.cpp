
#include "CppUnitTest.h"

#include "render/allegro/TextParser.h"

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
				parser.parse("Hello World!");

				Assert::IsFalse(parser.empty());
			}
			TEST_METHOD(TextParser_parseSize)
			{
				TextParser parser{ m_registry };
				parser.parse("<size=17>");

				Assert::IsTrue(parser.empty());
				Assert::AreEqual(17u, parser.getSize());
			}

		private:
			asset::AssetRegistry m_registry;
		};
	}
}