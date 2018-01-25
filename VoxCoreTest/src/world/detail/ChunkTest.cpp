
#include "CppUnitTest.h"

#include "world/detail/Chunk.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(ChunkTest)
	{
	public:
		TEST_METHOD(Chunk_setFastUnsafe)
		{
			Chunk chunk;
			chunk.setFastUnsafe(1337u, data::BlockData{ 2u, 3u }, data::ColorData{ { 4u, 5u, 6u } });

			Assert::AreEqual(2u, chunk.readBlock(1337u).getId());
			Assert::AreEqual(3u, chunk.readBlock(1337u).getLight());
			Assert::AreEqual({ 4u, 5u, 6u }, chunk.readColor(1337u).getColor());
		}
		TEST_METHOD(Chunk_write)
		{
			Chunk chunk;
			chunk.write(81u, data::BlockData{ 1u, 31u }, data::ColorData{ { 4u, 7u, 5u } });

			Assert::AreEqual(1u, chunk.readBlock(81u).getId());
			Assert::AreEqual(31u, chunk.readBlock(81u).getLight());
			Assert::AreEqual({ 4u, 7u, 5u }, chunk.readColor(81u).getColor());
		}

		TEST_METHOD(Chunk_pushLight)
		{
			Chunk chunk;
			data::Index propagation, removal;

			Assert::IsFalse(chunk.pollLightPropagation(propagation));
			Assert::IsFalse(chunk.pollLightRemoval(removal));

			chunk.pushLightPropagation(42u);
			chunk.pushLightRemoval(1337u);

			Assert::IsTrue(chunk.pollLightPropagation(propagation));
			Assert::IsTrue(chunk.pollLightRemoval(removal));
			Assert::IsFalse(chunk.pollLightPropagation(propagation));
			Assert::IsFalse(chunk.pollLightRemoval(removal));
			Assert::AreEqual(42u, static_cast<unsigned int>(propagation));
			Assert::AreEqual(1337u, static_cast<unsigned int>(removal));
		}
		TEST_METHOD(Chunk_pollLight)
		{
			Chunk chunk;
			data::Index index;

			Assert::IsFalse(chunk.pollLightPropagation(index));
			chunk.write(42u, data::BlockData{ 1u, 31u }, data::ColorData{ { 0u, 0u, 0u } });
			Assert::IsTrue(chunk.pollLightPropagation(index));

			Assert::IsFalse(chunk.pollLightRemoval(index));
			chunk.write(42u, data::BlockData{ 0u, 0u }, data::ColorData{ { 0u, 0u, 0u } });
			Assert::IsTrue(chunk.pollLightRemoval(index));
		}
	};
}