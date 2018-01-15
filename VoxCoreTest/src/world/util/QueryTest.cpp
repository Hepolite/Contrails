
#include "CppUnitTest.h"

#include "world/util/Query.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace util
	{
		TEST_CLASS(QueryTest)
		{
		public:
			TEST_METHOD(Query_writeBlock)
			{
				const auto query = Query{}.readBlock({ 1, 3, 4 });

				Assert::AreEqual(1u, query.count());
				Assert::IsTrue(query.has({ 1, 3, 4 }));
			}
			TEST_METHOD(Query_writeRectangle)
			{
				const auto query = Query{}.readRectangle({ 1, 3, 4 }, { -1, 3, 3 });

				Assert::AreEqual(6u, query.count());
				Assert::IsTrue(query.has({ -1, 3, 3 }));
				Assert::IsTrue(query.has({ 0, 3, 3 }));
				Assert::IsTrue(query.has({ 1, 3, 3 }));
				Assert::IsTrue(query.has({ -1, 3, 4 }));
				Assert::IsTrue(query.has({ 0, 3, 4 }));
				Assert::IsTrue(query.has({ 1, 3, 4 }));
			}
		};
	}
}