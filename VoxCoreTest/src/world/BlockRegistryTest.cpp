
#include "CppUnitTest.h"

#include "world/BlockRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace world
{
	TEST_CLASS(BlockRegistryTest)
	{
	public:
		TEST_METHOD(BlockRegistry_ctor)
		{
			BlockRegistry registry;

			Assert::AreEqual(1u, registry.size());
		}

		TEST_METHOD(BlockRegistry_add)
		{
			BlockRegistry registry;
			
			auto stone = registry.add("stone");
			auto grass = registry.add("grass", 3u);
			auto dirt = registry.add("dirt");

			Assert::AreEqual(4u, registry.size());

			Assert::AreEqual(1u, stone.m_id);
			Assert::AreEqual({ "stone" }, stone.m_name);
			Assert::AreEqual(2u, dirt.m_id);
			Assert::AreEqual({ "dirt" }, dirt.m_name);
			Assert::AreEqual(3u, grass.m_id);
			Assert::AreEqual({ "grass" }, grass.m_name);

			Assert::ExpectException<std::invalid_argument>([&registry]() { registry.add("air"); });
			Assert::ExpectException<std::invalid_argument>([&registry]() { registry.add("whatever", 0u); });
			Assert::ExpectException<std::invalid_argument>([&registry]() { registry.add("whatever", 4096u); });
		}

		TEST_METHOD(BlockRegistry_get)
		{
			BlockRegistry registry;
			registry.add("stone");
			registry.add("dirt");
			registry.add("grass");

			Assert::AreEqual(0u, registry["air"].m_id);
			Assert::AreEqual({ "air" }, registry["air"].m_name);
			Assert::AreEqual(1u, registry["stone"].m_id);
			Assert::AreEqual({ "stone" }, registry["stone"].m_name);
			Assert::AreEqual(2u, registry["dirt"].m_id);
			Assert::AreEqual({ "dirt" }, registry["dirt"].m_name);
			Assert::AreEqual(3u, registry["grass"].m_id);
			Assert::AreEqual({ "grass" }, registry["grass"].m_name);

			Assert::AreEqual(0u, registry[5u].m_id);
			Assert::AreEqual({ "air" }, registry["invalid"].m_name);
		}
	};
}