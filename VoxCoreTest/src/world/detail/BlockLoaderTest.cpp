
#include "CppUnitTest.h"

#include "world/detail/BlockLoader.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(BlockLoaderTest)
	{
	public:
		BlockLoaderTest() { file.write(R"( <variant /> <variant name="foo" /> <variant name="bar" /> )"); }
		~BlockLoaderTest() { file.erase(); }

		TEST_METHOD(BlockLoader_loadBlock)
		{
			BlockRegistry registry;
			BlockLoader loader;
			loader.inject(registry);

			loader.loadBlock(file);

			Assert::AreEqual({ "block" }, registry["block"].m_name);
			Assert::AreEqual({ "block:foo" }, registry["block:foo"].m_name);
			Assert::AreEqual({ "block:bar" }, registry["block:bar"].m_name);
		}

	private:
		const io::File file{ "block.xml" };
	};

	TEST_CLASS(BlockVariantLoaderTest)
	{
	public:
		TEST_METHOD(BlockVariantLoader_loadPhase)
		{
			pugi::xml_document node;
			pugi::xml_node light = node.append_child("phase");
			light.append_attribute("type").set_value("liquid");

			BlockVariantLoader loader;
			Block block;
			loader.loadPhase(block, light);

			Assert::IsTrue(block.m_phase == BlockPhase::LIQUID);
		}
		TEST_METHOD(BlockVariantLoader_loadLight)
		{
			pugi::xml_document node;
			pugi::xml_node light = node.append_child("light");
			light.append_attribute("emit").set_value("2 10 7 0");
			light.append_attribute("absorb").set_value("9 5 8 6");
			light.append_attribute("filter").set_value("0 1 4 3");

			BlockVariantLoader loader;
			Block block;
			loader.loadLight(block, light);

			Assert::AreEqual({ 2u, 10u, 7u, 0u }, block.m_lightEmitted);
			Assert::AreEqual({ 9u, 5u, 8u, 6u }, block.m_lightAbsorbed);
			Assert::AreEqual({ 0u, 1u, 4u, 3u }, block.m_lightFiltered);
		}
	};
}