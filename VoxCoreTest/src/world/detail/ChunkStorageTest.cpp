
#include "CppUnitTest.h"

#include "world/detail/ChunkStorage.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(ChunkStorageTest)
	{
	public:
		TEST_METHOD(ChunkStorage_createChunk)
		{
			ChunkStorage storage;

			Assert::IsFalse(storage.hasChunkAt({ 0, 0, 0 }));
			storage.createChunk({ 0, 0, 0 });
			Assert::IsTrue(storage.hasChunkAt({ 0, 0, 0 }));
		}
		TEST_METHOD(ChunkStorage_createOrGetChunk)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createOrGetChunk({ 0, 0, 0 });
			auto & chunkB = storage.createOrGetChunk({ 0, 0, 0 });

			Assert::IsTrue(&chunkA == &chunkB);
		}
		TEST_METHOD(ChunkStorage_destroyChunk)
		{
			ChunkStorage storage;
			storage.createChunk({ 0, 0, 0 });

			Assert::IsTrue(storage.hasChunkAt({ 0, 0, 0 }));
			storage.destroyChunk({ 0, 0, 0 });
			Assert::IsFalse(storage.hasChunkAt({ 0, 0, 0 }));
		}

		TEST_METHOD(ChunkStorage_hasChunkAt)
		{
			ChunkStorage storage;
			storage.createChunk({ 0, 0, 0 });

			Assert::IsTrue(storage.hasChunkAt({ 0, 0, 0 }));
			Assert::IsFalse(storage.hasChunkAt({ 0, 0, 1 }));
			Assert::IsFalse(storage.hasChunkAt({ 0, -1, 0 }));
		}
		TEST_METHOD(ChunkStorage_getChunkAt)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createChunk({ 0, 0, 0 });
			auto & chunkB = storage.createChunk({ 1, 0, 0 });

			Assert::IsTrue(&chunkA == storage.getChunkAt({ 0, 0, 0 }));
			Assert::IsTrue(&chunkB == storage.getChunkAt({ 1, 0, 0 }));
		}
		TEST_METHOD(ChunkStorage_getChunkAbove)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createChunk({ 0, 0, -4 });
			auto & chunkB = storage.createChunk({ 0, 0, 1 });
			auto & chunkC = storage.createChunk({ 0, 0, 9 });

			Assert::IsTrue(&chunkA == storage.getChunkAbove({ 0, 0, -5 }));
			Assert::IsTrue(&chunkB == storage.getChunkAbove({ 0, 0, -4 }));
			Assert::IsTrue(&chunkC == storage.getChunkAbove({ 0, 0, 3 }));
			Assert::IsNull(storage.getChunkAbove({ 0, 0, 9 }));
		}
		TEST_METHOD(ChunkStorage_getChunkBelow)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createChunk({ 0, 0, -4 });
			auto & chunkB = storage.createChunk({ 0, 0, 1 });
			auto & chunkC = storage.createChunk({ 0, 0, 9 });

			Assert::IsTrue(&chunkA == storage.getChunkBelow({ 0, 0, -3 }));
			Assert::IsTrue(&chunkB == storage.getChunkBelow({ 0, 0, 9 }));
			Assert::IsTrue(&chunkC == storage.getChunkBelow({ 0, 0, 161 }));
			Assert::IsNull(storage.getChunkBelow({ 0, 0, -4 }));
		}
		TEST_METHOD(ChunkStorage_getChunkPosAbove)
		{
			ChunkStorage storage;
			storage.createChunk({ 0, 0, -4 });
			storage.createChunk({ 0, 0, 1 });
			storage.createChunk({ 0, 0, 9 });

			Assert::AreEqual({ 0, 0, -4 }, storage.getChunkPosAbove({ 0, 0, -5 }));
			Assert::AreEqual({ 0, 0, 1 }, storage.getChunkPosAbove({ 0, 0, -4 }));
			Assert::AreEqual({ 0, 0, 9 }, storage.getChunkPosAbove({ 0, 0, 3 }));
			Assert::AreEqual({ 0, 0, std::numeric_limits<int>::max() }, storage.getChunkPosAbove({ 0, 0, 9 }));
		}
		TEST_METHOD(ChunkStorage_getChunkPosBelow)
		{
			ChunkStorage storage;
			storage.createChunk({ 0, 0, -4 });
			storage.createChunk({ 0, 0, 1 });
			storage.createChunk({ 0, 0, 9 });

			Assert::AreEqual({ 0, 0, -4 }, storage.getChunkPosBelow({ 0, 0, -3 }));
			Assert::AreEqual({ 0, 0, 1 }, storage.getChunkPosBelow({ 0, 0, 9 }));
			Assert::AreEqual({ 0, 0, 9 }, storage.getChunkPosBelow({ 0, 0, 161 }));
			Assert::AreEqual({ 0, 0, std::numeric_limits<int>::min() }, storage.getChunkPosBelow({ 0, 0, -4 }));
		}

		TEST_METHOD(ChunkStorage_getOutermostChunks)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createChunk({ 0, 0, -4 });
			auto & chunkB = storage.createChunk({ 0, 0, 1 });
			auto & chunkC = storage.createChunk({ 0, 0, 9 });

			Assert::IsTrue(&chunkA == storage.getBottommostChunk({ 0, 0 }));
			Assert::IsTrue(&chunkC == storage.getTopmostChunk({ 0, 0 }));
		}
		TEST_METHOD(ChunkStorage_getOutermostChunkPos)
		{
			ChunkStorage storage;
			auto & chunkA = storage.createChunk({ 0, 0, -4 });
			auto & chunkB = storage.createChunk({ 0, 0, 1 });
			auto & chunkC = storage.createChunk({ 0, 0, 9 });

			Assert::AreEqual({ 0, 0, -4 }, storage.getBottommostChunkPos({ 0, 0 }));
			Assert::AreEqual({ 0, 0, 9 }, storage.getTopmostChunkPos({ 0, 0 }));
		}
	};
}