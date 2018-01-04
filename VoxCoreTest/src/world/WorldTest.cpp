
#include "CppUnitTest.h"

#include "world/detail/data/WorldQuery.h"
#include "world/World.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(WorldTest)
	{
	public:
		TEST_METHOD(World_write)
		{
			World world;
			world.write({ 3, 1, 4 }, data::BlockData{ 4u, 29u }, data::ColorData{ { 1u, 2u, 3u } });

			Assert::AreEqual(4u, world.readBlock({ 3, 1, 4 }).getId());
			Assert::AreEqual(29u, world.readBlock({ 3, 1, 4 }).getLight());
			Assert::AreEqual({ 1u, 2u, 3u }, world.readColor({ 3, 1, 4 }).getColor());
		}
	};
}