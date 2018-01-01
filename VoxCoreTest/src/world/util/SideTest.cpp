
#include "CppUnitTest.h"

#include "world/util/Side.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace util
	{
		TEST_CLASS(SideTest)
		{
		public:
			TEST_METHOD(Side_fromName)
			{
				Assert::AreEqual(SIDE_FRONT.m_id, fromName("front").m_id);
				Assert::AreEqual(SIDE_LEFT.m_id, fromName("left").m_id);
				Assert::AreEqual(SIDE_BACK.m_id, fromName("back").m_id);
				Assert::AreEqual(SIDE_RIGHT.m_id, fromName("right").m_id);
				Assert::AreEqual(SIDE_TOP.m_id, fromName("top").m_id);
				Assert::AreEqual(SIDE_BOTTOM.m_id, fromName("bottom").m_id);
				Assert::AreEqual(SIDE_UNKNOWN.m_id, fromName("whatevr").m_id);
			}

			TEST_METHOD(Side_fromNameExt)
			{
				const auto left = fromNameExt("left");
				const auto side = fromNameExt("side");
				const auto all = fromNameExt("all");

				Assert::AreEqual(1u, left.size());
				Assert::AreEqual(4u, side.size());
				Assert::AreEqual(7u, all.size());

				Assert::AreEqual(SIDE_LEFT.m_id, left[0u].m_id);
				Assert::AreEqual(SIDE_FRONT.m_id, side[0u].m_id);
				Assert::AreEqual(SIDE_LEFT.m_id, side[1u].m_id);
				Assert::AreEqual(SIDE_BACK.m_id, side[2u].m_id);
				Assert::AreEqual(SIDE_RIGHT.m_id, side[3u].m_id);
				Assert::AreEqual(SIDE_FRONT.m_id, all[0u].m_id);
				Assert::AreEqual(SIDE_LEFT.m_id, all[1u].m_id);
				Assert::AreEqual(SIDE_BACK.m_id, all[2u].m_id);
				Assert::AreEqual(SIDE_RIGHT.m_id, all[3u].m_id);
				Assert::AreEqual(SIDE_TOP.m_id, all[4u].m_id);
				Assert::AreEqual(SIDE_BOTTOM.m_id, all[5u].m_id);
				Assert::AreEqual(SIDE_UNKNOWN.m_id, all[6u].m_id);
			}
		};
	}
}