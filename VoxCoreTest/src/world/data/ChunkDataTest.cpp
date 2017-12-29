
#include "CppUnitTest.h"

#include "world/data/ChunkData.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(ChunkDataBloatedTest)
		{
		public:
			TEST_METHOD(ChunkDataBloated_write)
			{
				ChunkDataBloated data;
				BlockData block{ 1u, 5u };
				ColorData color{ { 4u, 2u, 8u } };

				data.write(42u, block, color);

				Assert::AreEqual(0u, block.getId());
				Assert::AreEqual(0u, block.getLight());
				Assert::AreEqual({ 0u, 0u, 0u }, color.getColor());

				data.read(42u, block, color);

				Assert::AreEqual(1u, block.getId());
				Assert::AreEqual(5u, block.getLight());
				Assert::AreEqual({ 4u, 2u, 8u }, color.getColor());
			}

			TEST_METHOD(ChunkDataBloated_pushLight)
			{
				ChunkDataBloated data;
				Index propagation, removal;

				Assert::IsFalse(data.pollLightPropagation(propagation));
				Assert::IsFalse(data.pollLightRemoval(removal));

				data.pushLightPropagation(42u);
				data.pushLightRemoval(1337u);

				Assert::IsTrue(data.pollLightPropagation(propagation));
				Assert::IsTrue(data.pollLightRemoval(removal));
				Assert::IsFalse(data.pollLightPropagation(propagation));
				Assert::IsFalse(data.pollLightRemoval(removal));
				Assert::AreEqual(42u, static_cast<unsigned int>(propagation));
				Assert::AreEqual(1337u, static_cast<unsigned int>(removal));
			}
			TEST_METHOD(ChunkDataBloated_setLight)
			{
				ChunkDataBloated data;
				Index index;

				Assert::IsFalse(data.pollLightPropagation(index));
				data.write(42u, BlockData{ 1u, 31u }, ColorData{ { 0u, 0u, 0u } });
				Assert::IsTrue(data.pollLightPropagation(index));

				Assert::IsFalse(data.pollLightRemoval(index));
				data.write(42u, BlockData{ 0u, 0u }, ColorData{ { 0u, 0u, 0u } });
				Assert::IsTrue(data.pollLightRemoval(index));
			}
		};

		TEST_CLASS(ChunkDataCompressedTest)
		{
		public:
			// ...
		};
	}
}