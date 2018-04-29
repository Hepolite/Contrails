
#include "CppUnitTest.h"

#include "editor/util/shapes/ShapeCylinder.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(ShapeCylinderTest)
		{
		public:
			TEST_METHOD(ShapeCylinder_setAxis)
			{
				ShapeCylinder shape;
				shape.setAxis(math::Axis::Y);
				
				Assert::IsTrue(math::Axis::Y == shape.getAxis());
			}

			TEST_METHOD(ShapeCylinder_getReadQuery)
			{
				ShapeCylinder shapeA, shapeB, shapeC;
				shapeB.setSize({ 2, 2, 3 });
				shapeC.setSize({ 5, 1, 3 });
				shapeC.setAxis(math::Axis::Y);

				Assert::AreEqual(1u, shapeA.getReadQuery().count());
				Assert::AreEqual(12u, shapeB.getReadQuery().count());
				Assert::AreEqual(11u, shapeC.getReadQuery().count());
			}

		private:
			setup::Context m_context;
		};
	}
}