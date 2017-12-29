
#include "CppUnitTest.h"

#include "io/File.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace io
{
	TEST_CLASS(FileTest)
	{
	public:
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

		TEST_METHOD(File_io)
		{
			File file{ "TestFileIo" };
			file.erase();

			Assert::IsFalse(file.exists());
			Assert::IsTrue(file.create());
			Assert::IsFalse(file.create());
			Assert::IsTrue(file.exists());
			Assert::IsTrue(file.erase());
			Assert::IsFalse(file.erase());
			Assert::IsFalse(file.exists());
		}

		TEST_METHOD(File_write)
		{
			File file{ "TestFileWrite.txt" };
			file.erase();

			file.write("This is some data");
			Assert::AreEqual({ "This is some data" }, file.read());
			Assert::AreEqual({ "This is some data" }, file.parse());

			file.erase();
		}
	};
}