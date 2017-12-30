
#include "CppUnitTest.h"

#include "world/Chunk.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(ChunkTest)
	{
	public:
		TEST_METHOD(Chunk_write)
		{
			Chunk chunk;
			data::BlockData block{ 1u, 31u };
			data::ColorData color{ { 4u, 7u, 5u } };

			chunk.write({ 3u, 1u, 4u }, block, color);

			Assert::AreEqual(0u, block.getId());
			Assert::AreEqual(0u, block.getLight());
			Assert::AreEqual({ 0u, 0u, 0u }, color.getColor());

			chunk.read({ 3u, 1u, 4u }, block, color);

			Assert::AreEqual(1u, block.getId());
			Assert::AreEqual(31u, block.getLight());
			Assert::AreEqual({ 4u, 7u, 5u }, color.getColor());
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
	};
}