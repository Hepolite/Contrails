
#include "CppUnitTest.h"

#include "render/scene/CameraStorage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace scene
	{
		TEST_CLASS(CameraStorageTest)
		{
		public:
			TEST_METHOD(CameraStorage_getCamera)
			{
				CameraStorage storage;
				auto & normal = storage.getCamera(CameraType::NORMAL);
				auto & mirror = storage.getCamera(CameraType::MIRROR);

				Assert::IsFalse(&normal == &mirror);
			}
		};
	}
}