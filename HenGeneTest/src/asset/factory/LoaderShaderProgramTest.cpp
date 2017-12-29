
#include "CppUnitTest.h"

#include "asset/factory/LoaderShaderProgram.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	TEST_CLASS(LoaderShaderProgramTest)
	{
	public:
		LoaderShaderProgramTest() { initialize(); }
		~LoaderShaderProgramTest() { deinitialize(); }

		TEST_METHOD(LoaderShaderProgram_load)
		{
			render::opengl::Program program;
			const render::uboRegistry registry;

			util::LoaderShaderProgram{}.load(program, "shader.xml", registry);

			Assert::IsTrue(program.bind());
		}

	private:
		void initialize() const
		{
			io::File{ "shader.fs" }.write("void main() { gl_FragColor = vec4(1, 1, 1, 1); }");
			io::File{ "shader.vs" }.write("void main() { gl_Position = vec4(0, 0, 0, 1); }");
			io::File{ "shader.xml" }.write(R"(
				<shader type="vertex">
					<file>shader.vs</file>
				</shader>
				<shader type="fragment">
					<file>shader.fs</file>
				</shader>
			)");
		}
		void deinitialize() const
		{
			io::File{ "shader.fs" }.erase();
			io::File{ "shader.vs" }.erase();
			io::File{ "shader.xml" }.erase();
		}

		setup::Context m_context;
	};
}