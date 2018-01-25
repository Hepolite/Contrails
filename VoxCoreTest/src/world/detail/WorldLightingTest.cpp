
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
			world.propagateLight();
			
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, 60 }).getLight());
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, 20 }).getLight());
			Assert::AreEqual(data::MAX_BLOCK_LIGHT, world.readBlock({ 0, 0, -20 }).getLight());
		}
		TEST_METHOD(WorldLighting_writeLightBlock)
		{
			Block block{ 1u, "glowblock" };
			block.m_lightEmitted = { 31u, 31u, 31u, 0u };

			World world;
			world.write(util::Query{}.writeBlock(block, { 0, 0, 0 }));
			world.propagateLight();

			Assert::AreEqual({ 30u, 30u, 30u, 31u }, readLight(world, { 1, 0, 0 }));
			Assert::AreEqual({ 30u, 30u, 30u, 31u }, readLight(world, { -1, 0, 0 }));
			Assert::AreEqual({ 30u, 30u, 30u, 31u }, readLight(world, { 0, 1, 0 }));
			Assert::AreEqual({ 30u, 30u, 30u, 31u }, readLight(world, { 0, -1, 0 }));
			Assert::AreEqual({ 30u, 30u, 30u, 31u }, readLight(world, { 0, 0, 1 }));
			Assert::AreEqual({ 30u, 30u, 30u, 30u }, readLight(world, { 0, 0, -1 }));
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