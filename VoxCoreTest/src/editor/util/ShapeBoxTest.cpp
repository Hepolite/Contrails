
#include "CppUnitTest.h"

#include "editor/util/ShapeBox.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(ShapeBoxTest)
		{
		public:
			TEST_METHOD(ShapeBox_getReadQuery)
			{
				ShapeBox shapeA, shapeB, shapeC;
				shapeB.setSize({ 2, 2, 3 });
				shapeC.setSize({ 10, 1, 1 });
				
				Assert::AreEqual(1u, shapeA.getReadQuery().count());
				Assert::AreEqual(12u, shapeB.getReadQuery().count());
				Assert::AreEqual(10u, shapeC.getReadQuery().count());
			}

		private:
			setup::Context m_context;
		};
	}
}