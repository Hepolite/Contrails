
#include "CppUnitTest.h"

#include "render/allegro/String.h"

#include "Setup.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace render
{
	namespace allegro
	{
		TEST_CLASS(StringTest)
		{
		public:
			TEST_METHOD(String_ctor)
			{
				const String stringA;
				const String stringB{ "Hello World!" };

				Assert::AreEqual({ "" }, stringA.getString());
				Assert::AreEqual({ "Hello World!" }, stringB.getString());
			}
			TEST_METHOD(String_copy)
			{
				const String tmpA{ "Foo" }, tmpB{ "Baz" };
				const String copyA{ tmpA };
				String copyB{ "Bar" }; copyB = tmpB;

				Assert::AreEqual({ "Foo" }, copyA.getString());
				Assert::AreEqual({ "Baz" }, copyB.getString());
			}
			TEST_METHOD(String_move)
			{
				String tmpA{ "Foo" }, tmpB{ "Baz" };
				const String moveA{ std::move(tmpA) };
				String moveB{ "Bar" }; moveB = std::move(tmpB);

				Assert::AreEqual({ "Foo" }, moveA.getString());
				Assert::AreEqual({ "Baz" }, moveB.getString());
			}

			TEST_METHOD(String_length)
			{
				Assert::AreEqual(0u, String{}.length());
				Assert::AreEqual(5u, String{ "Hello" }.length());
				Assert::AreEqual(2u, String{ "Æé" }.length());
			}
			TEST_METHOD(String_at)
			{
				const String string{ "Hello!" };

				Assert::AreEqual(static_cast<unsigned int>('H'), string.at(0u));
				Assert::AreEqual(static_cast<unsigned int>('!'), string.at(5u));
				Assert::AreEqual(static_cast<unsigned int>('\0'), string.at(6u));
			}
			TEST_METHOD(String_next)
			{
				const String string{ "Te" };
				unsigned int index = 0u;

				Assert::AreEqual(static_cast<unsigned int>('T'), string.next(index));
				Assert::AreEqual(1u, index);
				Assert::AreEqual(static_cast<unsigned int>('e'), string.next(index));
				Assert::AreEqual(2u, index);
				Assert::AreEqual(static_cast<unsigned int>('\0'), string.next(index));
				Assert::AreEqual(2u, index);
			}

		private:
			setup::Context m_context;
		};
	}
}