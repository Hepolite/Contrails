
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
#include "world/util/Query.h"
#include "world/World.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(WorldLightingTest)
	{
	public:
		TEST_METHOD(WorldLighting_initializeSkylight)
		{
			World world;
			world.createChunk({ 0, 0, 0 }, true);
			world.process();
			
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, 60 }).getLight());
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, 20 }).getLight());
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, -20 }).getLight());
		}
		TEST_METHOD(WorldLighting_castShadow)
		{
			BlockRegistry registry;
			registry.add("stone").m_lightAbsorbed = { 31u, 31u, 31u, 31u };
			
			World world;
			world.inject(registry);
			world.write(util::Query{}.writeRectangle(registry["stone"], { 0, 0, 30 }, { 31, 31, 30 }));
			world.process();
			
			Assert::AreEqual({ 0u, 0u, 0u, 31u }, readLight(world, { -1, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 30u }, readLight(world, { 0, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 25u }, readLight(world, { 5, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 20u }, readLight(world, { 10, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 15u }, readLight(world, { 15, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 15u }, readLight(world, { 15, 15, 0 }));
			Assert::AreEqual({ 0u, 0u, 0u, 20u }, readLight(world, { 21, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 30u }, readLight(world, { 31, 15, 20 }));
		}
		TEST_METHOD(WorldLighting_castShadowChunkBorder)
		{
			BlockRegistry registry;
			registry.add("stone").m_lightAbsorbed = { 31u, 31u, 31u, 31u };

			World world;
			world.inject(registry);
			world.write(util::Query{}.writeRectangle(registry["stone"], { -5, 0, 30 }, { 5, 31, 30 }));
			world.process();

			Assert::AreEqual({ 0u, 0u, 0u, 30u }, readLight(world, { -5, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 26u }, readLight(world, { -1, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 25u }, readLight(world, { 0, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 26u }, readLight(world, { 1, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 30u }, readLight(world, { 5, 15, 20 }));
		}
		TEST_METHOD(WorldLighting_castShadowFarDown)
		{
			BlockRegistry registry;
			registry.add("stone").m_lightAbsorbed = { 31u, 31u, 31u, 31u };

			World world;
			world.inject(registry);
			world.write(util::Query{}.writeRectangle(registry["stone"], { 0, 0, 0 }, { 31, 31, 0 }));
			world.write(util::Query{}.writeRectangle(registry["stone"], { 0, 0, 1000 }, { 31, 31, 1000 }));
			world.process();

			Assert::AreEqual({ 0u, 0u, 0u, 30u }, readLight(world, { 0, 15, 20 }));
			Assert::AreEqual({ 0u, 0u, 0u, 25u }, readLight(world, { 5, 15, 20 }));
		}

		TEST_METHOD(WorldLighting_writeLightBlock)
		{
			BlockRegistry registry;
			auto & block = registry.add("glowblock");
			block.m_lightAbsorbed = { 31u, 31u, 31u, 31u };
			block.m_lightEmitted = { 0u, 16u, 31u, 0u };

			World world;
			world.inject(registry);
			world.write(util::Query{}.writeBlock(block, { 0, 0, 0 }));
			world.process();

			Assert::AreEqual({ 0u, 15u, 30u, 31u }, readLight(world, { 1, 0, 0 }));
			Assert::AreEqual({ 0u, 15u, 30u, 31u }, readLight(world, { -1, 0, 0 }));
			Assert::AreEqual({ 0u, 15u, 30u, 31u }, readLight(world, { 0, 1, 0 }));
			Assert::AreEqual({ 0u, 15u, 30u, 31u }, readLight(world, { 0, -1, 0 }));
			Assert::AreEqual({ 0u, 15u, 30u, 31u }, readLight(world, { 0, 0, 1 }));
			Assert::AreEqual({ 0u, 15u, 30u, 30u }, readLight(world, { 0, 0, -1 }));
			Assert::AreEqual({ 0u, 14u, 29u, 31u }, readLight(world, { 2, 0, 0 }));
			Assert::AreEqual({ 0u, 14u, 29u, 31u }, readLight(world, { -2, 0, 0 }));
			Assert::AreEqual({ 0u, 5u, 20u, 30u }, readLight(world, { 0, 0, -11 }));
		}
		TEST_METHOD(WorldLighting_writeLightBlockChunkBorder)
		{
			BlockRegistry registry;
			registry.add("stone").m_lightAbsorbed = { 31u, 31u, 31u, 31u };
			registry.add("glowblock").m_lightEmitted = { 0u, 16u, 31u, 0u };

			World world;
			world.inject(registry);
			world.write(util::Query{}.writeBlock(registry["glowblock"], { 0, 15, 29 }));
			world.process();
			world.write(util::Query{}.writeRectangle(registry["stone"], { -5, 0, 30 }, { 5, 31, 30 }));
			world.process();

			Assert::AreEqual({ 0u, 2u, 17u, 31u }, readLight(world, { 0, 15, 31 }));
		}

		TEST_METHOD(WorldLighting_repropagateSkylight)
		{
			BlockRegistry registry;
			registry.add("stone").m_lightAbsorbed = { 31u, 31u, 31u, 31u };

			World world;
			world.inject(registry);
			world.createChunk({ 0, 0, 0 }, true);
			world.write(util::Query{}.writeRectangle(registry["stone"], { 12, 6, 2 }, { 16, 10, 5 }));
			world.process();

			Assert::AreEqual({ 0u, 0u, 0u, 0u }, readLight(world, { 14, 7, 5 }));
			Assert::AreEqual({ 0u, 0u, 0u, 0u }, readLight(world, { 14, 8, 4 }));

			world.write(util::Query{}.writeRectangle(registry["air"], { 14, 7, 5 }, { 14, 8, 4 }));
			world.process();

			Assert::AreEqual({ 0u, 0u, 0u, 31u }, readLight(world, { 14, 7, 5 }));
			Assert::AreEqual({ 0u, 0u, 0u, 31u }, readLight(world, { 14, 8, 4 }));
		}

	private:
		glm::uvec4 readLight(const World & world, const glm::ivec3 & pos)
		{
			const auto block = world.readBlock(pos);
			const auto color = world.readColor(pos);
			return { color.getColor(), block.getLight() };
		}
	};
}