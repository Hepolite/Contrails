
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"
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
	};
}