
#include "CppUnitTest.h"

#include "render/scene/Camera.h"
#include "util/MathGeneric.h"

#include <glm/Unittest.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		TEST_CLASS(CameraTest)
		{
		public:
			TEST_METHOD(Camera_setPosition)
			{
				Camera camera;
				camera.setPosition({ 3.0f, 1.0f, 4.0f });

				Assert::AreEqual({ 3.0f, 1.0f, 4.0f }, camera.getPosition());
			}
			TEST_METHOD(Camera_setRotation)
			{
				Camera camera;
				camera.setRotation(60.0f, 24.0f);

				Assert::AreEqual({ 60.0f, 24.0f }, camera.getRotation());
			}
			TEST_METHOD(Camera_setUpVector)
			{
				Camera camera;
				camera.setUpVector({ -0.6f, 0.6f, 0.2f });

				Assert::AreEqual({ -0.6f, 0.6f, 0.2f }, camera.getUpVector());
			}
			TEST_METHOD(Camera_setFOV)
			{
				Camera camera;
				camera.setFOV(91.0f);

				Assert::AreEqual(91.0f, camera.getFOV());
			}

			TEST_METHOD(Camera_lookTowards)
			{
				Camera cameraA, cameraB, cameraC, cameraD;
				cameraD.setPosition({ 2.0f, 4.0f, 0.0f });

				cameraA.lookTowards({ 1.0f, 0.0f, 0.0f });
				cameraB.lookTowards({ 0.0f, 1.0f, 0.0f });
				cameraC.lookTowards({ 0.0f, 0.0f, 1.0f });
				cameraD.lookTowards({ -1.0f, 1.0f, 0.0f });

				Assert::AreEqual({ 0.0f, 0.0f }, cameraA.getRotation());
				Assert::AreEqual({ 90.0f, 0.0f }, cameraB.getRotation());
				Assert::AreEqual({ 0.0f, 90.0f }, cameraC.getRotation());
				Assert::AreEqual({ 225.0f, 00.0f }, cameraD.getRotation());
			}
			TEST_METHOD(Camera_getLookVector)
			{
				Camera camera;
				camera.lookTowards({ 5.0f, 5.0f, -5.0f });
				camera.process();

				Assert::AreEqual({ 58, 58, -58 }, math::round(100.0f * camera.getLookVector()));
			}
		};
	}
}