
#include "CppUnitTest.h"

#include "render/opengl/Attribute.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(AttributeTest)
		{
		public:
			TEST_METHOD(Attribute_enable)
			{
				Attribute attrA{ 0u, DataFormat::UNSIGNED_INT, 1, 0u };
				Attribute attrB{ 1u, DataFormat::FLOAT, 3, 4u };
				Attribute attrC{ 0u, DataFormat::DOUBLE, 1, 0u };

				Assert::IsTrue(attrA.enable(4u));
				Assert::IsTrue(attrB.enable(16u));
				Assert::IsTrue(attrC.enable(4u));
			}

		private:
			setup::Context m_context;
		};
	}
}