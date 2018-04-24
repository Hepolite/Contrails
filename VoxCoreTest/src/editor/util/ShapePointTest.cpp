
#include "CppUnitTest.h"

#include "editor/util/ShapePoint.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(ShapePointTest)
		{
		public:
			TEST_METHOD(ShapePoint_getReadQuery)
			{
				ShapePoint shape;

				Assert::AreEqual(1u, shape.getReadQuery().count());
			}

		private:
			setup::Context m_context;
		};
	}
}