
#include "CppUnitTest.h"

#include "world/data/ChunkQuery.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(ChunkQueryTest)
		{
		public:
			TEST_METHOD(ChunkQuery_ctor)
			{
				ChunkQuery query;

				Assert::IsTrue(query.empty());
				Assert::AreEqual(0u, query.size());
				Assert::AreEqual(0u, query.memuse());
			}

			TEST_METHOD(ChunkQuery_add)
			{
				ChunkQuery query;
				query.add({ 3u, 1u, 4u });
				query.add({ 5u, 2u, 2u }, { 5u, 2u, 3u });

				Assert::IsFalse(query.empty());
				Assert::AreEqual(3u, query.size());
				Assert::AreNotEqual(0u, query.memuse());
				Assert::AreEqual({ 3u, 1u, 2u }, query.min());
				Assert::AreEqual({ 5u, 2u, 4u }, query.max());
			}

			TEST_METHOD(ChunkQuery_iteration)
			{
				ChunkQuery query;
				query.add({ 0u, 0u, 6u }, { 2u, 0u });
				query.add({ 0u, 0u, 8u }, { 0u, 0u }); // This data gets overwritten
				query.add({ 0u, 0u, 2u }, { 0u, 0u });
				query.add({ 0u, 0u, 4u }, { 1u, 0u });
				query.add({ 0u, 0u, 8u }, { 3u, 0u });

				Assert::AreEqual(4u, query.size());

				unsigned int i = 0u;
				for (const auto & it : query)
					Assert::AreEqual(i++, it.m_block.getId());
			}
		};
	}
}