
#include "CppUnitTest.h"

#include "editor/util/Shape.h"
#include "Setup.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace editor
{
	namespace util
	{
		class ShapeMock : public Shape
		{
		public:
			virtual world::data::WorldQuery query(const world::Block & block) const override final
			{
				m_queried = true;
				return {};
			}
			virtual void mesh(std::vector<glm::vec3> & vertices, std::vector<unsigned int> & indices) const override final
			{
				m_meshed = true;
			}

			inline auto getStart() const { return Shape::getStart(); }
			inline auto getEnd() const { return Shape::getEnd(); }

			inline auto isQueried() const { return m_queried; }
			inline auto isMeshed() const { return m_meshed; }

		private:
			mutable bool m_queried = false;
			mutable bool m_meshed = false;
		};

		TEST_CLASS(ShapeTest)
		{
		public:
			TEST_METHOD(Shape_setPos)
			{
				ShapeMock shape;
				shape.setPos({ 3, -7, 2 });

				Assert::AreEqual({ 3, -7, 2 }, shape.getPos());
			}
			TEST_METHOD(Shape_setSize)
			{
				ShapeMock shapeA, shapeB, shapeC, shapeD;
				shapeA.setSize({ 5, 3, 7 });
				shapeB.setSizeX(4);
				shapeC.setSizeY(6);
				shapeD.setSizeZ(8);

				Assert::AreEqual({ 5, 3, 7 }, shapeA.getSize());
				Assert::AreEqual({ 4, 1, 1 }, shapeB.getSize());
				Assert::AreEqual({ 1, 6, 1 }, shapeC.getSize());
				Assert::AreEqual({ 1, 1, 8 }, shapeD.getSize());
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeX(0); });
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeY(0); });
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeZ(0); });
				Assert::IsTrue(shapeA.isMeshed());
				Assert::IsTrue(shapeB.isMeshed());
				Assert::IsTrue(shapeC.isMeshed());
				Assert::IsTrue(shapeD.isMeshed());
			}
			TEST_METHOD(Shape_getStartAndEnd)
			{
				ShapeMock shape;
				shape.setPos({ 3, 1, -4 });
				shape.setSize({ 4, 7, 10 });

				Assert::AreEqual({ 1, -2, -9 }, shape.getStart());
				Assert::AreEqual({ 4, 4, 0 }, shape.getEnd());
			}

			TEST_METHOD(Shape_setDynamic)
			{
				ShapeMock shape;
				shape.setDynamic(true);

				Assert::IsTrue(shape.isDynamic());
			}

			TEST_METHOD(Shape_read)
			{
				ShapeMock shape;
				shape.read();

				Assert::IsTrue(shape.isQueried());
			}
			TEST_METHOD(Shape_write)
			{
				ShapeMock shape;
				shape.write({ 1u, "stone" });

				Assert::IsTrue(shape.isQueried());
			}

		private:
			setup::Context m_context;
		};
	}
}