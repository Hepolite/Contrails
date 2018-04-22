
#include "CppUnitTest.h"

#include "editor/util/ShapeLine.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(ShapeLineTest)
		{
		public:
			TEST_METHOD(ShapeLine_read)
			{
				ShapeLine shapeA, shapeB, shapeC;
				shapeB.stretch({ 3, 1, 4 }, { 6, 1, 5 });
				shapeC.stretch({ 2, -1, 4 }, { -3, -3, 6 });

				Assert::AreEqual(1u, shapeA.read().count());
				Assert::AreEqual(4u, shapeB.read().count());
				Assert::AreEqual(6u, shapeC.read().count());
			}

		private:
			setup::Context m_context;
		};
	}
}