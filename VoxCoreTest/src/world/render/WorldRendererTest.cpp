
#include "CppUnitTest.h"

#include "Setup.h"
#include "world/render/WorldRenderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(WorldRendererTest)
		{
		public:
			TEST_METHOD(WorldRenderer_chunkCreateAndDestroy)
			{
				logic::event::EventBus bus;
				World world;
				world.inject(bus);
				WorldRenderer renderer;
				renderer.inject(bus);
				renderer.inject(world);

				// 26 surrounding chunks are automatically created
				world.createChunk({ 0, 0, 0 });
				Assert::AreEqual(27u, renderer.size());
				// 26 surrounding chunks are automatically destroyed
				world.destroyChunk({ 0, 0, 0 });
				Assert::AreEqual(0u, renderer.size());
			}

		private:
			setup::Context m_context;
		};
	}
}