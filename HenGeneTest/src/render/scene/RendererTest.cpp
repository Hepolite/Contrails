
#include "CppUnitTest.h"

#include "render/scene/Renderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		class RendererMock : public Renderer<int>
		{
		public:
			virtual void render(const Time & t, const Time & dt, float pt) const override final {}
		};

		TEST_CLASS(RendererTest)
		{
		public:
			TEST_METHOD(Renderer_setVisibleToCamera)
			{
				RendererMock renderer;
				renderer.setVisibleToCamera(CameraType::NORMAL, true);
				renderer.setVisibleToCamera(CameraType::MIRROR, false);
				
				Assert::IsTrue(renderer.isVisibleToCamera(CameraType::NORMAL));
				Assert::IsFalse(renderer.isVisibleToCamera(CameraType::MIRROR));
			}
		};
	}
}