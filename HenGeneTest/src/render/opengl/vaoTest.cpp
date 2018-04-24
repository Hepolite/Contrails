
#include "CppUnitTest.h"

#include "render/opengl/vao.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(vaoTest)
		{
		public:
			TEST_METHOD(vao_ctor)
			{
				vao vao;

				Assert::AreNotEqual(0u, vao.getHandle());
			}

			TEST_METHOD(vao_bind)
			{
				vao vaoA, vaoB;

				Assert::IsTrue(vaoA.bind());
				Assert::IsFalse(vaoA.bind());
				Assert::IsTrue(vaoB.bind());
				Assert::IsFalse(vaoB.bind());
			}
			TEST_METHOD(vao_unbind)
			{
				vao vaoA, vaoB;
				vaoB.bind();

				Assert::IsFalse(vaoA.unbind());
				Assert::IsTrue(vaoB.unbind());
				Assert::IsFalse(vaoB.unbind());
			}

			TEST_METHOD(vao_getBoundHandle)
			{
				vao vao;
				vao.bind();

				Assert::AreEqual(vao.getHandle(), vao::getBoundHandle());
			}

		private:
			setup::Context m_context;
		};
	}
}