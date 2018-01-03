
#include "CppUnitTest.h"

#include "render/opengl/fbo.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(vaoTest)
		{
		public:
			TEST_METHOD(fbo_ctor)
			{
				fbo fbo;

				Assert::AreNotEqual(0u, fbo.getHandle());
			}

			TEST_METHOD(fbo_bind)
			{
				fbo fboA, fboB;

				Assert::IsTrue(fboA.bind());
				Assert::IsFalse(fboA.bind());
				Assert::IsTrue(fboB.bind());
				Assert::IsFalse(fboB.bind());
			}
			TEST_METHOD(fbo_unbind)
			{
				fbo fboA, fboB;
				fboB.bind();

				Assert::IsFalse(fboA.unbind());
				Assert::IsTrue(fboB.unbind());
				Assert::IsFalse(fboB.unbind());
			}

		private:
			setup::Context m_context;
		};
	}
}