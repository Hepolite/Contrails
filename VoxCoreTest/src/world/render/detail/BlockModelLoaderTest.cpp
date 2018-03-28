
#include "CppUnitTest.h"

#include "world/render/detail/BlockModelLoader.h"

#include <glm/Unittest.h>
#include <pugixml/pugixml.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	namespace render
	{
		TEST_CLASS(BlockModelLoaderTest)
		{
		public:
			TEST_METHOD(BlockModelLoader_loadVertices)
			{
				const auto side = ::world::util::SIDE_FRONT;

				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				appendVertex(node, "0 0 0", "0 0 1", "0 0 0", "1 1 1");
				appendVertex(node, "1 0 0", "0 0 1", "1 0 0", "1 1 1");
				appendVertex(node, "0 1 0", "0 0 1", "0 1 0", "1 1 1");

				BlockModelLoader loader;
				loader.loadVertices(node, side);
				const auto model = loader.extractModel();

				Assert::AreEqual(3u, model.m_vertices[side.m_id].size());
				Assert::AreEqual({ 1, 0, 0 }, model.m_vertices[side.m_id][1u].m_position);
				Assert::AreEqual({ 0, 0, 1 }, model.m_vertices[side.m_id][1u].m_normal);
				Assert::AreEqual({ 1, 0, 0 }, model.m_vertices[side.m_id][1u].m_uv);
				Assert::AreEqual({ 1, 1, 1 }, model.m_vertices[side.m_id][1u].m_color);
			}

			TEST_METHOD(BlockModelLoader_loadIndices)
			{
				const auto side = ::world::util::SIDE_FRONT;

				pugi::xml_document doc;
				pugi::xml_node node = doc.append_child("node");
				node.append_child(pugi::node_pcdata).set_value("0 2 1");

				BlockModelLoader loader;
				loader.loadIndices(node, side);
				const auto model = loader.extractModel();

				Assert::AreEqual(3u, model.m_indices[side.m_id].size());
				Assert::AreEqual(0u, model.m_indices[side.m_id][0u]);
				Assert::AreEqual(2u, model.m_indices[side.m_id][1u]);
				Assert::AreEqual(1u, model.m_indices[side.m_id][2u]);
			}

		private:
			void appendVertex(pugi::xml_node & node, const std::string & position, const std::string & normal, const std::string & uv, const std::string & color)
			{
				auto vertex = node.append_child("vertex");
				vertex.append_attribute("position").set_value(position.c_str());
				vertex.append_attribute("normal").set_value(normal.c_str());
				vertex.append_attribute("uv").set_value(uv.c_str());
				vertex.append_attribute("color").set_value(color.c_str());
			}
		};
	}
}