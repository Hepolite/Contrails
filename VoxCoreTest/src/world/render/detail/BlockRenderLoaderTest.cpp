
#include "CppUnitTest.h"

#include "world/render/detail/BlockRenderLoader.h"

#include <glm/Unittest.h>
#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(BlockRenderLoaderTest)
		{
		public:
		};

		TEST_CLASS(BlockRenderVariantLoaderTest)
		{
		public:
			TEST_METHOD(BlockRenderVariantLoader_loadOcclude)
			{
				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_attribute("front").set_value(true);
				node.append_attribute("top").set_value(false);
				node.append_attribute("bottom").set_value(true);

				BlockRenderVariantLoader loader;
				loader.loadOcclusion(node);
				const auto block = loader.extractBlock();

				Assert::IsTrue(block.m_occlude[::world::util::SIDE_FRONT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_LEFT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_BACK.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_RIGHT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_TOP.m_id]);
				Assert::IsTrue(block.m_occlude[::world::util::SIDE_BOTTOM.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_UNKNOWN.m_id]);
			}
		};
	}
}