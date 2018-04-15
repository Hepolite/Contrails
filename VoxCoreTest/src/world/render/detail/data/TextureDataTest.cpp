
#include "CppUnitTest.h"

#include "world/detail/Limits.h"
#include "world/render/detail/data/BlockTexture.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		namespace data
		{
			TEST_CLASS(TextureDataTest)
			{
			public:
				TEST_METHOD(TextureData_limit)
				{
					static_assert(::world::data::MAX_TEXTURE_ID < 65536u, "No more than 65536 texture ids are supported");
					static_assert(::world::data::MAX_TEXTURE_META < 356u, "No more than 256 texture meta values are supported");
				}

				TEST_METHOD(TextureData_ctor)
				{
					TextureData dataA{ 1u, 2u, 3u };
					TextureData dataB{ ::world::data::MAX_TEXTURE_ID, ::world::data::MAX_TEXTURE_META, 137u };

					Assert::AreEqual(1u, dataA.getTexture());
					Assert::AreEqual(2u, dataA.getMeta());
					Assert::AreEqual(3u, dataA.getHash());
					Assert::AreEqual(::world::data::MAX_TEXTURE_ID, dataB.getTexture());
					Assert::AreEqual(::world::data::MAX_TEXTURE_META, dataB.getMeta());
					Assert::AreEqual(137u, dataB.getHash());
				}

				TEST_METHOD(TextureData_setTexture)
				{
					TextureData data;
					data.setTexture(65535u);

					Assert::AreEqual(65535u, data.getTexture());
					Assert::AreEqual(0u, data.getMeta());
					Assert::AreEqual(0u, data.getHash());
				}
				TEST_METHOD(TextureData_setMeta)
				{
					TextureData data;
					data.setMeta(255u);

					Assert::AreEqual(0u, data.getTexture());
					Assert::AreEqual(255u, data.getMeta());
					Assert::AreEqual(0u, data.getHash());
				}
				TEST_METHOD(TextureData_setHash)
				{
					TextureData data;
					data.setHash(255u);

					Assert::AreEqual(0u, data.getTexture());
					Assert::AreEqual(0u, data.getMeta());
					Assert::AreEqual(255u, data.getHash());
				}
			};
		}
	}
}