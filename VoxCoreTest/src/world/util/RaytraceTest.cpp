
#include "CppUnitTest.h"

#include "world/World.h"
#include "world/util/Raytrace.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace util
	{
		TEST_CLASS(RaytraceTest)
		{
		public:
			TEST_METHOD(Raytrace_ctor)
			{
				World world;
				Raytrace rayA{ world, glm::ivec3{ -2, 0, 2 }, glm::ivec3{ 3, 1, 4 } };
				Raytrace rayB{ world, glm::vec3{ 0.5f, 1.25f, 0.25f }, glm::vec3{ -0.5f, -20.0f, 0.0f } };
				Raytrace rayC{ world, glm::vec3{ -0.5f, 5.31f, -1.05f }, glm::vec3{ -1.0f, -0.0f, 0.0f }, 5.0f };

				Assert::AreEqual({ -1.5f, 0.5f, 2.5f }, rayA.getPos());
				Assert::AreEqual({ 0.5f, 1.25f, 0.25f }, rayB.getPos());
				Assert::AreEqual({ -0.5f, 5.31f, -1.05f }, rayC.getPos());
			}
			TEST_METHOD(Raytrace_isValid)
			{
				World world;
				Raytrace rayA{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 0, 0 } };
				Raytrace rayB{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 1, 0, 0 } };

				Assert::IsFalse(rayA.isValid());
				Assert::IsTrue(rayB.isValid());
				rayB.next();
				Assert::IsFalse(rayB.isValid());
			}

			TEST_METHOD(Raytrace_getPos)
			{
				World world;
				Raytrace ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ -1, 0, 0 } };
				ray.next();

				Assert::AreEqual({ -0.5f, 0.5f, 0.5f }, ray.getPos());
				Assert::AreEqual({ 0.5f, 0.5f, 0.5f }, ray.getOldPos());
				Assert::AreEqual({ -1, 0, 0 }, ray.getBlockPos());
				Assert::AreEqual({ 0, 0, 0 }, ray.getOldBlockPos());
			}
			TEST_METHOD(Raytrace_getBlock)
			{
				World world;
				world.write({ 0, 0, 0 }, data::BlockData{ 2u, 31u });
				world.write({ 0, 1, 0 }, data::BlockData{ 1u, 31u });
				Raytrace ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 1, 0 } };
				ray.next();

				Assert::AreEqual(1u, ray.getBlock());
				Assert::AreEqual(2u, ray.getOldBlock());
			}

			TEST_METHOD(Raytrace_next)
			{
				World world;
				Raytrace ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, -4, -6 } };

				ray.next();
				Assert::AreNotEqual({ 0.5f, 0.5f, 0.5f }, ray.getPos());
			}
			TEST_METHOD(Raytrace_nextPos)
			{
				World world;
				Raytrace ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 4, 0, 1 } };

				Assert::AreEqual({ 1.5f, 0.5f, 0.5f }, ray.nextPos());
				Assert::AreEqual({ 2.5f, 0.5f, 0.5f }, ray.nextPos());
				Assert::AreEqual({ 2.5f, 0.5f, 1.5f }, ray.nextPos());
				Assert::AreEqual({ 3.5f, 0.5f, 1.5f }, ray.nextPos());
				Assert::AreEqual({ 4.5f, 0.5f, 1.5f }, ray.nextPos());
			}
			TEST_METHOD(Raytrace_nextBlockPos)
			{
				World world;
				Raytrace ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ -3, 2, 0 } };

				Assert::AreEqual({ -1, 0, 0 }, ray.nextBlockPos());
				Assert::AreEqual({ -1, 1, 0 }, ray.nextBlockPos());
				Assert::AreEqual({ -2, 1, 0 }, ray.nextBlockPos());
				Assert::AreEqual({ -2, 2, 0 }, ray.nextBlockPos());
				Assert::AreEqual({ -3, 2, 0 }, ray.nextBlockPos());
			}
		};

		TEST_CLASS(RaytraceBresenhamTest)
		{
		public:
			TEST_METHOD(RaytraceBresenham_ctor)
			{
				World world;
				RaytraceBresenham rayA{ world, glm::ivec3{ -2, 0, 2 }, glm::ivec3{ 3, 1, 4 } };
				RaytraceBresenham rayB{ world, glm::vec3{ 0.5f, 1.25f, 0.25f }, glm::vec3{ -0.5f, -20.0f, 0.0f } };
				RaytraceBresenham rayC{ world, glm::vec3{ -0.5f, 5.31f, -1.05f }, glm::vec3{ -1.0f, -0.0f, 0.0f }, 5.0f };

				Assert::AreEqual({ -2, 0, 2 }, rayA.getPos());
				Assert::AreEqual({ 0, 1, 0 }, rayB.getPos());
				Assert::AreEqual({ -1, 5, -2 }, rayC.getPos());
			}
			TEST_METHOD(RaytraceBresenham_isValid)
			{
				World world;
				RaytraceBresenham rayA{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 0, 0 } };
				RaytraceBresenham rayB{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 1, 0, 0 } };

				Assert::IsFalse(rayA.isValid());
				Assert::IsTrue(rayB.isValid());
				rayB.next();
				Assert::IsFalse(rayB.isValid());
			}

			TEST_METHOD(RaytraceBresenham_getPos)
			{
				World world;
				RaytraceBresenham ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ -1, 0, 0 } };
				ray.next();

				Assert::AreEqual({ -1, 0, 0 }, ray.getPos());
				Assert::AreEqual({ 0, 0, 0 }, ray.getOldPos());
			}
			TEST_METHOD(RaytraceBresenham_getBlock)
			{
				World world;
				world.write({ 0, 0, 0 }, data::BlockData{ 2u, 31u });
				world.write({ 0, 1, 0 }, data::BlockData{ 1u, 31u });
				RaytraceBresenham ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, 1, 0 } };
				ray.next();

				Assert::AreEqual(1u, ray.getBlock());
				Assert::AreEqual(2u, ray.getOldBlock());
			}

			TEST_METHOD(RaytraceBresenham_next)
			{
				World world;
				RaytraceBresenham ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 0, -4, -6 } };

				ray.next();
				Assert::AreNotEqual({ 0, 0, 0 }, ray.getPos());
			}
			TEST_METHOD(RaytraceBresenham_nextPos)
			{
				World world;
				RaytraceBresenham ray{ world, glm::ivec3{ 0, 0, 0 }, glm::ivec3{ 5, 0, -2 } };

				Assert::AreEqual({ 1, 0, 0 }, ray.nextPos());
				Assert::AreEqual({ 2, 0, -1 }, ray.nextPos());
				Assert::AreEqual({ 3, 0, -1 }, ray.nextPos());
				Assert::AreEqual({ 4, 0, -2 }, ray.nextPos());
				Assert::AreEqual({ 5, 0, -2 }, ray.nextPos());
			}
		};
	}
}