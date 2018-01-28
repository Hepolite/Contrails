
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

			for (unsigned int i = 0; i < 4u; ++i)
			{
				data::LightPropagationNode node;
				Assert::IsFalse(chunk.pollLightPropagation(node, i));
				chunk.pushLightPropagation({ 42u, 31u }, i);
				Assert::IsTrue(chunk.pollLightPropagation(node, i));
				Assert::IsFalse(chunk.pollLightPropagation(node, i));
				Assert::AreEqual(42u, static_cast<unsigned int>(node.m_index));
				Assert::AreEqual(31u, static_cast<unsigned int>(node.m_light));
			}
		}
		TEST_METHOD(Chunk_pollLight)
		{
			Chunk chunk;

			data::LightPropagationNode node;
			for (unsigned int i = 0; i < 4u; ++i)
				Assert::IsFalse(chunk.pollLightPropagation(node, i));
			chunk.write(42u, data::BlockData{ 1u, 2u }, data::ColorData{ { 3u, 4u, 5u } });
			for (unsigned int i = 0; i < 4u; ++i)
			{
				Assert::IsTrue(chunk.pollLightPropagation(node, i));
				Assert::AreEqual(42u, static_cast<unsigned int>(node.m_index));
				Assert::AreEqual(2u + i, static_cast<unsigned int>(node.m_light));
			}
		}
	};
}