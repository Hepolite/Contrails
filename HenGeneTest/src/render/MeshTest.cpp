
#include "CppUnitTest.h"

#include "render/Mesh.h"
#include "Setup.h"

#include <glm/vec3.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	TEST_CLASS(MeshTest)
	{
	public:
		TEST_METHOD(Mesh_build)
		{
			Mesh<glm::vec3> meshA;
			Mesh<glm::vec3> meshB;
			meshB.getIndiceData() = { 0, 1, 2 };
			meshB.getVertexData() = { { 0, 0, 0 }, { 1, 0, 0 }, { 0, 1, 0 } };

			Assert::IsFalse(meshA.build());
			Assert::IsTrue(meshB.build());
		}

	private:
		setup::Context m_context;
	};
}