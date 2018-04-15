
#include "CppUnitTest.h"

#include "world/detail/data/BlockRegion.h"
#include "world/render/detail/BlockTextureLoader.h"

#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(BlockTextureLoaderTest)
		{
		public:
			TEST_METHOD(BlockTextureLoader_loadDefaultConnection)
			{
				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_attribute("type").set_value("default");

				BlockTextureLoader loader;
				loader.loadConnection(node);
				const auto texture = loader.extractTexture();
				const auto data = texture.m_lookup(m_region, { 0, 0, 0 }, util::SIDE_TOP);

				Assert::AreEqual(texture.m_handle, data.getTexture());
			}

			TEST_METHOD(BlockTextureLoader_loadRandomConnection)
			{
				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_attribute("type").set_value("random");
				node.append_attribute("start").set_value("10");
				node.append_attribute("end").set_value("53");

				BlockTextureLoader loader;
				loader.loadConnection(node);
				const auto texture = loader.extractTexture();
				const auto data = texture.m_lookup(m_region, { 0, 0, 0 }, util::SIDE_TOP);

				Assert::AreEqual(texture.m_handle + 10u, data.getTexture());
				Assert::AreEqual(43u, data.getMeta());
			}

			TEST_METHOD(BlockTextureLoader_loadConnectedConnection)
			{
				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_attribute("type").set_value("connected");
				node.append_attribute("direction").set_value("vertical");
				node.append_attribute("start").set_value("20 21 22 23");
				node.append_attribute("end").set_value("35 36 37 38");

				BlockRegistry registry;
				BlockTextureLoader loader;
				loader.inject(registry);
				loader.loadConnection(node);
				const auto texture = loader.extractTexture();
				const auto data = texture.m_lookup(m_region, { 0, 0, 0 }, util::SIDE_FRONT);

				Assert::AreEqual(texture.m_handle + 20u, data.getTexture());
				Assert::AreEqual(15u, data.getMeta());
			}

		private:
			world::data::BlockRegion m_region;
		};
	}
}