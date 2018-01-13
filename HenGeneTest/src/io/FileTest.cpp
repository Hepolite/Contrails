
#include "CppUnitTest.h"

#include "io/File.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace io
{
	TEST_CLASS(FileTest)
	{
	public:
		~FileTest() { deinitialize(); }

		TEST_METHOD(File_get)
		{
			File fileA{ "data/root/subfolder/name.txt" };
			File fileB{ "name" };

			Assert::AreEqual({ "data/root/subfolder/name.txt" }, fileA.getPath());
			Assert::AreEqual({ "data/root/subfolder" }, fileA.getFolder());
			Assert::AreEqual({ "name" }, fileA.getName());
			Assert::AreEqual({ "txt" }, fileA.getExtension());

			Assert::AreEqual({ "name" }, fileB.getPath());
			Assert::AreEqual({ "" }, fileB.getFolder());
			Assert::AreEqual({ "name" }, fileB.getName());
			Assert::AreEqual({ "" }, fileB.getExtension());
		}

		TEST_METHOD(File_create)
		{
			Assert::IsFalse(m_file.exists());
			Assert::IsTrue(m_file.create());
			Assert::IsFalse(m_file.create());
			Assert::IsTrue(m_file.exists());
		}
		TEST_METHOD(File_erase)
		{
			m_file.create();

			Assert::IsTrue(m_file.exists());
			Assert::IsTrue(m_file.erase());
			Assert::IsFalse(m_file.erase());
			Assert::IsFalse(m_file.exists());
		}

		TEST_METHOD(File_write)
		{
			m_file.write("This is some data");
			Assert::AreEqual({ "This is some data" }, m_file.read());
			Assert::AreEqual({ "This is some data" }, m_file.parse());
		}

	private:
		void deinitialize()
		{
			m_file.erase();
		}

		File m_file{ "testfile.txt" };
	};
}