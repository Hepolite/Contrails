
#include "CppUnitTest.h"

#include "render/world/detail/BlockRenderLoader.h"

#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace world
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
				pugi::xml_document node;
				pugi::xml_node def = node.append_child("default");
				pugi::xml_node defOcclude = def.append_child("occlude");
				defOcclude.append_attribute("right").set_value(true);
				defOcclude.append_attribute("top").set_value(true);
				pugi::xml_node occlude = node.append_child("occlude");
				occlude.append_attribute("front").set_value(true);
				occlude.append_attribute("top").set_value(false);
				occlude.append_attribute("bottom").set_value(true);

				BlockRenderVariantLoader loader;
				data::BlockRender block;
				loader.loadVariant(block, node, def);

				Assert::IsTrue(block.m_occlude[::world::util::SIDE_FRONT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_LEFT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_BACK.m_id]);
				Assert::IsTrue(block.m_occlude[::world::util::SIDE_RIGHT.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_TOP.m_id]);
				Assert::IsTrue(block.m_occlude[::world::util::SIDE_BOTTOM.m_id]);
				Assert::IsFalse(block.m_occlude[::world::util::SIDE_UNKNOWN.m_id]);
			}
		};
	}
}