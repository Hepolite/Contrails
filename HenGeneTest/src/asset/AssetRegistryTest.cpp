
#include "CppUnitTest.h"

#include "asset/AssetRegistry.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	TEST_CLASS(AssetRegistryTest)
	{
	public:
		TEST_METHOD(AssetRegistry_add)
		{
			AssetRegistry registry;

			Asset<int> & assetA = registry.add<int>("name");
			Asset<float> & assetB = registry.add<float>("name");
		}
		TEST_METHOD(AssetRegistry_get)
		{
			unsigned int counter = 0u;

			AssetRegistry registry;
			Asset<int> & asset = registry.add<int>("int");
			asset.m_factory = [&counter]() { counter++; return std::make_unique<int>(0); };

			Ref<int> ref = registry.get<int>("int");
			Ref<int> refCopy = ref;
			Ref<int> refMove = std::move(ref);
			Ref<int> refInvalid = registry.get<int>("nothere");

			Assert::IsTrue(refCopy != nullptr);
			Assert::IsTrue(refInvalid == nullptr);
			Assert::AreEqual(2u, asset.m_references);
			Assert::AreEqual(1u, counter);
		}

		TEST_METHOD(AssetRegistry_has)
		{
			AssetRegistry registry;
			registry.add<int>("asset");

			Assert::IsTrue(registry.has<int>("asset"));
			Assert::IsFalse(registry.has<int>("nothere"));
			Assert::IsFalse(registry.has<float>("asset"));
		}
	};
}