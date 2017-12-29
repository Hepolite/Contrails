
#include "CppUnitTest.h"

#include "core/allegro/Allegro.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace core
{
	namespace allegro
	{
		TEST_CLASS(AllegroTest)
		{
		public:
			TEST_METHOD(Allegro_ctor)
			{
				Allegro allegro;

				Assert::IsTrue(allegro.isInitialized());
				Assert::IsFalse(allegro.hasErrors());
			}
		};
	}
}