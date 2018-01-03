
#include "CppUnitTest.h"

#include "render/scene/Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		TEST_CLASS(SceneTest)
		{
		public:
			TEST_METHOD(Scene_add)
			{
				Scene scene;
				const auto refA = scene.add([](auto & t, auto & dt) {}, RenderLayer::SOLID);
				const auto refB = scene.add([](auto & t, auto & dt) {}, RenderLayer::SOLID);
				const auto refC = scene.add([](auto & t, auto & dt) {}, RenderLayer::CUTOFF);
				Assert::ExpectException<std::invalid_argument>([&scene]() { scene.add(nullptr, RenderLayer::SOLID); });

				Assert::AreEqual(0u, refA.second);
				Assert::AreEqual(1u, refB.second);
				Assert::AreEqual(0u, refC.second);
				Assert::IsTrue(RenderLayer::SOLID == refA.first);
				Assert::IsTrue(RenderLayer::SOLID == refB.first);
				Assert::IsTrue(RenderLayer::CUTOFF == refC.first);
			}
			TEST_METHOD(Scene_remove)
			{
				Scene scene;
				const auto refA = scene.add([](auto & t, auto & dt) {}, RenderLayer::SOLID);
				const auto refB = scene.add([](auto & t, auto & dt) {}, RenderLayer::CUTOFF);
				const auto refC = std::make_pair(RenderLayer::SOLID, 1u);

				Assert::IsTrue(scene.remove(refA));
				Assert::IsFalse(scene.remove(refA));
				Assert::IsTrue(scene.remove(refB));
				Assert::IsFalse(scene.remove(refB));
				Assert::IsFalse(scene.remove(refC));
			}

			TEST_METHOD(Scene_render)
			{
				int id = 0;
				int idBackground = -1;
				int idSolid = -1;
				int idCutoff = -1;
				int idTransparent = -1;
				int idInvisible = -1;

				Scene scene;
				scene.add([&](auto & t, auto & dt) { idBackground = id++; }, RenderLayer::BACKGROUND);
				scene.add([&](auto & t, auto & dt) { idCutoff = id++; }, RenderLayer::CUTOFF);
				scene.add([&](auto & t, auto & dt) { idInvisible = id++; }, RenderLayer::INVISIBLE);
				scene.add([&](auto & t, auto & dt) { idSolid = id++; }, RenderLayer::SOLID);
				scene.add([&](auto & t, auto & dt) { idTransparent = id++; }, RenderLayer::TRANSPARENT);
				scene.render(0.0_s, 0.05_s);

				Assert::AreEqual(0, idBackground);
				Assert::AreEqual(1, idSolid);
				Assert::AreEqual(2, idCutoff);
				Assert::AreEqual(3, idTransparent);
				Assert::AreEqual(-1, idInvisible);
			}
		};
	}
}