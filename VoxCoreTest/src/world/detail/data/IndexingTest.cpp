
#include "CppUnitTest.h"

#include "world/detail/data/Indexing.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(IndexingTest)
		{
		public:
			TEST_METHOD(Indexing_limit)
			{
				static_assert(MAX_CHUNK_SIZE <= 32u, "Chunk size bigger than 32 blocks is not supported");
			}

			TEST_METHOD(Indexing_toIndex)
			{
				if (CHUNK_SIZE<unsigned int> == 32u)
				{
					Assert::AreEqual(31780u, static_cast<unsigned int>(toIndex<unsigned int>({ 4u, 1u, 31u })));
					Assert::AreEqual(425u, static_cast<unsigned int>(toIndex<int>({ 9, 13, 0 })));
				}
				else
					Assert::Fail();

				Assert::AreEqual(42, static_cast<int>(toIndex<int>({ 0, 7, 1 }, { 3, 7, 2 })));
			}

			TEST_METHOD(Indexing_toPos)
			{
				if (CHUNK_SIZE<unsigned int> == 32u)
				{
					Assert::AreEqual({ 4u, 15u, 27u }, toPos<unsigned int>(28132u));
					Assert::AreEqual({ 29, 31, 17 }, toPos<int>(18429u));
				}
				else
					Assert::Fail();
			}
		};
	}
}