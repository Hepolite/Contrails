
#include "CppUnitTest.h"

#include "render/opengl/vbo.h"
#include "Setup.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(vboTest)
		{
		public:
			TEST_METHOD(vbo_ctor)
			{
				vbo vbo;

				Assert::AreNotEqual(0u, vbo.getHandle());
			}

			TEST_METHOD(vbo_bind)
			{
				vbo vboA, vboB;

				Assert::IsTrue(vboA.bind());
				Assert::IsFalse(vboA.bind());
				Assert::IsTrue(vboB.bind());
				Assert::IsFalse(vboB.bind());
			}
			TEST_METHOD(vbo_unbind)
			{
				vbo vboA, vboB;
				vboB.bind();

				Assert::IsFalse(vboA.unbind());
				Assert::IsTrue(vboB.unbind());
				Assert::IsFalse(vboB.unbind());
			}

			TEST_METHOD(vbo_reserve)
			{
				const glm::vec3 data{ 3.14f, 0.5f, 14.05f };

				vbo vbo;
				vbo.bind();

				Assert::IsTrue(vbo.reserve(64u));
				Assert::IsTrue(vbo.reserve(sizeof(data), &data));
			}
			TEST_METHOD(vbo_buffer)
			{
				glm::vec3 vecIn;
				glm::mat4 matIn;
				const glm::vec3 vecOut{ 3.14f, 0.5f, 14.05f };
				const glm::mat4 matOut{ 1.0f };

				vbo vbo;
				vbo.bind();
				Assert::IsTrue(vbo.reserve(sizeof(vecOut) + sizeof(matOut)));

				Assert::IsTrue(vbo.buffer(sizeof(vecOut), &vecOut, 0u));
				Assert::IsTrue(vbo.buffer(sizeof(matOut), &matOut, sizeof(vecOut)));
				Assert::IsTrue(vbo.retrieve(sizeof(vecIn), &vecIn, 0u));
				Assert::IsTrue(vbo.retrieve(sizeof(matIn), &matIn, sizeof(vecOut)));
				Assert::AreEqual(vecOut, vecIn);
				Assert::AreEqual(matOut, matIn);
			}

		private:
			setup::Context m_context;
		};
	}
}