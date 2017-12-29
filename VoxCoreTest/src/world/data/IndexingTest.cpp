
#include "CppUnitTest.h"

#include "world/data/Indexing.h"

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
				static_assert(MAX_CHUNK_SIZE <= 32u, "Chunks bigger than 32 blocks are not supported");
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