
#include "CppUnitTest.h"

#include "render/world/BlockRenderRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace world
	{
		TEST_CLASS(BlockRenderRegistryTest)
		{
		public:
			TEST_METHOD(BlockRenderRegistry_access)
			{
				BlockRenderRegistry registry;
				data::BlockRender block;
				block.m_occlude[::world::util::SIDE_BOTTOM.m_id] = true;
				
				registry[2u] = block;

				Assert::IsFalse(registry[2u].m_occlude[::world::util::SIDE_FRONT.m_id]);
				Assert::IsTrue(registry[2u].m_occlude[::world::util::SIDE_BOTTOM.m_id]);
			}
		};
	}
}