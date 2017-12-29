
#include "CppUnitTest.h"

#include "world/ChunkColumn.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(ChunkColumnTest)
	{
	public:
		TEST_METHOD(ChunkColumn_createChunk)
		{
			ChunkColumn column;
			column.createChunk(2);

			Assert::IsFalse(column.hasChunkAt(1));
			Assert::IsTrue(column.hasChunkAt(2));
		}
		TEST_METHOD(ChunkColumn_deleteChunk)
		{
			ChunkColumn column;
			column.createChunk(-4);
			column.destroyChunk(-4);

			Assert::IsFalse(column.hasChunkAt(-4));
		}

		TEST_METHOD(ChunkColumn_getChunkAt)
		{
			ChunkColumn column;
			column.createChunk(3);

			Assert::IsNull(column.getChunkAt(5));
			Assert::IsNotNull(column.getChunkAt(3));
		}
		TEST_METHOD(ChunkColumn_getChunkAbove)
		{
			ChunkColumn column;
			auto & chunkA = column.createChunk(7);
			auto & chunkB = column.createChunk(-2);

			Assert::IsNull(column.getChunkAbove(7));
			Assert::IsTrue(&chunkA == column.getChunkAbove(6));
			Assert::IsTrue(&chunkA == column.getChunkAbove(-2));
			Assert::IsTrue(&chunkB == column.getChunkAbove(-3));
		}
		TEST_METHOD(ChunkColumn_getChunkBelow)
		{
			ChunkColumn column;
			auto & chunkA = column.createChunk(-4);
			auto & chunkB = column.createChunk(8);

			Assert::IsNull(column.getChunkBelow(-4));
			Assert::IsTrue(&chunkA == column.getChunkBelow(-3));
			Assert::IsTrue(&chunkA == column.getChunkBelow(8));
			Assert::IsTrue(&chunkB == column.getChunkBelow(9));
		}

		TEST_METHOD(ChunkColumn_getOutermostChunks)
		{
			ChunkColumn column;
			auto & chunkA = column.createChunk(3);
			auto & chunkB = column.createChunk(-4);
			auto & chunkC = column.createChunk(8);

			Assert::IsTrue(&chunkB == column.getBottommostChunk());
			Assert::IsTrue(&chunkC == column.getTopmostChunk());
		}
	};
}