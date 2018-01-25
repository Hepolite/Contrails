
#include "CppUnitTest.h"

#include "world/detail/data/BlockData.h"
#include "world/detail/Limits.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(BlockDataTest)
		{
		public:
			TEST_METHOD(BlockData_limit)
			{
				static_assert(MAX_BLOCK_ID < 2048u, "No more than 2048 block ids are supported");
				static_assert(MAX_BLOCK_LIGHT < 32u, "No more than 32 light colors are supported");
			}

			TEST_METHOD(BlockData_ctor)
			{
				BlockData dataA{ 1u, 2u };
				BlockData dataB{ MAX_BLOCK_ID, MAX_BLOCK_LIGHT };

				Assert::AreEqual(1u, dataA.getId());
				Assert::AreEqual(2u, dataA.getLight());
				Assert::AreEqual(MAX_BLOCK_ID, dataB.getId());
				Assert::AreEqual(MAX_BLOCK_LIGHT, dataB.getLight());
			}
			TEST_METHOD(BlockData_setId)
			{
				BlockData data;
				data.setId(2047u);
				data.setLight(0u);

				Assert::AreEqual(2047u, data.getId());
				Assert::AreEqual(0u, data.getLight());
			}
			TEST_METHOD(BlockData_setLight)
			{
				BlockData data;
				data.setLight(31u);
				data.setId(0u);

				Assert::AreEqual(0u, data.getId());
				Assert::AreEqual(31u, data.getLight());
			}

			TEST_METHOD(ColorData_ctor)
			{
				ColorData dataA{ { 18u, 31u, 4u } };
				ColorData dataB{ glm::uvec3{ MAX_BLOCK_LIGHT } };

				Assert::AreEqual({ 18u, 31u, 4u }, dataA.getColor());
				Assert::AreEqual(glm::uvec3{ MAX_BLOCK_LIGHT }, dataB.getColor());
			}
			TEST_METHOD(ColorkData_set)
			{
				ColorData data;
				data.setColor({ 31u, 18u, 1u });

				Assert::AreEqual({ 31u, 18u, 1u }, data.getColor());
			}
		};
	}
}