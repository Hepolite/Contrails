
#include "CppUnitTest.h"

#include "world/render/detail/meshing/ChunkMesher.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(ChunkMesherTest)
		{
		public:
			TEST_METHOD(ChunkMesher_finish)
			{
				ChunkMeshTask taskA{ { 3, 1, 4 }, {}, nullptr };
				ChunkMeshTask taskB{};
				ChunkMesher mesher;
				mesher.schedule(std::move(taskA));
				mesher.finish();
				mesher.extract(taskB);

				Assert::AreEqual({ 3, 1, 4 }, taskB.m_cpos);
			}
		};
	}
}