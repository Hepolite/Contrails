
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
			TEST_METHOD(Query_readBlock)
			{
				const auto query = Query{}.readBlock({ 1, 3, 4 });

				Assert::AreEqual(1u, query.count());
				Assert::IsTrue(query.has({ 1, 3, 4 }));
			}
			TEST_METHOD(Query_testCylinder)
			{
				const auto queryA = Query{}.readCylinder({ 1, 3, 5 }, { -1, 4, 5 }, math::Axis::Z);
				const auto queryB = Query{}.readCylinder({ 1, 3, 5 }, { -1, 3, 3 }, math::Axis::Y);
				const auto queryC = Query{}.readCylinder({ 1, -1, 5 }, { 1, 3, 1 }, math::Axis::X);

				Assert::AreEqual(6u, queryA.count());
				Assert::IsTrue(queryA.has({ -1, 3, 5 }));
				Assert::IsTrue(queryA.has({ -1, 4, 5 }));
				Assert::IsTrue(queryA.has({ 0, 3, 5 }));
				Assert::IsTrue(queryA.has({ 0, 4, 5 }));
				Assert::IsTrue(queryA.has({ 1, 3, 5 }));
				Assert::IsTrue(queryA.has({ 1, 4, 5 }));

				Assert::AreEqual(9u, queryB.count());
				Assert::IsTrue(queryB.has({ -1, 3, 4 }));
				Assert::IsTrue(queryB.has({ 0, 3, 3 }));
				Assert::IsTrue(queryB.has({ 0, 3, 4 }));
				Assert::IsTrue(queryB.has({ 0, 3, 5 }));
				Assert::IsTrue(queryB.has({ 1, 3, 4 }));

				Assert::AreEqual(21u, queryC.count());
			}
			TEST_METHOD(Query_readRectangle)
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
			TEST_METHOD(Query_readLine)
			{
				const auto query = Query{}.readLine({ -2, 2, 1 }, { 5, -1, 0 });

				Assert::AreEqual(8u, query.count());
				Assert::IsTrue(query.has({ -2, 2, 1 }));
				Assert::IsTrue(query.has({ -1, 2, 1 }));
				Assert::IsTrue(query.has({ 0, 1, 1 }));
				Assert::IsTrue(query.has({ 1, 1, 1 }));
				Assert::IsTrue(query.has({ 2, 0, 0 }));
				Assert::IsTrue(query.has({ 3, 0, 0 }));
				Assert::IsTrue(query.has({ 4, -1, 0 }));
				Assert::IsTrue(query.has({ 5, -1, 0 }));
			}
		};
	}
}