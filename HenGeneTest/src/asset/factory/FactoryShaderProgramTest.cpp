
#include "CppUnitTest.h"

#include "asset/factory/FactoryShaderProgram.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	namespace factory
	{
		TEST_CLASS(LoaderShaderProgramTest)
		{
		public:
			LoaderShaderProgramTest() { initialize(); }
			~LoaderShaderProgramTest() { deinitialize(); }

			TEST_METHOD(LoaderShaderProgram_load)
			{
				const render::uboRegistry registry;
				render::opengl::Program programA;
				render::opengl::Program programB;

				LoaderShaderProgram{}.load(programA, "shaderA.xml", registry);
				LoaderShaderProgram{}.load(programB, "shaderB.xml", registry);

				Assert::IsTrue(programA.bind());
				Assert::IsTrue(programB.bind());
			}

		private:
			void initialize() const
			{
				io::File{ "shaderA.fs" }.write("void main() { gl_FragColor = vec4(1, 1, 1, 1); }");
				io::File{ "shaderA.vs" }.write("void main() { gl_Position = vec4(0, 0, 0, 1); }");
				io::File{ "shaderA.xml" }.write(R"(
					<shader type="vertex" file="shaderA.vs" />
					<shader type="fragment" file="shaderA.fs" />
					)");
				io::File{ "shaderB.xml" }.write(R"(
					<shader type="vertex">
					void main()
					{
						gl_Position = vec4(0, 0, 0, 1);
					}
					</shader>
					<shader type="fragment">
					void main()
					{
						gl_FragColor = vec4(1, 1, 1, 1);
					}
					</shader>
					)");
			}
			void deinitialize() const
			{
				io::File{ "shaderA.fs" }.erase();
				io::File{ "shaderA.vs" }.erase();
				io::File{ "shaderA.xml" }.erase();
				io::File{ "shaderB.xml" }.erase();
			}

			setup::Context m_context;
		};
	}
}