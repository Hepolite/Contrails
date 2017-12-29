
#include "CppUnitTest.h"

#include "io/Folder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace io
{
	TEST_CLASS(FolderTest)
	{
	public:
		TEST_METHOD(Folder_get)
		{
			Folder folderA{ "data/root/subfolder/name" };
			Folder folderB{ "name" };

			Assert::AreEqual({ "data/root/subfolder/name" }, folderA.getPath());
			Assert::AreEqual({ "data/root/subfolder" }, folderA.getFolder());
			Assert::AreEqual({ "name" }, folderA.getName());

			Assert::AreEqual({ "name" }, folderB.getPath());
			Assert::AreEqual({ "" }, folderB.getFolder());
			Assert::AreEqual({ "name" }, folderB.getName());
		}
	};
}