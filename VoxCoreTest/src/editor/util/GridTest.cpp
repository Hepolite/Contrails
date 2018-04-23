
#include "CppUnitTest.h"

#include "editor/util/Grid.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		TEST_CLASS(GridTest)
		{
		public:
			TEST_METHOD(Grid_setPos)
			{
				Grid grid;
				grid.setPos({ 3, -7, 2 });

				Assert::AreEqual({ 3, -7, 2 }, grid.getPos());
			}
			TEST_METHOD(Grid_setSize)
			{
				Grid grid;
				grid.setSize(16.5f);

				Assert::AreEqual(16.5f, grid.getSize());
				Assert::ExpectException<std::invalid_argument>([&grid]() { grid.setSize(0.0f); });
				Assert::ExpectException<std::invalid_argument>([&grid]() { grid.setSize(-1.0f); });
			}
			TEST_METHOD(Grid_setResolution)
			{
				Grid grid;
				grid.setResolution(0.5f);

				Assert::AreEqual(0.5f, grid.getResolution());
				Assert::ExpectException<std::invalid_argument>([&grid]() { grid.setResolution(0.0f); });
				Assert::ExpectException<std::invalid_argument>([&grid]() { grid.setResolution(-1.0f); });
			}
			
			TEST_METHOD(Grid_setVisible)
			{
				Grid gridA, gridB;
				gridA.setVisible(false);
				gridB.setVisible(true);

				Assert::IsFalse(gridA.isVisible());
				Assert::IsTrue(gridB.isVisible());
			}
			TEST_METHOD(Grid_getMesh)
			{
				Grid grid;
				Assert::IsNotNull(grid.getMesh());
			}

		private:
			setup::Context m_context;
		};
	}
}