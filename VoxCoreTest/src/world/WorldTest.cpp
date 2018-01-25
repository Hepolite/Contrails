
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