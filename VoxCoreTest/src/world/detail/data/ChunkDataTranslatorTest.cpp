
#include "CppUnitTest.h"

#include "world/detail/data/ChunkDataTranslator.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(ChunkDataTranslatorTest)
		{
		public:
			TEST_METHOD(ChunkDataTranslator_expand)
			{
				ChunkDataBloated data;
				data.write(42u, BlockData{ 1u, 6u }, ColorData{ { 0u, 0u, 0u } });
				data.write(43u, BlockData{ 1u, 6u }, ColorData{ { 7u, 8u, 9u } });
				data.write(44u, BlockData{ 2u, 6u }, ColorData{ { 7u, 8u, 9u } });
				data = ChunkDataTranslator::expand(ChunkDataTranslator::compress(data));

				compare({ 0u, 0u }, data.readBlock(0u));
				compare({ 0u, 0u }, data.readBlock(41u));
				compare({ 1u, 6u }, data.readBlock(42u));
				compare({ 1u, 6u }, data.readBlock(43u));
				compare({ 2u, 6u }, data.readBlock(44u));
				compare({ 0u, 0u }, data.readBlock(45u));
				compare({ { 0u, 0u, 0u } }, data.readColor(0u));
				compare({ { 0u, 0u, 0u } }, data.readColor(42u));
				compare({ { 7u, 8u, 9u } }, data.readColor(43u));
				compare({ { 7u, 8u, 9u } }, data.readColor(44u));
				compare({ { 0u, 0u, 0u } }, data.readColor(45u));
			}
			TEST_METHOD(ChunkDataTranslator_compress)
			{
				ChunkDataBloated bloated;
				bloated.write(42u, BlockData{ 1u, 6u }, ColorData{ { 0u, 0u, 0u } });
				bloated.write(43u, BlockData{ 1u, 6u }, ColorData{ { 7u, 8u, 9u } });
				bloated.write(44u, BlockData{ 2u, 6u }, ColorData{ { 7u, 8u, 9u } });
				const auto data = ChunkDataTranslator::compress(bloated);

				compare({ 0u, 0u }, data.readBlock(0u));
				compare({ 0u, 0u }, data.readBlock(41u));
				compare({ 1u, 6u }, data.readBlock(42u));
				compare({ 1u, 6u }, data.readBlock(43u));
				compare({ 2u, 6u }, data.readBlock(44u));
				compare({ 0u, 0u }, data.readBlock(45u));
				compare({ { 0u, 0u, 0u } }, data.readColor(0u));
				compare({ { 0u, 0u, 0u } }, data.readColor(42u));
				compare({ { 7u, 8u, 9u } }, data.readColor(43u));
				compare({ { 7u, 8u, 9u } }, data.readColor(44u));
				compare({ { 0u, 0u, 0u } }, data.readColor(45u));
			}

		private:
			void compare(const BlockData & expected, const BlockData & actual)
			{
				Assert::AreEqual(expected.getId(), actual.getId());
				Assert::AreEqual(expected.getLight(), actual.getLight());
			}
			void compare(const ColorData & expected, const ColorData & actual)
			{
				Assert::AreEqual(expected.getColor(), actual.getColor());
			}
		};
	}
}