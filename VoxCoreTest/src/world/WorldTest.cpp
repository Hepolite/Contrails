
#include "CppUnitTest.h"

#include "world/detail/data/WorldQuery.h"
#include "world/util/Query.h"
#include "world/World.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(WorldTest)
	{
	public:
		TEST_METHOD(World_createChunk)
		{
			World world;
			auto & chunk = world.createChunk({ 0, 0, 0 });

			glm::ivec3 pos;
			for (pos.x = -1; pos.x <= 1; ++pos.x)
			for (pos.y = -1; pos.y <= 1; ++pos.y)
			for (pos.z = -1; pos.z <= 1; ++pos.z)
				Assert::IsTrue(world.hasChunkAt(pos));
			Assert::IsTrue(&chunk == world.getChunkAt({ 0, 0, 0 }));
		}
		// TEST_METHOD(World_destroyChunk)

		TEST_METHOD(World_hasChunkAt)
		{
			World world;

			Assert::IsFalse(world.hasChunkAt({ 0, 0, 0 }));
			world.createChunk({ 0, 0, 0 });
			Assert::IsTrue(world.hasChunkAt({ 0, 0, 0 }));
		}
		TEST_METHOD(World_getChunkAt)
		{
			World world;
			auto & chunkA = world.createChunk({ 0, 0, 0 });
			auto & chunkB = world.createChunk({ 1, 0, 0 });

			Assert::IsTrue(&chunkA == world.getChunkAt({ 0, 0, 0 }));
			Assert::IsTrue(&chunkB == world.getChunkAt({ 1, 0, 0 }));
		}
		TEST_METHOD(World_getChunkAbove)
		{
			World world;
			world.createChunk({ 0, 0, -4 });
			world.createChunk({ 0, 0, 1 });
			world.createChunk({ 0, 0, 9 });

			Assert::IsTrue(world.getChunkAt({ 0, 0, -4 }) == world.getChunkAbove({ 0, 0, -5 }));
			Assert::IsTrue(world.getChunkAt({ 0, 0, 0 }) == world.getChunkAbove({ 0, 0, -3 }));
			Assert::IsTrue(world.getChunkAt({ 0, 0, 8 }) == world.getChunkAbove({ 0, 0, 3 }));
			Assert::IsNull(world.getChunkAbove({ 0, 0, 10 }));
		}
		TEST_METHOD(World_getChunkBelow)
		{
			World world;
			world.createChunk({ 0, 0, -4 });
			world.createChunk({ 0, 0, 1 });
			world.createChunk({ 0, 0, 9 });

			Assert::IsTrue(world.getChunkAt({ 0, 0, -4 }) == world.getChunkBelow({ 0, 0, -3 }));
			Assert::IsTrue(world.getChunkAt({ 0, 0, 2 }) == world.getChunkBelow({ 0, 0, 8 }));
			Assert::IsTrue(world.getChunkAt({ 0, 0, 10 }) == world.getChunkBelow({ 0, 0, 161 }));
			Assert::IsNull(world.getChunkBelow({ 0, 0, -5 }));
		}

		TEST_METHOD(World_getBottommostChunk)
		{
			World world;
			world.createChunk({ 0, 0, -4 });
			world.createChunk({ 0, 0, 9 });

			Assert::IsTrue(world.getChunkAt({ 0, 0, -5 }) == world.getBottommostChunk({ 0, 0 }));
		}
		TEST_METHOD(World_getTopmostChunk)
		{
			World world;
			world.createChunk({ 0, 0, -4 });
			world.createChunk({ 0, 0, 9 });

			Assert::IsTrue(world.getChunkAt({ 0, 0, 10 }) == world.getTopmostChunk({ 0, 0 }));
		}

		// ...

		TEST_METHOD(World_writeData)
		{
			World world;
			world.write({ 3, 1, 4 }, data::BlockData{ 4u, 29u }, data::ColorData{ { 1u, 2u, 3u } });

			Assert::AreEqual(4u, world.readBlock({ 3, 1, 4 }).getId());
			Assert::AreEqual(29u, world.readBlock({ 3, 1, 4 }).getLight());
			Assert::AreEqual({ 1u, 2u, 3u }, world.readColor({ 3, 1, 4 }).getColor());
		}
		TEST_METHOD(World_writeQuery)
		{
			Block block{ 1u, "stone" };
			World world;
			world.write(util::Query{}.writeBlock(block, { 3, 1, 4 }));

			Assert::AreEqual(1u, world.readBlock({ 3, 1, 4 }).getId());
			Assert::AreEqual(0u, world.readBlock({ 3, 1, 4 }).getLight());
			Assert::AreEqual({ 0u, 0u, 0u }, world.readColor({ 3, 1, 4 }).getColor());
		}
		TEST_METHOD(World_readQuery)
		{
			World world;
			world.write({ 3, 1, 4 }, data::BlockData{ 4u, 29u }, data::ColorData{ { 1u, 2u, 3u } });

			auto query = util::Query{}.readBlock({ 3, 1, 4 });
			world.read(query);

			const auto & data = *query.begin()->second.begin();
			Assert::AreEqual(4u, data.m_block.getId());
			Assert::AreEqual(29u, data.m_block.getLight());
			Assert::AreEqual({ 1u, 2u, 3u }, data.m_color.getColor());
		}
	};
}