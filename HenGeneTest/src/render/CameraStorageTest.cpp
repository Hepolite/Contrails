
#include "CppUnitTest.h"

#include "render/CameraStorage.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
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