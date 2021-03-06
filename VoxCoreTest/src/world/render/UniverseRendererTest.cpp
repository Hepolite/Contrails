
#include "CppUnitTest.h"

#include "world/render/UniverseRenderer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(UniverseRendererTest)
		{
		public:
			TEST_METHOD(UniverseRenderer_createWorld)
			{
				Universe universe;
				universe.createWorld("world");
				UniverseRenderer renderer;
				renderer.inject(universe);
				renderer.createWorld("world");

				Assert::IsTrue(renderer.hasWorld("world"));
				Assert::IsFalse(renderer.hasWorld("whatever"));
			}
			TEST_METHOD(UniverseRenderer_destroyWorld)
			{
				Universe universe;
				universe.createWorld("world");
				UniverseRenderer renderer;
				renderer.inject(universe);
				renderer.createWorld("world");
				renderer.destroyWorld("world");

				Assert::IsFalse(renderer.hasWorld("world"));
			}
			TEST_METHOD(UniverseRenderer_getWorld)
			{
				Universe universe;
				universe.createWorld("world");
				UniverseRenderer renderer;
				renderer.inject(universe);
				renderer.createWorld("world");

				Assert::IsNotNull(renderer.getWorld("world"));
				Assert::IsNull(renderer.getWorld("whatever"));
			}
		};
	}
}