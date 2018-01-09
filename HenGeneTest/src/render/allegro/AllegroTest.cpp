
#include "CppUnitTest.h"

#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(AllegroTest)
		{
		public:
			TEST_METHOD(Allegro_check)
			{
				Assert::IsTrue(m_context.m_allegro->isInitialized());
				Assert::IsFalse(m_context.m_allegro->hasErrors());
			}

		private:
			setup::Context m_context;
		};
	}
}