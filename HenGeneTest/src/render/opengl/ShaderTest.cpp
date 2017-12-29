
#include "CppUnitTest.h"

#include "render/opengl/Shader.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(ShaderTest)
		{
		public:
			TEST_METHOD(Shader_ctor)
			{
				Shader shader{ ShaderType::VERTEX };

				Assert::AreNotEqual(0u, shader.getHandle());
			}

			TEST_METHOD(Shader_compile)
			{
				Shader shaderF{ ShaderType::FRAGMENT };
				Shader shaderV{ ShaderType::VERTEX };

				Assert::IsFalse(shaderF.compile(""));
				Assert::IsFalse(shaderF.compile("void main() { malformed code"));
				Assert::IsTrue(shaderF.compile("void main() { gl_FragColor = vec4(1, 1, 1, 1); }"));
				Assert::IsTrue(shaderV.compile("void main() { gl_Position = vec4(0, 0, 0, 1); }"));
			}

		private:
			setup::Context m_context;
		};
	}
}