
#include "CppUnitTest.h"

#include "render/world/detail/BlockTextureLoader.h"

#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace world
	{
		TEST_CLASS(BlockTextureLoaderTest)
		{
		public:
			TEST_METHOD(BlockTextureLoader_loadConnection)
			{
				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_attribute("type").set_value("default");

				BlockTextureLoader loader;
				loader.loadConnection(node);
				const auto texture = loader.extractTexture();

				Assert::IsFalse(texture.m_lookup == nullptr);
			}
		};
	}
}