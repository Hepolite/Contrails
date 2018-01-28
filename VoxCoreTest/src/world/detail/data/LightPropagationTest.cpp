
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
#include "world/detail/data/LightPropagation.h"
#include "world/World.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(LightSunPropagatorTest)
		{
		public:
			TEST_METHOD(LightSunPropagator_spreadSide)
			{
				World world;
				auto & chunk = world.createChunk({});
				LightSunPropagator worker{ world, {} };
				
				worker.spreadSide(chunk, { 1, 1, 1 }, 20u);
				Assert::AreEqual(19u, world.readBlock({ 1, 1, 1 }).getLight());
			}
			TEST_METHOD(LightSunPropagator_spreadDown)
			{
				World world;
				auto & chunk = world.createChunk({});
				LightSunPropagator worker{ world,{} };

				worker.spreadDown(chunk, { 1, 1, 1 }, 20u);
				Assert::AreEqual(20u, world.readBlock({ 1, 1, 1 }).getLight());
			}
			TEST_METHOD(LightSunPropagator_spreadFrom)
			{
				World world;
				auto & chunk = world.createChunk({});
				LightSunPropagator worker{ world, {} };

				worker.spreadFrom(chunk, { 0, 0, 0 }, 20u);
				Assert::AreEqual(19u, world.readBlock({ 1, 0, 0 }).getLight());
				Assert::AreEqual(19u, world.readBlock({ -1, 0, 0 }).getLight());
				Assert::AreEqual(19u, world.readBlock({ 0, 1, 0 }).getLight());
				Assert::AreEqual(19u, world.readBlock({ 0, -1, 0 }).getLight());
				Assert::AreEqual(19u, world.readBlock({ 0, 0, 1 }).getLight());
				Assert::AreEqual(20u, world.readBlock({ 0, 0, -1 }).getLight());
			}
			TEST_METHOD(LightSunPropagator_spread)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 0, 0, 31 }, data::BlockData{ 0u, 31u });
				LightSunPropagator worker{ world, {} };

				worker.spread(chunk);
				Assert::AreEqual(31u, world.readBlock({ 0, 0, 31 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, 0, 0 }).getLight());
				Assert::AreEqual(21u, world.readBlock({ 10, 0, 31 }).getLight());
				Assert::AreEqual(1u, world.readBlock({ 30, 0, 31 }).getLight());
				Assert::AreEqual(1u, world.readBlock({ 0, 30, 31 }).getLight());
				Assert::AreEqual(1u, world.readBlock({ 0, 30, 0 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 31, 0, 31 }).getLight());
			}
		};

		TEST_CLASS(LightSunRemoverTest)
		{
		public:
			TEST_METHOD(LightSunRemover_spreadSide)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 0, 0, 0 }, data::BlockData{ 0u, 31u });
				world.write({ 1, 0, 0 }, data::BlockData{ 0u, 20u });
				LightSunRemover worker{ world,{} };

				worker.spreadSide(chunk, { 0, 0, 0 }, 25u);
				worker.spreadSide(chunk, { 1, 0, 0 }, 25u);
				Assert::AreEqual(31u, world.readBlock({ 0, 0, 0 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 1, 0, 0 }).getLight());
			}
			TEST_METHOD(LightSunRemover_spreadDown)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 0, 0, 0 }, data::BlockData{ 0u, 31u });
				world.write({ 1, 0, 0 }, data::BlockData{ 0u, 20u });
				LightSunRemover worker{ world, {} };

				worker.spreadDown(chunk, { 0, 0, 0 }, 25u);
				worker.spreadDown(chunk, { 1, 0, 0 }, 25u);
				Assert::AreEqual(0u, world.readBlock({ 0, 0, 0 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 1, 0, 0 }).getLight());
			}
			TEST_METHOD(LightSunRemover_spreadFrom)
			{
				World world;
				auto & chunk = world.createChunk({}, true);
				LightSunRemover worker{ world, {} };

				worker.spreadFrom(chunk, { 0, 0, 0 }, 25u);
				Assert::AreEqual(31u, world.readBlock({ 1, 0, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ -1, 0, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, 1, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, -1, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, 0, 1 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 0, 0, -1 }).getLight());
			}
			TEST_METHOD(LightSunRemover_spread)
			{
				World world;
				auto & chunk = world.createChunk({}, true);
				world.write({ 0, 0, 31 }, data::BlockData{ 0u, 0u });
				LightSunRemover worker{ world, {} };

				worker.spread(chunk);
				Assert::AreEqual(0u, world.readBlock({ 0, 0, 31 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 0, 0, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 1, 0, 31 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, 1, 31 }).getLight());
			}
		};
	}
}