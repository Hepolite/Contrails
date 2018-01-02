
#include "CppUnitTest.h"

#include "render/world/WorldRenderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace world
	{
		TEST_CLASS(WorldRendererTest)
		{
		public:
			TEST_METHOD(WorldRenderer_load)
			{
				WorldRenderer renderer;
				Assert::ExpectException<std::exception>([&renderer]() { renderer.load(""); });

				::world::BlockRegistry registry;
				renderer.injectBlockRegistry(registry);
				renderer.load("");
			}
		};
	}
}