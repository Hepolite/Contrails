
#include "CppUnitTest.h"

#include "render/opengl/Program.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(ProgramTest)
		{
		public:
			TEST_METHOD(Program_ctor)
			{
				Program program{ "name" };

				Assert::AreEqual({ "name" }, program.getName());
				Assert::AreNotEqual(0u, program.getHandle());
			}

			TEST_METHOD(Program_attach)
			{
				Program program;

				Assert::IsTrue(program.attach(fragmentShader()));
				Assert::IsTrue(program.attach(vertexShader()));
			}
			TEST_METHOD(Program_link)
			{
				Program programA, programB, programC;
				programA.attach(fragmentShader());
				programA.attach(vertexShader());
				programB.attach(fragmentShader());
				programB.attach(vertexShader("borked code"));

				Assert::IsTrue(programA.link());
				Assert::IsFalse(programB.link());
				Assert::IsFalse(programC.link());
			}

			TEST_METHOD(Program_bind)
			{
				Program programA = program();
				Program programB = program();

				Assert::IsTrue(programA.bind());
				Assert::IsFalse(programA.bind());
				Assert::IsTrue(programB.bind());
				Assert::IsFalse(programB.bind());
			}
			TEST_METHOD(Program_unbind)
			{
				Program programA = program();
				Program programB = program();
				programB.bind();

				Assert::IsFalse(programA.unbind());
				Assert::IsTrue(programB.unbind());
				Assert::IsFalse(programB.unbind());
			}

		private:
			Program program()
			{
				Program program;
				program.attach(fragmentShader());
				program.attach(vertexShader());
				program.link();
				return program;
			}
			Shader fragmentShader(const std::string & code = "void main() { gl_FragColor = vec4(1, 1, 1, 1); }")
			{
				Shader shader{ ShaderType::FRAGMENT };
				shader.compile(code);
				return shader;
			}
			Shader vertexShader(const std::string & code = "void main() { gl_Position = vec4(0, 0, 0, 1); }")
			{
				Shader shader{ ShaderType::VERTEX };
				shader.compile(code);
				return shader;
			}

		private:
			setup::Context m_context;
		};
	}
}