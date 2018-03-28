
#include "CppUnitTest.h"

#include "core/scene/Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace core
{
	namespace scene
	{
		int processedA = 0;
		int processedB = 0;
		int rendered = 0;

		float processedFloat = 0.0f;

		class SystemMockA : public logic::ecs::System<int, double>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override final
			{
				processedA = 0;
				for (const auto & entity : *this)
					++processedA;
			}
		};
		class SystemMockB : public logic::ecs::System<float>
		{
		public:
			virtual void process(const Time & t, const Time & dt) override final
			{
				processedB = 0;
				for (const auto & entity : *this)
				{
					++processedB;
					processedFloat = getData<float>()[entity];
				}
			}
		};
		class RendererMock : public render::scene::Renderer<float>
		{
		public:
			virtual void render(const render::RenderContext & context, const Time & t, const Time & dt) const override final
			{
				rendered = 0;
				for (const auto & entity : *this)
					++rendered;
			}
		};

		TEST_CLASS(SceneTest)
		{
		public:
			TEST_METHOD(Scene_registerSystems)
			{
				Scene scene;
				scene.registerSystems<SystemMockA>();
				processedA = -1;
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
			}
			TEST_METHOD(Scene_registerRenderers)
			{
				Scene scene;
				scene.registerRenderers<RendererMock>();
				rendered = -1;
				scene.render(0.0_s, 0.05_s, 0.0f);

				Assert::AreEqual(0, rendered);
			}
			TEST_METHOD(Scene_clearSystems)
			{
				Scene scene;
				scene.registerSystems<SystemMockA>();
				scene.clearSystems();
				processedA = -1;
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(-1, processedA);
			}
			TEST_METHOD(Scene_clearRenderer)
			{
				Scene scene;
				scene.registerRenderers<RendererMock>();
				scene.clearRenderers();
				rendered = -1;
				scene.render(0.0_s, 0.05_s, 0.0f);

				Assert::AreEqual(-1, rendered);
			}

			TEST_METHOD(Scene_createEntity)
			{
				Scene scene;
				scene.registerSystems<SystemMockA>();
				scene.createEntity<int, double>();
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(1, processedA);
			}
			TEST_METHOD(Scene_deleteEntity)
			{
				Scene scene;
				scene.registerSystems<SystemMockA>();
				scene.deleteEntity(scene.createEntity<int, double>());
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
			}
			TEST_METHOD(Scene_clearEntities)
			{
				Scene scene;
				scene.registerSystems<SystemMockA>();
				scene.createEntity<int, double>();
				scene.clearEntities();
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
			}
			TEST_METHOD(Scene_attachComponent)
			{
				Scene scene;
				scene.registerSystems<SystemMockA, SystemMockB>();
				scene.attachEntityComponent<float>(scene.createEntity<int, double>());
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(1, processedA);
				Assert::AreEqual(1, processedB);
			}
			TEST_METHOD(Scene_detachComponent)
			{
				Scene scene;
				scene.registerSystems<SystemMockA, SystemMockB>();
				scene.detachEntityComponent<int>(scene.createEntity<int, float, double>());
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(0, processedA);
				Assert::AreEqual(1, processedB);
			}

			TEST_METHOD(Scene_getEntityData)
			{
				Scene scene;
				scene.registerSystems<SystemMockA, SystemMockB>();
				scene.getEntityData<float>(scene.createEntity<float>()) = 3.14f;
				scene.process(0.0_s, 0.05_s);

				Assert::AreEqual(3.14f, processedFloat);
			}
		};
	}
}