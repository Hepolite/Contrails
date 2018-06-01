
#include "CppUnitTest.h"

#include "render/allegro/TextBuilder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(TextBuilderTest)
		{
		public:
			TEST_METHOD(TextBuilder_build)
			{
				asset::AssetRegistry registry;
				TextBuilder builder{ registry };
				builder.addString({ "Hello World!" });
				const auto text = builder.build();

				Assert::IsFalse(text.empty());
			}
		};
	}
}