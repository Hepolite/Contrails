
#include "CppUnitTest.h"

#include "world/detail/data/BlockRegion.h"
#include "world/detail/data/ChunkData.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(ChunkDataBloatedTest)
		{
		public:
			TEST_METHOD(ChunkDataBloated_setFastUnsafe)
			{
				ChunkDataBloated data;
				data.setFastUnsafe(1337u, BlockData{ 2u, 3u }, ColorData{ { 4u, 5u, 6u } });

				Assert::AreEqual(2u, data.readBlock(1337u).getId());
				Assert::AreEqual(3u, data.readBlock(1337u).getLight());
				Assert::AreEqual({ 4u, 5u, 6u }, data.readColor(1337u).getColor());
			}
			TEST_METHOD(ChunkDataBloated_write)
			{
				ChunkDataBloated data;
				data.write(42u, BlockData{ 1u, 5u }, ColorData{ { 4u, 2u, 8u } });

				Assert::AreEqual(1u, data.readBlock(42u).getId());
				Assert::AreEqual(5u, data.readBlock(42u).getLight());
				Assert::AreEqual({ 4u, 2u, 8u }, data.readColor(42u).getColor());
			}
			TEST_METHOD(ChunkDataBloated_read)
			{
				BlockRegion regionA{ glm::ivec3{ -1 }, glm::ivec3{ 6 } };
				BlockRegion regionB{ glm::ivec3{ -1 }, glm::ivec3{ 6 } };
				ChunkDataBloated data;
				data.write(toIndex<unsigned int>({ 3u, 1u, 0u }), BlockData{ 1u, 0u });
				data.write(toIndex<unsigned int>({ 4u, 0u, 2u }), BlockData{ 2u, 0u });

				data.read(regionA, { 0, 0, 0 }, { 0, 0, 0 }, { 4, 4, 4 });
				data.read(regionB, { 4, 0, 0 }, { -1, 0, 0 }, { 1, 4, 4 });
				
				Assert::AreEqual(1u, regionA.readBlock({ 3, 1, 0 }).getId());
				Assert::AreEqual(2u, regionB.readBlock({ -1, 0, 2 }).getId());
			}

			TEST_METHOD(ChunkDataBloated_pushLight)
			{
				ChunkDataBloated data;
				Index propagation, removal;

				Assert::IsFalse(data.pollLightPropagation(propagation));
				Assert::IsFalse(data.pollLightRemoval(removal));

				data.pushLightPropagation(42u);
				data.pushLightRemoval(1337u);

				Assert::IsTrue(data.pollLightPropagation(propagation));
				Assert::IsTrue(data.pollLightRemoval(removal));
				Assert::IsFalse(data.pollLightPropagation(propagation));
				Assert::IsFalse(data.pollLightRemoval(removal));
				Assert::AreEqual(42u, static_cast<unsigned int>(propagation));
				Assert::AreEqual(1337u, static_cast<unsigned int>(removal));
			}
			TEST_METHOD(ChunkDataBloated_pollLight)
			{
				ChunkDataBloated data;
				Index index;

				Assert::IsFalse(data.pollLightPropagation(index));
				data.write(42u, BlockData{ 1u, 31u }, ColorData{ { 0u, 0u, 0u } });
				Assert::IsTrue(data.pollLightPropagation(index));

				Assert::IsFalse(data.pollLightRemoval(index));
				data.write(42u, BlockData{ 0u, 0u }, ColorData{ { 0u, 0u, 0u } });
				Assert::IsTrue(data.pollLightRemoval(index));
			}
		};

		TEST_CLASS(ChunkDataCompressedTest)
		{
		public:
			// ...
		};
	}
}