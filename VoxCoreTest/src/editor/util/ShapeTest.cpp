
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
			ShapeMock() { setName("mock"); }
			~ShapeMock() = default;

			virtual world::data::WorldQuery query(const world::Block & block) const override final
			{
				m_queried = true;
				return {};
			}
			virtual void mesh(Vertices & vertices, Indices & indices) const override final
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
				shapeA.setSize({ 5, -3, 7 });
				shapeB.setSizeX(4);
				shapeC.setSizeY(6);
				shapeD.setSizeZ(-8);

				Assert::AreEqual({ 5, -3, 7 }, shapeA.getSize());
				Assert::AreEqual({ 4, 1, 1 }, shapeB.getSize());
				Assert::AreEqual({ 1, 6, 1 }, shapeC.getSize());
				Assert::AreEqual({ 1, 1, -8 }, shapeD.getSize());
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeX(0); });
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeY(0); });
				Assert::ExpectException<std::invalid_argument>([&shapeA]() { shapeA.setSizeZ(0); });
			}
			TEST_METHOD(Shape_stretch)
			{
				ShapeMock shapeA, shapeB, shapeC, shapeD, shapeE;
				shapeA.stretch({ 0, 0, 0 }, { 1, 2, 3 });
				shapeB.stretch({ 3, 1, 4 }, { 6, 5, 10 });
				shapeC.stretch({ 2, -3, 0 }, { 5, 0, -3 });
				shapeD.stretch({ -3, 0, 4 }, { -10, -1, -2 });
				shapeE.stretch({ 0, 3, -2 }, { 0, 3, -2});

				Assert::AreEqual({ 0, 1, 1 }, shapeA.getPos());
				Assert::AreEqual({ 2, 3, 4 }, shapeA.getSize());
				Assert::AreEqual({ 4, 3, 7 }, shapeB.getPos());
				Assert::AreEqual({ 4, 5, 7 }, shapeB.getSize());
				Assert::AreEqual({ 3, -2, -2 }, shapeC.getPos());
				Assert::AreEqual({ 4, 4, -4 }, shapeC.getSize());
				Assert::AreEqual({ -7, -1, 1 }, shapeD.getPos());
				Assert::AreEqual({ -8, -2, -7 }, shapeD.getSize());
				Assert::AreEqual({ 0, 3, -2 }, shapeE.getPos());
				Assert::AreEqual({ 1, 1, 1 }, shapeE.getSize());
			}
			TEST_METHOD(Shape_getStartAndEnd)
			{
				ShapeMock shapeA, shapeB, shapeC;
				shapeA.setPos({ 3, 1, -4 });
				shapeA.setSize({ 4, 7, 10 });
				shapeB.setPos({ 0, 0, 0 });
				shapeB.setSize({ 5, -7, -4 });
				shapeC.setPos({ -2, 1, 3 });
				shapeC.setSize({ -4, -2, 1 });

				Assert::AreEqual({ 2, -2, -8 }, shapeA.getStart());
				Assert::AreEqual({ 5, 4, 1 }, shapeA.getEnd());
				Assert::AreEqual({ -2, 3, 2 }, shapeB.getStart());
				Assert::AreEqual({ 2, -3, -1 }, shapeB.getEnd());
				Assert::AreEqual({ 0, 2, 3 }, shapeC.getStart());
				Assert::AreEqual({ -3, 1, 3 }, shapeC.getEnd());
			}

			TEST_METHOD(Shape_setDynamic)
			{
				ShapeMock shape;
				shape.setDynamic(true);

				Assert::IsTrue(shape.isDynamic());
			}

			TEST_METHOD(Shape_getReadQuery)
			{
				ShapeMock shape;
				shape.getReadQuery();

				Assert::IsTrue(shape.isQueried());
			}
			TEST_METHOD(Shape_getWriteQuery)
			{
				ShapeMock shape;
				shape.getWriteQuery({ 1u, "stone" });

				Assert::IsTrue(shape.isQueried());
			}

			TEST_METHOD(Shape_getMesh)
			{
				ShapeMock shape;
				Assert::IsNotNull(shape.getMesh());
				Assert::IsTrue(shape.isMeshed());
			}

		private:
			setup::Context m_context;
		};
	}
}