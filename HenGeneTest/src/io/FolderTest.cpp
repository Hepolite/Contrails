
#include "CppUnitTest.h"

#include "io/Folder.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace io
{
	TEST_CLASS(FolderTest)
	{
	public:
		~FolderTest() { deinitialize(); }

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

		TEST_METHOD(Folder_create)
		{
			Assert::IsFalse(m_folder.exists());
			Assert::IsTrue(m_folder.create());
			Assert::IsFalse(m_folder.create());
			Assert::IsTrue(m_folder.exists());
		}
		TEST_METHOD(Folder_erase)
		{
			m_folder.create();

			Assert::IsTrue(m_folder.exists());
			Assert::IsTrue(m_folder.erase());
			Assert::IsFalse(m_folder.erase());
			Assert::IsFalse(m_folder.exists());
		}
		TEST_METHOD(Folder_eraseRecursively)
		{
			m_folder.create();
			File{ m_folder.getPath() + "/file.txt" }.write("Hello World!");
			Folder{ m_folder.getPath() + "/subfolder" }.create();

			Assert::IsTrue(m_folder.erase(true));
			Assert::IsFalse(m_folder.exists());
		}

	private:
		void deinitialize()
		{
			m_folder.erase(true);
		}

		Folder m_folder{ "testfolder" };
	};
}