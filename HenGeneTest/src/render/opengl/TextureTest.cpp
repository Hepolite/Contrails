
#include "CppUnitTest.h"

#include "render/opengl/Texture.h"
#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace opengl
	{
		TEST_CLASS(TextureTest)
		{
		public:
			TEST_METHOD(Texture_ctor)
			{
				Texture texture{ TextureType::TEXTURE_2D };

				Assert::AreNotEqual(0u, texture.getHandle());
			}

			TEST_METHOD(Texture_bind)
			{
				Texture textureA{ TextureType::TEXTURE_2D };
				Texture textureB{ TextureType::TEXTURE_2D };

				Assert::IsTrue(textureA.bind());
				Assert::IsFalse(textureA.bind());
				Assert::IsTrue(textureB.bind());
				Assert::IsFalse(textureB.bind());
			}
			TEST_METHOD(Texture_unbind)
			{
				Texture textureA{ TextureType::TEXTURE_2D };
				Texture textureB{ TextureType::TEXTURE_2D };
				textureB.bind();

				Assert::IsFalse(textureA.unbind());
				Assert::IsTrue(textureB.unbind());
				Assert::IsFalse(textureB.unbind());
			}

		private:
			setup::Context m_context;
		};
	}
}