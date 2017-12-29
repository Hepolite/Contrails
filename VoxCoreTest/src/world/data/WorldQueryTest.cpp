
#include "CppUnitTest.h"

#include "world/data/WorldQuery.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace data
	{
		TEST_CLASS(WorldQueryTest)
		{
		public:
			TEST_METHOD(WorldQuery_ctor)
			{
				WorldQuery query;

				Assert::IsTrue(query.empty());
				Assert::AreEqual(0u, query.size());
				Assert::AreEqual(0u, query.memuse());
			}

			TEST_METHOD(WorldQuery_add)
			{
				WorldQuery query;
				ChunkQuery subQuery;
				subQuery.add({ 2u, 0u, 5u }, { 1u, 0u });

				query.add({ -4, 2, 0 }, { 1u, 0u });
				query.add({ 0, 0, 0 }, std::move(subQuery));

				Assert::IsFalse(query.empty());
				Assert::AreEqual(2u, query.size());
				Assert::AreNotEqual(0u, query.memuse());
			}
		};
	}
}