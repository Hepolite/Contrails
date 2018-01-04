
#include "CppUnitTest.h"

#include "render/opengl/ubo.h"
#include "Setup.h"

#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(uboTest)
		{
		public:
			TEST_METHOD(ubo_ctor)
			{
				ubo ubo{ 2u };

				Assert::AreEqual(2u, ubo.getPort());
				Assert::AreNotEqual(0u, ubo.getHandle());
			}

			TEST_METHOD(ubo_bind)
			{
				ubo uboA{ 0u }, uboB{ 1u };

				Assert::IsTrue(uboA.bind());
				Assert::IsFalse(uboA.bind());
				Assert::IsTrue(uboB.bind());
				Assert::IsFalse(uboB.bind());
			}
			TEST_METHOD(ubo_unbind)
			{
				ubo uboA{ 0u }, uboB{ 1u };
				uboB.bind();

				Assert::IsFalse(uboA.unbind());
				Assert::IsTrue(uboB.unbind());
				Assert::IsFalse(uboB.unbind());
			}

			TEST_METHOD(ubo_build)
			{
				ubo ubo{ 0u };
				ubo.bind();

				Assert::IsTrue(ubo.build());
			}

			TEST_METHOD(ubo_add)
			{
				ubo ubo{ 0u };

				Assert::IsTrue(ubo.add<float>("float"));
				Assert::IsTrue(ubo.add<glm::vec3>("vec3"));
				Assert::IsTrue(ubo.add<glm::mat4>("mat4"));
				Assert::IsFalse(ubo.add<float>("float"));
			}
			TEST_METHOD(ubo_set)
			{
				float floatIn;
				glm::vec3 vecIn;
				glm::mat4 matIn;
				const float floatOut = 42.5f;
				const glm::vec3 vecOut{ 12.5f, -4.005f, 1.0f };
				const glm::mat4 matOut{ 3.14f };

				ubo ubo{ 0u };
				Assert::AreNotEqual(0u, ubo.getHandle());
				ubo.add<float>("float");
				ubo.add<glm::vec3>("vec");
				ubo.add<glm::mat4>("mat");
				Assert::IsTrue(ubo.build());

				Assert::IsTrue(ubo.set("mat", matOut));
				Assert::IsTrue(ubo.set("float", floatOut));
				Assert::IsTrue(ubo.set("vec", vecOut));
				Assert::IsFalse(ubo.set("float", glm::vec3{}));
				Assert::IsFalse(ubo.set("whatever", -4));

				Assert::IsTrue(ubo.get("mat", matIn));
				Assert::IsTrue(ubo.get("vec", vecIn));
				Assert::IsTrue(ubo.get("float", floatIn));
				Assert::IsFalse(ubo.get("float", vecIn));
				Assert::IsFalse(ubo.get("whatever", floatIn));

				Assert::AreEqual(floatOut, floatIn);
				Assert::AreEqual(vecOut, vecIn);
				Assert::AreEqual(matIn, matOut);
			}

		private:
			setup::Context m_context;
		};
	}
}