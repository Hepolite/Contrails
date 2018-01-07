
#include "CppUnitTest.h"

#include "asset/AssetRef.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace asset
{
	TEST_CLASS(AssetRefTest)
	{
	public:
		TEST_METHOD(AssetRef_ctor)
		{
			Asset<int> asset;
			Ref<int> ref{ &asset };

			Assert::AreEqual(1u, asset.m_references);
		}
		TEST_METHOD(AssetRef_ctorCopy)
		{
			Asset<int> asset;
			Ref<int> refA{ &asset };
			Ref<int> refB{ refA };

			Assert::AreEqual(2u, asset.m_references);
		}
		TEST_METHOD(AssetRef_dtor)
		{
			Asset<int> asset;
			asset.m_factory = []() {return std::make_unique<int>(0); };

			{ Ref<int> ref{ &asset }; }

			Assert::AreEqual(0u, asset.m_references);
			Assert::IsNull(asset.m_handle.get());
		}
		TEST_METHOD(AssetRef_copy)
		{
			Asset<int> assetA, assetB;
			Ref<int> refA{ &assetA };
			Ref<int> refB{ &assetB };
			
			refA = refB;

			Assert::AreEqual(0u, assetA.m_references);
			Assert::AreEqual(2u, assetB.m_references);
		}
		TEST_METHOD(AssetRef_move)
		{
			Asset<int> assetA, assetB;
			Ref<int> refA{ &assetA };
			Ref<int> refB{ &assetB };

			refA = std::move(refB);

			Assert::AreEqual(0u, assetA.m_references);
			Assert::AreEqual(1u, assetB.m_references);
		}

		TEST_METHOD(AssetRef_get)
		{
			Asset<int> asset;
			asset.m_factory = []() { return std::make_unique<int>(42); };

			Ref<int> ref{ &asset };

			Assert::AreEqual(42, *ref);
		}

		TEST_METHOD(AssetRef_equalRef)
		{
			Asset<int> assetA, assetB;

			Ref<int> refA1{ &assetA };
			Ref<int> refA2{ &assetA };
			Ref<int> refB{ &assetB };
			Ref<int> refC{ nullptr };

			Assert::IsTrue(refA1 == refA2);
			Assert::IsFalse(refA1 == refB);
			Assert::IsFalse(refA1 == refC);
		}
		TEST_METHOD(AssetRef_equalNullptr)
		{
			Asset<int> assetA, assetB;
			assetA.m_factory = []() { return std::make_unique<int>(0); };

			Ref<int> refA{ &assetA };
			Ref<int> refB{ &assetB };
			Ref<int> refC{ nullptr };

			Assert::IsFalse(refA == nullptr);
			Assert::IsTrue(refA != nullptr);
			Assert::IsTrue(refB == nullptr);
			Assert::IsFalse(refB != nullptr);
			Assert::IsTrue(refC == nullptr);
			Assert::IsFalse(refC != nullptr);
		}
		TEST_METHOD(AssetRef_valid)
		{
			Asset<int> assetA, assetB;
			assetA.m_factory = []() { return std::make_unique<int>(0); };

			Ref<int> refA{ &assetA };
			Ref<int> refB{ &assetB };
			Ref<int> refC{ nullptr };

			Assert::IsTrue(refA);
			Assert::IsFalse(refB);
			Assert::IsFalse(refC);
		}
	};
}