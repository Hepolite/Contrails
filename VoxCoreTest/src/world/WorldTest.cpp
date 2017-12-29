
#include "CppUnitTest.h"

#include "world/World.h"
#include "logic/event/ChunkEvents.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(WorldTest)
	{
	public:
		TEST_METHOD(World_writeQuery)
		{
			World world;
			data::WorldQuery query;
			query.add({ 0, 0, 0 }, data::BlockData{ 1u, 0u });

			// Any chunk write operation must ensure that 26 neighbors are present around the chunk for lighting purposes
			world.write(query);

			for (int x = -1; x <= 1; ++x)
			for (int y = -1; y <= 1; ++y)
			for (int z = -1; z <= 1; ++z)
				Assert::IsTrue(world.hasChunkAt({ x, y, z }));
		}

		// ...

		TEST_METHOD(World_createChunk)
		{
			World world;
			world.createChunk({ 3, 1, -2 });

			Assert::IsFalse(world.hasChunkAt({ -1, 2, 6 }));
			Assert::IsTrue(world.hasChunkAt({ 3, 1, -2 }));
			Assert::ExpectException<std::invalid_argument>([&world]() { world.createChunk({ 3, 1, -2 }); });
		}
		TEST_METHOD(World_destroyChunk)
		{
			World world;
			world.createChunk({ 1, 6, -1 });
			world.destroyChunk({ 1, 6, -1 });

			Assert::IsFalse(world.hasChunkAt({ 1, 6, -1 }));
			Assert::ExpectException<std::invalid_argument>([&world]() { world.destroyChunk({ 1, 6, -1 }); });
		}

		TEST_METHOD(World_getChunkAt)
		{
			World world;
			world.createChunk({ 5, 0, 0 });

			Assert::IsNull(world.getChunkAt({ 4, 0, 0 }));
			Assert::IsNotNull(world.getChunkAt({ 5, 0, 0 }));
		}
		TEST_METHOD(World_getChunkAbove)
		{
			World world;
			auto & chunkA = world.createChunk({ 1, -3, 7 });
			auto & chunkB = world.createChunk({ 1, -3, -2 });

			Assert::IsNull(world.getChunkAbove({ -5, 1, 7 }));
			Assert::IsNull(world.getChunkAbove({ 1, -3, 7 }));
			Assert::IsTrue(&chunkA == world.getChunkAbove({ 1, -3, 6 }));
			Assert::IsTrue(&chunkA == world.getChunkAbove({ 1, -3, -2 }));
			Assert::IsTrue(&chunkB == world.getChunkAbove({ 1, -3, -3 }));
		}
		TEST_METHOD(World_getChunkBelow)
		{
			World world;
			auto & chunkA = world.createChunk({ 7, 0, -4 });
			auto & chunkB = world.createChunk({ 7, 0, 8 });

			Assert::IsNull(world.getChunkBelow({ 0, -2, -4 }));
			Assert::IsNull(world.getChunkBelow({ 7, 0, -4 }));
			Assert::IsTrue(&chunkA == world.getChunkBelow({ 7, 0, -3 }));
			Assert::IsTrue(&chunkA == world.getChunkBelow({ 7, 0, 8 }));
			Assert::IsTrue(&chunkB == world.getChunkBelow({ 7, 0, 9 }));
		}

		TEST_METHOD(World_getOutermostChunks)
		{
			World world;
			auto & chunkA = world.createChunk({ 15, -61, 3 });
			auto & chunkB = world.createChunk({ 15, -61, -4 });
			auto & chunkC = world.createChunk({ 15, -61, 8 });

			Assert::IsTrue(&chunkB == world.getBottommostChunk({ 15, -61 }));
			Assert::IsTrue(&chunkC == world.getTopmostChunk({ 15, -61 }));
			Assert::IsNull(world.getBottommostChunk({ 3, 1 }));
			Assert::IsNull(world.getTopmostChunk({ -5, 2 }));
		}

		// ...

		TEST_METHOD(World_Event_ChunkCreate)
		{
			logic::event::EventBus bus;
			World world{ bus };

			bool received = false;
			bus.add<logic::event::ChunkCreate>([&received](auto & event) { received = true; });

			Assert::IsFalse(received);
			world.createChunk({});
			Assert::IsTrue(received);
		}
		TEST_METHOD(World_Event_ChunkDestroy)
		{
			logic::event::EventBus bus;
			World world{ bus };
			world.createChunk({});

			bool received = false;
			bus.add<logic::event::ChunkDestroy>([&received](auto & event) { received = true; });

			Assert::IsFalse(received);
			world.destroyChunk({});
			Assert::IsTrue(received);
		}
	};
}