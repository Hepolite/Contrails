
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
#include "world/detail/data/LightPropagation.h"
#include "world/World.h"

#include <glm/Unittest.h>

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
				world.write({ 0, 0, 31 }, data::BlockData{ 1u, 31u });
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
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 31u });
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 20u });
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
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 31u });
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 20u });
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
				world.write({ 0, 0, 31 }, data::BlockData{ 1u, 0u });
				LightSunRemover worker{ world, {} };

				worker.spread(chunk);
				Assert::AreEqual(0u, world.readBlock({ 0, 0, 31 }).getLight());
				Assert::AreEqual(0u, world.readBlock({ 0, 0, 0 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 1, 0, 31 }).getLight());
				Assert::AreEqual(31u, world.readBlock({ 0, 1, 31 }).getLight());
			}
		};

		TEST_CLASS(LightColorPropagatorTest)
		{
		public:
			TEST_METHOD(LightColorPropagator_spreadSide)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 25u, 25u, 25u } });
				LightColorPropagator worker{ world, {} };

				worker.spreadSide(chunk, { 0, 0, 0 }, { 10u, 20u, 30u });
				worker.spreadSide(chunk, { 1, 0, 0 }, { 10u, 20u, 30u });
				Assert::AreEqual({ 9u, 19u, 29u }, world.readColor({ 0, 0, 0 }).getColor());
				Assert::AreEqual({ 25u, 25u, 29u }, world.readColor({ 1, 0, 0 }).getColor());
			}
			TEST_METHOD(LightColorPropagator_spreadFrom)
			{
				World world;
				auto & chunk = world.createChunk({});
				LightColorPropagator worker{ world, {} };

				worker.spreadFrom(chunk, { 0, 0, 0 }, { 5u, 10u, 0u });
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ 1, 0, 0 }).getColor());
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ -1, 0, 0 }).getColor());
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ 0, 1, 0 }).getColor());
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ 0, -1, 0 }).getColor());
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ 0, 0, 1 }).getColor());
				Assert::AreEqual({ 4u, 9u, 0u }, world.readColor({ 0, 0, -1 }).getColor());
			}
			TEST_METHOD(LightColorPropagator_spread)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 3u, 31u, 10u } });
				LightColorPropagator worker{ world, {} };

				worker.spread(chunk);
				Assert::AreEqual({ 3u, 31u, 10u }, world.readColor({ 0, 0, 0 }).getColor());
				Assert::AreEqual({ 2u, 30u, 9u }, world.readColor({ 0, 0, 1 }).getColor());
				Assert::AreEqual({ 0u, 26u, 5u }, world.readColor({ 5, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 6u, 0u }, world.readColor({ 0, 25, 0 }).getColor());
			}
		};
		TEST_CLASS(LightColorRemoverTest)
		{
		public:
			TEST_METHOD(LightColorRemover_spreadSide)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 15u, 20u, 0u } });
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 31u, 31u } });
				LightColorRemover worker{ world, {} };

				worker.spreadSide(chunk, { 0, 0, 0 }, { 25u, 25u, 25u });
				worker.spreadSide(chunk, { 1, 0, 0 }, { 25u, 25u, 25u });
				Assert::AreEqual({ 0u, 0u, 0u }, world.readColor({ 0, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 31u, 31u }, world.readColor({ 1, 0, 0 }).getColor());
			}
			TEST_METHOD(LightColorRemover_spreadFrom)
			{
				World world;
				auto & chunk = world.createChunk({});
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 31u, 31u, 31u } });
				world.write({ -1, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 21u, 29u } });
				world.write({ 0, 1, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 28u, 21u } });
				world.write({ 0, -1, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 3u, 25u } });
				world.write({ 0, 0, 1 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 15u, 19u } });
				world.write({ 0, 0, -1 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 20u, 0u, 5u } });
				LightColorRemover worker{ world, {} };

				worker.spreadFrom(chunk, { 0, 0, 0 }, { 25u, 25u, 25u });
				Assert::AreEqual({ 31u, 31u, 31u }, world.readColor({ 1, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 29u }, world.readColor({ -1, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 28u, 0u }, world.readColor({ 0, 1, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 25u }, world.readColor({ 0, -1, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 0u }, world.readColor({ 0, 0, 1 }).getColor());
				Assert::AreEqual({ 0u, 0u, 0u }, world.readColor({ 0, 0, -1 }).getColor());
			}
			TEST_METHOD(LightColorRemover_spread)
			{
				World world;
				auto & chunk = world.createChunk({}, true);
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 31u, 31u, 31u } });
				world.write({ 1, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 29u, 29u, 31u } });
				world.write({ 2, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 27u, 27u, 31u } });
				world.write({ 3, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 25u, 31u, 31u } });
				world.write({ 4, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 23u, 31u, 31u } });
				world.write({ 5, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 25u, 31u, 31u } });
				world.write({ 0, 0, 0 }, data::BlockData{ 1u, 0u }, data::ColorData{ { 0u, 0u, 0u } });
				LightColorRemover worker{ world, {} };

				worker.spread(chunk);
				Assert::AreEqual({ 0u, 0u, 0u }, world.readColor({ 0, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 31u }, world.readColor({ 1, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 0u, 31u }, world.readColor({ 2, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 31u, 31u }, world.readColor({ 3, 0, 0 }).getColor());
				Assert::AreEqual({ 0u, 31u, 31u }, world.readColor({ 4, 0, 0 }).getColor());
				Assert::AreEqual({ 25u, 31u, 31u }, world.readColor({ 5, 0, 0 }).getColor());
			}
		};
	}
}