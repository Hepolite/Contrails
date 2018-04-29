
#include "CppUnitTest.h"

#include "editor/util/shapes/ShapeEllipse.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(ShapeEllipseTest)
		{
		public:
			TEST_METHOD(ShapeEllipse_getReadQuery)
			{
				ShapeEllipse shapeA, shapeB, shapeC;
				shapeB.setSize({ 3, 5, 2 });
				shapeC.setSize({ 3, 2, 2 });

				Assert::AreEqual(1u, shapeA.getReadQuery().count());
				Assert::AreEqual(22u, shapeB.getReadQuery().count());
				Assert::AreEqual(12u, shapeC.getReadQuery().count());
			}

		private:
			setup::Context m_context;
		};
	}
}