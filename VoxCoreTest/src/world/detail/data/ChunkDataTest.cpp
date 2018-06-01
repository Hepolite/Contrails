
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
				LightPropagationNode node;

				for (unsigned int i = 0; i < LIGHT_PROPAGATION_CHANNEL_COUNT; ++i)
				{
					Assert::IsFalse(data.pollLightPropagation(node, i));
					data.pushLightPropagation({ 42u, 31u }, i);
					Assert::IsTrue(data.pollLightPropagation(node, i));
					Assert::IsFalse(data.pollLightPropagation(node, i));
					Assert::AreEqual(42u, static_cast<unsigned int>(node.m_index));
					Assert::AreEqual(31u, node.m_light);
				}
			}
			TEST_METHOD(ChunkDataBloated_pollLight)
			{
				ChunkDataBloated data;
				LightPropagationNode nodeA, nodeB;

				Assert::IsFalse(data.pollLightPropagation(nodeA, LIGHT_PROPAGATION_CHANNEL_SUN));
				Assert::IsFalse(data.pollLightPropagation(nodeB, LIGHT_PROPAGATION_CHANNEL_COLOR));

				data.write(42u, BlockData{ 1u, 2u }, ColorData{ { 5u, 4u, 3u } });

				Assert::IsTrue(data.pollLightPropagation(nodeA, LIGHT_PROPAGATION_CHANNEL_SUN));
				Assert::IsTrue(data.pollLightPropagation(nodeB, LIGHT_PROPAGATION_CHANNEL_COLOR));
				Assert::AreEqual(42u, static_cast<unsigned int>(nodeA.m_index));
				Assert::AreEqual(42u, static_cast<unsigned int>(nodeB.m_index));
				Assert::AreEqual(2u, nodeA.m_light);
				Assert::AreEqual((5u << 16u) | (4u << 8u) | 3u, nodeB.m_light);
			}
		
			TEST_METHOD(ChunkDataBloated_empty)
			{
				ChunkDataBloated data;

				Assert::IsTrue(data.empty());
				data.setFastUnsafe(1337u, BlockData{ 2u, 3u });
				Assert::IsFalse(data.empty());
			}
		};

		TEST_CLASS(ChunkDataCompressedTest)
		{
		public:
			// ...
		};
	}
}