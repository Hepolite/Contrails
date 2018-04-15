
#include "CppUnitTest.h"

#include "logic/event/ChunkEvents.h"
#include "logic/event/EventBus.h"
#include "world/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	namespace event
	{
		TEST_CLASS(ChunkEventTest)
		{
		public:
			TEST_METHOD(ChunkEvent_ChunkCreate)
			{
				EventBus bus;
				world::World world;
				world.inject(bus);

				bool created = false;
				auto listener = bus.add<ChunkCreate>([&created](auto & event) { created = true; });
				world.createChunk({ 0, 0, 0 }, false);

				Assert::IsTrue(created);
			}
			TEST_METHOD(ChunkEvent_ChunkDestroy)
			{
				EventBus bus;
				world::World world;
				world.inject(bus);
				world.createChunk({ 0, 0, 0 }, false);

				bool destroyed = false;
				auto listener = bus.add<ChunkDestroy>([&destroyed](auto & event) { destroyed = true; });
				world.destroyChunk({ 0, 0, 0 });

				Assert::IsTrue(destroyed);
			}

			TEST_METHOD(ChunkEvent_ChunkChange)
			{
				EventBus bus;
				world::World world;
				world.inject(bus);

				unsigned int counter = 0u;
				auto listener = bus.add<ChunkChange>([&counter](auto & event) { ++counter; });

				world.write({ 0, 0, 0 }, world::data::BlockData{ 1u, 0u });
				Assert::AreEqual(1u, counter);

				world.write({ 0, 0, 0 }, world::data::ColorData{ { 0u, 0u, 0u } });
				Assert::AreEqual(2u, counter);

				world.markChunkChange({ 0, 0, 0 });
				Assert::AreEqual(3u, counter);
			}
		};
	}
}