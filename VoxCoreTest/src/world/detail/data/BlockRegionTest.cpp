
#include "CppUnitTest.h"

#include "world/detail/data/BlockRegion.h"
#include "util/Maths.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(BlockRegionTest)
		{
		public:
			TEST_METHOD(BlockRegion_ctor)
			{
				BlockRegion regionA;
				BlockRegion regionB{ glm::ivec3{ -1 }, glm::ivec3{ CHUNK_SIZE<int> + 2 } };

				const auto memuseA = (sizeof(BlockData) + sizeof(ColorData)) * CHUNK_SIZE_VOLUME<unsigned int>;
				const auto memuseB = (sizeof(BlockData) + sizeof(ColorData)) * math::pow(CHUNK_SIZE<unsigned int> + 2u, 3u);
				Assert::AreEqual(memuseA, regionA.memuse());
				Assert::AreEqual(memuseB, regionB.memuse());
			}

			TEST_METHOD(BlockRegion_write)
			{
				BlockRegion region{ glm::ivec3{ -1 }, glm::ivec3{ 6 } };
				region.write({ 3, 1, 4 }, BlockData{ 1u, 31u }, ColorData{ { 4u, 8u, 12u } });
				region.write({ -1, 3, 0 }, BlockData{ 2u, 30u }, ColorData{ { 20u, 21u, 22u } });

				Assert::AreEqual(1u, region.readBlock({ 3, 1, 4 }).getId());
				Assert::AreEqual(2u, region.readBlock({ -1, 3, 0 }).getId());
				Assert::AreEqual(0u, region.readBlock({ -2, 0, 0 }).getId());

				Assert::AreEqual(31u, region.readBlock({ 3, 1, 4 }).getLight());
				Assert::AreEqual(30u, region.readBlock({ -1, 3, 0 }).getLight());
				Assert::AreEqual(0u, region.readBlock({ 0, 5, 0 }).getLight());

				Assert::AreEqual({ 4u, 8u, 12u }, region.readColor({ 3, 1, 4 }).getColor());
				Assert::AreEqual({ 20u, 21u, 22u }, region.readColor({ -1, 3, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 0u }, region.readColor({ 2, 1, 5 }).getColor());
			}
		};
	}
}