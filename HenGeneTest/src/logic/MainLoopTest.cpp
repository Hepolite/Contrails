
#include "CppUnitTest.h"

#include "core/MainLoop.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace logic
{
	TEST_CLASS(MainLoopTest)
	{
	public:
		TEST_METHOD(MainLoop_ctor)
		{
			MainLoop loop{ 60.0, 60.0 };

			Assert::IsFalse(loop.running());
		}

		TEST_METHOD(MainLoop_process)
		{
			unsigned int i = 0u;

			MainLoop loop{ 60.0, 60.0 };
			loop.process(
				[&](auto & t, auto & dt) { if (i > 120 || t > 1.0_s) loop.terminate(); else i++; },
				[&](auto & t, auto & dt, auto pt) {}
			);

			Assert::AreEqual(60u, i);
		}

	private:
		setup::Context m_context;
	};
}