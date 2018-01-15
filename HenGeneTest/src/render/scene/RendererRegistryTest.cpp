
#include "CppUnitTest.h"

#include "render/scene/Renderer.h"
#include "render/scene/RendererRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		bool rendered = false;

		class RendererMock : public Renderer<int>
		{
		public:
			virtual void render(const Time & t, const Time & dt, float pt) const override final
			{
				rendered = true;
			}
		};

		TEST_CLASS(RendererRegistryTest)
		{
		public:
			TEST_METHOD(RendererRegistry_add)
			{
				RendererMock renderer;
				RendererRegistry registry;
				registry.add(&renderer);

				rendered = false;
				registry.render(0.0_s, 0.05_s, 0.0f, RenderPass::SOLID);

				Assert::IsTrue(rendered);
			}

			TEST_METHOD(RendererRegistry_clear)
			{
				RendererMock renderer;
				RendererRegistry registry;
				registry.add(&renderer);
				registry.clear();

				rendered = false;
				registry.render(0.0_s, 0.05_s, 0.0f, RenderPass::SOLID);

				Assert::IsFalse(rendered);
			}
		};
	}
}