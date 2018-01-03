
#include "CppUnitTest.h"

#include "render/scene/detail/SceneLayer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		TEST_CLASS(SceneLayerTest)
		{
		public:
			TEST_METHOD(SceneLayer_add)
			{
				SceneLayer layer;
				const auto idA = layer.add([](auto & t, auto & dt) {});
				const auto idB = layer.add([](auto & t, auto & dt) {});

				Assert::AreEqual(0u, idA);
				Assert::AreNotEqual(idA, idB);
				Assert::ExpectException<std::invalid_argument>([&layer]() { layer.add(nullptr); });
			}
			TEST_METHOD(SceneLayer_remove)
			{
				SceneLayer layer;
				const auto idA = layer.add([](auto & t, auto & dt) {});
				const auto idB = 1u;

				Assert::IsFalse(layer.remove(idB));
				Assert::IsTrue(layer.remove(idA));
				Assert::IsFalse(layer.remove(idA));
			}

			TEST_METHOD(SceneLayer_render)
			{
				bool rendered = false;

				SceneLayer layer;
				layer.add([&rendered](auto & t, auto & dt) { rendered = true; });
				layer.render(0.0_s, 0.05_s);

				Assert::IsTrue(rendered);
			}
		};
	}
}